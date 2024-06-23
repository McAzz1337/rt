 //  self

    #include "thrd-pool.h"


//  app

    #include "canvas.h"
    #include "thrd.h"
    #include "permutation.h"
    #include "prgs-bar.h"
    #include "scan-line.h"
    #include "stk-widget.h"
    #include "parm-dialog.h"


//  c++

    using namespace std;



ThrdPool :: ThrdPool ()
    : ThrdsRunning (0)
    , ScanlinesActive (0)
    , StkPtr (nullptr)
    , PgbPtr (nullptr)
{
}



void ThrdPool :: MakeThreads ()
{
    ThrdPtrs.clear();

    for (int id = 0, n = ParmPtr->threadCount(); id < n; ++id)
    {
        ThrdPtr tp = ThrdFactoryBase::make();

        connect (this, & ThrdPool::sigInitializeThread,
            tp.get(), & Thrd::sltThreadInitialized,
            Qt::QueuedConnection);

        connect (tp.get(), & Thrd::sigThreadInitialized,
            this, & ThrdPool::SltThreadInitialized,
            Qt::QueuedConnection);

        connect (this, & ThrdPool::sigStartImage,
            tp.get(), & Thrd::sltStartImage,
            Qt::QueuedConnection);

        connect (tp.get(), & Thrd::sigImageStarted,
            this, & ThrdPool::SltImageStarted,
            Qt::QueuedConnection);

        connect (this, & ThrdPool::sigFinishImage,
                tp.get(), & Thrd::sltFinishImage,
            Qt::QueuedConnection);

        connect (tp.get(), & Thrd::sigImageFinished,
            this, & ThrdPool::SltImageFinished,
            Qt::QueuedConnection);

        connect (tp.get(), & Thrd::sigDisplayLine,
            StkPtr->cnv(), & Canvas::sltDrawScanLine,
            Qt::QueuedConnection);

        ThrdPtrs.push_back (tp);
        tp->start (id, StkPtr->out());
    }
}



void ThrdPool :: ComputeImage ()
{
    int w = ParmPtr->width();
    int h = ParmPtr->height();
    PermPtr = make_shared <Permutation> (h, ParmPtr->permuteLines());

    // emit sigCanvasSize (w, h);
    emit sigBeginOfImage (ParmPtr);
    emit sigProgressStart (h);
    ThrdsRunning = int (ThrdPtrs.size());
    emit sigInitializeThread (w, h);
}



void ThrdPool :: connectWidgets (StkWidget * stkptr, PrgsBar * pgbptr)
{
    StkPtr = stkptr;

    // connect (this, & ThrdPool::sigCanvasSize,
    //     StkPtr->cnv(), & Canvas::sltResize,
    //     Qt::QueuedConnection);

    connect (this, & ThrdPool::sigBeginOfImage,
        StkPtr->cnv(), & Canvas::sltBeginOfImage,
        Qt::QueuedConnection);

    connect (StkPtr->cnv(), & Canvas::sigScanLineDrawn,
            this, & ThrdPool::SltComputeScanLine,
        Qt::QueuedConnection);

    connect (this, & ThrdPool::sigProgressStart,
            pgbptr, & PrgsBar::sltStart,
        Qt::QueuedConnection);

    connect (this, & ThrdPool::sigProgressStep,
            pgbptr, & PrgsBar::sltStep,
            Qt::QueuedConnection);
}



void ThrdPool :: compute (ParmDialogPtr parmptr)
{
    ParmPtr = parmptr;
    MakeThreads();
    ComputeImage();
}



void ThrdPool :: SltThreadInitialized ()
{
    if (ThrdsRunning > 0)
    {
        --ThrdsRunning;
        if (ThrdsRunning <= 0)
        {
            ThrdsRunning = int (ThrdPtrs.size());
            emit sigStartImage();
        }
    }
}



void ThrdPool :: SltImageStarted ()
{
    if (ThrdsRunning > 0)
    {
        --ThrdsRunning;
        if (ThrdsRunning <= 0)
        {
            ScanlinesActive = 0;
            for (int i = 0, m = ParmPtr->linesPerThread(); i < m; ++i)
                for (int k = 0, n = int (ThrdPtrs.size()); k < n; ++k)
                {
                    int w = ParmPtr->width();
                    ScanLinePtr lptr = make_shared <ScanLine> (ThrdPtrs [k], w);
                    ++ScanlinesActive;
                    SltComputeScanLine (lptr);
                }
        }
    }
}



void ThrdPool :: SltComputeScanLine (ScanLinePtr pptr)
{
    if (PermPtr)
    {
        if (PermPtr->valid())
        {
            pptr->compute (PermPtr->next());
            emit sigProgressStep();
        }
        else
        {
            if (ScanlinesActive > 0)
            {
                --ScanlinesActive;
                if (ScanlinesActive <= 0)
                {
                    ThrdsRunning = int (ThrdPtrs.size());
                    emit sigFinishImage();
                }
            }
        }
    }
}



void ThrdPool :: SltImageFinished ()
{
    if (ThrdsRunning > 0)
    {
        --ThrdsRunning;
        if (ThrdsRunning <= 0)
        {
            //  done
        }
    }
}
