//  self

    #include "main-window.h"


//  app

    #include "canvas.h"
    #include "file-dialog.h"
    #include "parm-dialog.h"
    #include "prgs-bar.h"
    #include "thrd-pool.h"
    #include "thrd.h"


//  qt designer

    #include "ui_main-window.h"


//  c++

    using namespace std;



MainWindow :: MainWindow (const QString & name)
    : UiPtr (new Ui::MainWindow)
    , FileDlgPtr (new FileDialog)
    , PrgsPtr (new PrgsBar)
    , Geometry ("geometry", geometry())
    , Maximized ("maximized", false)
    , ParmDlgPtr (make_shared <ParmDialog> ())
    , FirstShow (true)
{
    UiPtr->setupUi (this);
    setGeometry (Geometry);
    setWindowTitle ("   Ray Tracing ++   |   " + name);
    FileDlgPtr->setBaseName (name);

    QPalette ppal = PrgsPtr->palette();
    QPalette spal = UiPtr->Sts->palette();
    ppal.setColor (QPalette::Base, spal.color (QPalette::Window));
    PrgsPtr->setPalette (ppal);
    UiPtr->Sts->addPermanentWidget (PrgsPtr, 1);

    Thrd::setBackground (UiPtr->Stk->cnv()->palette().color (QPalette::Window));

    connect (UiPtr->ActFileClear, & QAction::triggered,
            UiPtr->Stk, & StkWidget::sltClear,
        Qt::QueuedConnection);

    connect (UiPtr->ActFileClear, & QAction::triggered,
            PrgsPtr, & QProgressBar::reset,
        Qt::QueuedConnection);

    connect (UiPtr->ActFileSave, & QAction::triggered,
        FileDlgPtr, & FileDialog::sltSave,
        Qt::QueuedConnection);

    connect (FileDlgPtr, & FileDialog::sigSave,
        UiPtr->Stk->cnv(), & Canvas::sltSave,
        Qt::QueuedConnection);

    connect (UiPtr->ActCompImg, & QAction::triggered,
        this, & MainWindow::SltCompute,
        Qt::QueuedConnection);

    connect (UiPtr->ActCompParm, & QAction::triggered,
        this, & MainWindow::SltParameters,
        Qt::QueuedConnection);

    UiPtr->Stk->connectActions (UiPtr->ActShowCanvas, UiPtr->ActShowOutput,
        UiPtr->ActShowToggle);

    ThrdPoolPtr tp = ThrdPool::instptr();
    tp->connectWidgets (UiPtr->Stk, PrgsPtr);
}



MainWindow :: ~ MainWindow ()
{
    Geometry = geometry();
    Maximized = isMaximized();

    delete PrgsPtr;
    delete FileDlgPtr;
    delete UiPtr;
}



void MainWindow :: showEvent (QShowEvent *)
{
    if (FirstShow)
    {
        FirstShow = false;
        SltCompute();
    }
}



void MainWindow :: SltCompute ()
{
    UiPtr->Stk->sltClear();
    ThrdPoolPtr tp = ThrdPool::instptr();
    tp->compute (ParmDlgPtr);
}



void MainWindow :: SltParameters ()
{
    if (ParmDlgPtr->exec() == QDialog::Accepted)
        SltCompute();
}



void MainWindow :: show ()
{
    if (Maximized)
        showMaximized();
    else
        QMainWindow::show();
}
