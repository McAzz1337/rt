//  self

    #include "out-widget.h"



OutWidget :: OutWidget (QWidget * parent)
    : QTextEdit (parent)
    , Out (false), ColCout (QColor (0, 0, 0))
    , Err (false), ColCerr (QColor (192, 0, 0))
    , Log (false), ColClog (QColor (0, 128, 0))
{
    setReadOnly (true);
    setFrameShape(QFrame::NoFrame);

    QPalette pal = palette();
    QColor col = pal.color (QPalette::Window);
    pal.setColor (QPalette::Base, col);
    setPalette (pal);
}



void OutWidget :: sltCout (QString qs)
{
    if (! Out)
    {
        Out = true; Err = Log = false;
        setTextColor (ColCout);
    }

    append (qs);
}



void OutWidget :: sltCerr (QString qs)
{
    if (! Err)
    {
        Err = true; Out = Log = false;
        setTextColor (ColCerr);
    }

    append (qs);
}



void OutWidget :: sltClog (QString qs)
{
    if (! Log)
    {
        Log = true; Out = Err = false;
        setTextColor (ColClog);
    }

    append (qs);
}
