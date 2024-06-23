//  self

    #include "prgs-bar.h"


//  qt

    #include <QElapsedTimer>
    #include <QTimer>



PrgsBar :: PrgsBar (QWidget *parent)
    : QProgressBar (parent)
    , TimPtr (new QTimer)
    , ElaPtr (new QElapsedTimer)
    , NextSystemStep (1)
    , UserSteps (1)
    , CurrentUserStep (0)
{
    setRange (0, SystemSteps);

    TimPtr->setInterval (100);

    connect (TimPtr, & QTimer::timeout,
            this, & PrgsBar::SltTick,
        Qt::QueuedConnection);
}



PrgsBar :: ~ PrgsBar ()
{
    delete ElaPtr;
    delete TimPtr;
}



QString PrgsBar :: TimeStr (int ms) const
{
    int sec = int (ms / 1000.0 + 0.5);
    int min = sec / 60;
    sec -= min * 60;
    return QString ("%1:%2%3") .arg (min) .arg (sec / 10). arg (sec % 10);
}



void PrgsBar :: Adjust ()
{
    setFormat (Done + " elapsed     %p% done     " + Todo + " left");
}



void PrgsBar :: SltTick ()
{
    long done = ElaPtr->elapsed();
    Done = TimeStr (done);
    Adjust();

    if (done >= 100)
    {
        double v = double (CurrentUserStep) / done;
        long todo = long ((UserSteps - CurrentUserStep) / v + 0.5);
        Todo = TimeStr (todo);
        Adjust();
    }
}



void PrgsBar :: sltStart (int usersteps)
{
    UserSteps = usersteps > 1 ? usersteps : 1;
    CurrentUserStep = 0;
    NextSystemStep = int (double (UserSteps) / SystemSteps + 0.5);
    setEnabled (true);
    setValue (0);
    TimPtr->start();
    ElaPtr->start();
}



void PrgsBar :: sltStep ()
{
    if (++CurrentUserStep < UserSteps)
    {
        if (CurrentUserStep >= NextSystemStep)
        {
            int step = int (double (CurrentUserStep) / UserSteps * SystemSteps + 0.5);
            setValue (step);
            NextSystemStep = long ((step + 1.0) / SystemSteps * UserSteps + 0.5);
        }
    }
    else
    {
        TimPtr->stop();
        Todo = "";
        Done = TimeStr (ElaPtr->elapsed());
        setValue (0);
        setFormat (Done + " elapsed");
        setEnabled (false);
    }
}
