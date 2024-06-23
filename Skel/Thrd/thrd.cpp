//  self

    #include "thrd.h"


//  app

    #include "scan-line.h"
    #include "out-widget.h"


//  qt

    #include <QThread>



RGB Thrd::Background;



Thrd :: Thrd ()
    : Id (-1)
    , ThrdPtr (new QThread)
    , Width (1)
    , Height (1)
    , Y (0)
    , LinesComputed (0)
{
    moveToThread (ThrdPtr);
    ThrdPtr->start (QThread::IdlePriority);
}



Thrd :: ~ Thrd ()
{
    ThrdPtr->terminate();
    ThrdPtr->wait();
    delete ThrdPtr;
}



void Thrd :: Initialize ()
{
}



void Thrd :: BeginOfImage ()
{
}



void Thrd :: EndOfImage ()
{
}



void Thrd :: BeginOfScanLine ()
{
}



void Thrd :: EndOfScanLine ()
{
}



RGB Thrd :: ComputePixel (int, int)
{
    return RGB (0, 0, 0);
}



void Thrd :: setBackground (const RGB & background)
{
    Background = background;
}



RGB Thrd :: background () const
{
    return Background;
}



void Thrd :: start (int id, OutWidget * txtptr)
{
    Id = id;

    auto func = [this, txtptr] () { SltInitialize (txtptr); };
    QMetaObject::invokeMethod (this, func, Qt::QueuedConnection);
}



void Thrd :: SltInitialize (OutWidget * txtptr)
{
    cout.initialize();
    cerr.initialize();
    clog.initialize();

    connect (& cout, & OutStream::sigOut,
            txtptr, & OutWidget::sltCout,
        Qt::QueuedConnection);

    connect (& cerr, & OutStream::sigOut,
            txtptr, & OutWidget::sltCerr,
        Qt::QueuedConnection);

    connect (& clog, & OutStream::sigOut,
            txtptr, & OutWidget::sltClog,
        Qt::QueuedConnection);
}



void Thrd :: sltThreadInitialized (int w, int h)
{
    Width = w;
    Height = h;
    Initialize();
    emit sigThreadInitialized();
}



void Thrd :: sltStartImage ()
{
    BeginOfImage();
    emit sigImageStarted();
}



void Thrd :: sltFinishImage ()
{
    EndOfImage(),
    emit sigImageFinished();
}



void Thrd :: sltComputeLine (ScanLinePtr pptr)
{
    Y = pptr->y();
    BeginOfScanLine();

    for (int x = 0, w = pptr->width(); x < w; ++x)
        pptr->setRgb (x, ComputePixel (x, Y));
    EndOfScanLine();

    emit sigDisplayLine (pptr);
    ++LinesComputed;
}
