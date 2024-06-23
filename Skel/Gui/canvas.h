#ifndef CANVAS_H_INCLUDED
#define CANVAS_H_INCLUDED



//  app

    #include "scan-line-ptr.h"
    #include "parm-dialog-ptr.h"


//  qt

    #include <QLabel>



class Canvas
    : public QLabel
{
        Q_OBJECT

        QColor DefaultColor;
        QImage Image;
        QPixmap Pixmap;
        bool Changed;
        QTimer * TimePtr;


        static int D2B (double d);
        static QColor D2C (double r, double g, double b);

        void MarkChanged ();
        void Show ();


    protected:

        void resizeEvent (QResizeEvent * event) override;


    public:

        Canvas (QWidget * parent = nullptr);
        ~ Canvas ();

        Canvas (const Canvas &) = delete;
        Canvas & operator = (const Canvas &) = delete;

        void clear ();


    signals:

        void sigScanLineDrawn (ScanLinePtr lptr);
        void sigInfo ();


    private slots:

        void SltShow ();


    public slots:

        // void sltResize (int w, int h);
        void sltBeginOfImage (ParmDialogPtr parmptr);
        void sltDrawScanLine (ScanLinePtr lptr);
        void sltSave (QString filename);
};



#endif
