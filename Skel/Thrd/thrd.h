#ifndef THRD_H_INCLUDED
#define THRD_H_INCLUDED



//  app

    class OutWidget;

    #include "rgb.h"
    #include "thrd-factory.h"
    #include "out-stream.h"
    #include "scan-line-ptr.h"



#define RegisterThrd(Class) \
    ThrdFactoryBasePtr ThrdFactoryDummy = ThrdFactoryTmpl<Class>::construct();



class Thrd
    : public QObject
{
        Q_OBJECT

        static RGB Background;

        int Id;
        QThread * ThrdPtr;
        int Width, Height, Y, LinesComputed;


    protected:

        OutStream cout, cerr, clog;


        Thrd ();
        virtual ~ Thrd ();

        Thrd (const Thrd &) = delete;
        Thrd & operator = (const Thrd &) = delete;

        virtual void Initialize ();
        virtual void BeginOfImage ();
        virtual void EndOfImage ();
        virtual void BeginOfScanLine ();
        virtual void EndOfScanLine ();
        virtual RGB ComputePixel (int x, int y);


    public:

        int id () const { return Id; }
        int width () const { return Width; }
        int height () const { return Height; }
        int y () const { return Y; }
        int linesComputed () const { return LinesComputed; }

        static void setBackground (const RGB & background);
        RGB background () const;

        void start (int id, OutWidget * txtptr);


    signals:

        void sigThreadInitialized ();
        void sigDisplayLine (ScanLinePtr);
        void sigImageStarted ();
        void sigImageFinished ();


    private slots:

        void SltInitialize (OutWidget * txtptr);


    public slots:

        void sltThreadInitialized (int w, int h);
        void sltStartImage ();
        void sltFinishImage ();
        void sltComputeLine (ScanLinePtr pptr);
};



#endif
