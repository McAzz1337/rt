//  self

    #include "stk-widget.h"


//  app

    #include "canvas.h"
    #include "out-widget.h"


//  qt

    #include <QAction>



StkWidget :: StkWidget (QWidget * parent)
    : QStackedWidget (parent)
    , CnvPtr (new Canvas)
    , OutPtr (new OutWidget)
    , ShowCanvas ("show-canvas", true)
{
    addWidget (CnvPtr);
    addWidget (OutPtr);

    if (ShowCanvas)
        SltShowCanvas();
    else
        SltShowToggle();

}



StkWidget :: ~ StkWidget ()
{
    ShowCanvas = currentWidget() == CnvPtr;
}



void StkWidget :: connectActions
    (QAction * canvas, QAction * output, QAction * toggle)
{
    connect (canvas, & QAction::triggered,
            this, & StkWidget::SltShowCanvas,
        Qt::QueuedConnection);

    connect (output, & QAction::triggered,
            this, & StkWidget::SltShowOutput,
        Qt::QueuedConnection);

    connect (toggle, & QAction::triggered,
            this, & StkWidget::SltShowToggle,
        Qt::QueuedConnection);

}



void StkWidget :: SltShowCanvas ()
{
    setCurrentWidget (CnvPtr);
}



void StkWidget :: SltShowOutput ()
{
    setCurrentWidget (OutPtr);
}



void StkWidget :: SltShowToggle ()
{
    int i = currentIndex();
    int n = count();
    int k = (i + 1) % n;
    setCurrentIndex (k);
}



void StkWidget :: sltClear ()
{
    CnvPtr->clear();
    OutPtr->clear();
}
