//  self

    #include "parm-dialog.h"


//  qt creator

    #include "ui_parm-dialog.h"


//  qt

    #include <QThread>



ParmDialog :: ParmDialog (QWidget * parent)
    : QDialog (parent)
    , UiPtr (new Ui::ParameterDialog)
    , Width ("image-width", 1600)
    , Height ("image-height", 1200)
    , ThrdCount ("thread-count", 99)
    , LinesPerThrd ("lines-per-thread", 10)
    , PermLines ("permute-lines", true)
    , UpIntMs ("update-ms", 200)
{
    UiPtr->setupUi (this);
    AdjustThrdCount();
}



ParmDialog :: ~ ParmDialog ()
{
    delete UiPtr;
}



void ParmDialog :: AdjustThrdCount ()
{
    int n = QThread::idealThreadCount();
    if (ThrdCount > n)
        ThrdCount = n;
}



void ParmDialog :: SetValue (QLineEdit * qle, int val)
{
    QString text = QString ("%1") .arg (val);
    qle->setText (text);
}



void ParmDialog :: GetValue (QLineEdit * qle, CfgVar <int> & var)
{
    QString text = qle->text();
    bool ok;
    int val = text.toInt (& ok);
    if (ok && val > 0)
        var = val;
}



void ParmDialog :: SetValues ()
{
    SetValue (UiPtr->EdtWidth, Width);
    SetValue (UiPtr->EdtHeight, Height);
    SetValue (UiPtr->EdtThrdCount, ThrdCount);
    SetValue (UiPtr->EdtLinesPerThrd, LinesPerThrd);
    SetValue (UiPtr->EdtUpInt, UpIntMs);

    UiPtr->CbxPermLines->setChecked (PermLines);
}



void ParmDialog :: GetValues ()
{
    GetValue (UiPtr->EdtWidth, Width);
    GetValue (UiPtr->EdtHeight, Height);
    GetValue (UiPtr->EdtThrdCount, ThrdCount);
    GetValue (UiPtr->EdtLinesPerThrd, LinesPerThrd);
    GetValue (UiPtr->EdtUpInt, UpIntMs);

    PermLines = UiPtr->CbxPermLines->isChecked();

    AdjustThrdCount();
}



int ParmDialog :: width () const
{
    return Width;
}



int ParmDialog :: height () const
{
    return Height;
}



int ParmDialog :: threadCount () const
{
    return ThrdCount;
}



int ParmDialog :: linesPerThread () const
{
    return LinesPerThrd;
}



bool ParmDialog :: permuteLines() const
{
    return PermLines;
}



int ParmDialog :: updateMs () const
{
    return UpIntMs;
}



int ParmDialog :: exec ()
{
    SetValues();
    int res = QDialog::exec();
    if (res == QDialog::Accepted)
        GetValues();
    return res;
}
