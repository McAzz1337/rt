#ifndef THRD_POOL_H_INCLUDED
#define THRD_POOL_H_INCLUDED



//  app

    class Permutation;
    class PrgsBar;
    class StkWidget;

    #include "cfg.h"
    #include "parm-dialog-ptr.h"
    #include "scan-line-ptr.h"
    #include "thrd-ptr.h"
    #include "thrd-pool-ptr.h"


//  qt

    #include <QObject>



class ThrdPool
    : public QObject
    , public Singleton <ThrdPool>
{
        Q_OBJECT


        std::vector <ThrdPtr> ThrdPtrs;
        std::shared_ptr <Permutation> PermPtr;
        int ThrdsRunning;
        int ScanlinesActive;

        StkWidget * StkPtr;
        PrgsBar * PgbPtr;
        ParmDialogPtr ParmPtr;


        void MakeThreads ();
        void ComputeImage ();


    public:

        ThrdPool ();

        void connectWidgets (StkWidget * stkptr, PrgsBar * pgbptr);
        void compute (ParmDialogPtr parmptr);


    signals:

        // void sigCanvasSize (int w, int h);
        void sigBeginOfImage (ParmDialogPtr parmptr);

        void sigInitializeThread (int w, int h);
        void sigStartImage ();
        void sigFinishImage ();

        void sigProgressStart (long max);
        void sigProgressStep ();


    private slots:

        void SltThreadInitialized ();
        void SltComputeScanLine (ScanLinePtr pptr);
        void SltImageStarted ();
        void SltImageFinished ();
};



#endif
