#ifndef MAIN_WINDOW_H_INCLUDED
#define MAIN_WINDOW_H_INCLUDED



//  app

    class FileDialog;
    class PrgsBar;

    #include "cfg.h"
    #include "parm-dialog-ptr.h"


//  qt designer

    namespace Ui { class MainWindow; }


//  qt

    #include <QMainWindow>



class MainWindow
    : public QMainWindow
{
        Q_OBJECT


        Ui::MainWindow * UiPtr;
        FileDialog * FileDlgPtr;
        PrgsBar * PrgsPtr;

        CfgVar <QRect> Geometry;
        CfgVar <bool> Maximized;

        ParmDialogPtr ParmDlgPtr;


        bool FirstShow;


    protected:

        virtual void showEvent (QShowEvent *) override;


    public:

        MainWindow (const QString & name);
        ~ MainWindow ();

        MainWindow (const MainWindow &) = delete;
        MainWindow & operator = (const MainWindow &) = delete;


    private slots:

        void SltCompute ();
        void SltParameters ();


    public slots:

        virtual void show ();
};



#endif
