#ifndef STK_WIDGET_H_INCLUDED
#define STK_WIDGET_H_INCLUDED



//  app

    class Canvas;
    class OutWidget;

    #include "cfg.h"


//  qt

    #include <QStackedWidget>



class StkWidget
    : public QStackedWidget
{
        Q_OBJECT

        Canvas * CnvPtr;
        OutWidget * OutPtr;
        CfgVar <bool> ShowCanvas;


    public:

        StkWidget (QWidget * parent);
        ~ StkWidget ();

        void connectActions (QAction * canvas, QAction * output, QAction * toggle);

        Canvas * cnv () const { return CnvPtr; }
        OutWidget * out () const { return OutPtr; }


    private slots:

        void SltShowCanvas ();
        void SltShowOutput ();
        void SltShowToggle ();


    public slots:

        void sltClear ();
};



#endif
