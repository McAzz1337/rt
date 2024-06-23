//  self

    #include "canvas.h"


//  app

    #include "parm-dialog.h"
    #include "scan-line.h"


//  qt

    #include <QTimer>


//  c++

    using namespace std;



Canvas :: Canvas (QWidget * parent)
    : QLabel (parent)
    , DefaultColor (palette() .color (QPalette::Window))
    , Image (15, 10, QImage::Format_RGB32)
    , Changed (false)
    , TimePtr (new QTimer)
{
    setAlignment (Qt::AlignHCenter | Qt::AlignVCenter);
    setSizePolicy (QSizePolicy::Ignored, QSizePolicy::Ignored);

    Image.fill (DefaultColor);

    TimePtr->setSingleShot (true);

    connect (TimePtr, & QTimer::timeout,
        this, & Canvas::SltShow,
        Qt::QueuedConnection);
}



Canvas :: ~ Canvas ()
{
    TimePtr->stop();
    delete TimePtr;
}



int Canvas :: D2B (double d)
{
    return int (255.0 * clamp (d, 0.0, 1.0) + 0.5);
}



QColor Canvas :: D2C (double r, double g, double b)
{
    return QColor (D2B (r), D2B (g), D2B (b));
}



void Canvas :: MarkChanged ()
{
    if (! Changed)
    {
        Changed = true;
        if (! TimePtr->isActive())
            TimePtr->start();
    }
}



void Canvas :: Show ()
{
    if (! Pixmap.isNull())
    {
        QPixmap pixmap = Pixmap.scaled (size(), Qt::KeepAspectRatio,
            Qt::SmoothTransformation);
        setPixmap (pixmap);
    }
}



void Canvas :: resizeEvent (QResizeEvent * event)
{
    QLabel::resizeEvent (event);
    Show();
}



void Canvas :: SltShow ()
{
    Changed = false;
    Pixmap = QPixmap::fromImage (Image);
    Show();
}



void Canvas :: clear ()
{
    Image.fill (DefaultColor);
    SltShow();
    // MarkChanged();
}



// void Canvas :: sltResize (int w, int h)
// {
//     Image = QImage (w, h, QImage::Format_RGB32);
//     Image.fill (DefaultColor);
//     MarkChanged();
//     emit sigInfo();
// }



void Canvas :: sltBeginOfImage (ParmDialogPtr parmptr)
{
    TimePtr->stop();

    int w = parmptr->width();
    int h = parmptr->height();

    Image = QImage (w, h, QImage::Format_RGB32);
    Image.fill (DefaultColor);
    // MarkChanged();
    emit sigInfo();

    TimePtr->setInterval (parmptr->updateMs());
}



void Canvas :: sltDrawScanLine (ScanLinePtr lptr)
{
    int y = lptr->y();
    int w = lptr->width();
    for (int x = 0; x < w; ++x)
    {
        QRgb c = lptr->qrgb (x);
        Image.setPixel (x, y, c);
    }

    MarkChanged();
    emit sigScanLineDrawn (lptr);
}



void Canvas :: sltSave (QString filename)
{
    Image.save (filename, "tiff");
}
