#ifndef PARM_DIALOG_H_INCLUDED
#define PARM_DIALOG_H_INCLUDED



//  app

    #include "cfg.h"


//  qt designer

    namespace Ui { class ParameterDialog; }


//  qt

    class QLineEdit;

    #include <QDialog>



class ParmDialog
    : public QDialog
{
        Q_OBJECT

        Ui::ParameterDialog * UiPtr;

        CfgVar <int> Width;
        CfgVar <int> Height;
        CfgVar <int> ThrdCount;
        CfgVar <int> LinesPerThrd;
        CfgVar <bool> PermLines;
        CfgVar <int> UpIntMs;

        void AdjustThrdCount ();

        void SetValue (QLineEdit * qle, int val);
        void GetValue (QLineEdit * qle, CfgVar <int> & var);

        void SetValues ();
        void GetValues ();


    public:

        explicit ParmDialog (QWidget * parent = nullptr);
        ~ ParmDialog ();

        int width () const;
        int height () const;
        int threadCount () const;
        int linesPerThread () const;
        bool permuteLines () const;
        int updateMs () const;


    public slots:

        virtual int exec () override;
};



#endif
