//  self

    #include "scan-line.h"


//  app

    #include "thrd.h"


//  c++

    using namespace std;



ScanLine :: ScanLine (ThrdPtr tptr, int wd)
    : ThrPtr (tptr)
    , Line (wd)
    , Y (0)
{
}



int ScanLine :: D2B (double d)
{
    return int (clamp (d, 0.0, 1.0) * 255.0 + 0.5);
}



QRgb ScanLine :: qrgb (int x) const
{
    if (0 <= x && x < width())
        return Line [x];
    return qRgb (0, 0, 0);
}



void ScanLine :: setQrgb (int x, const QRgb & qrgb)
{
    Line [x] = qrgb;
}



void ScanLine :: setRgb (int x, const RGB & c)
{
    setQrgb (x, qRgb (D2B (c.r()), D2B (c.g()), D2B (c.b())));
}



void ScanLine :: compute (int y)
{
    Y = y;
    ScanLinePtr lptr = shared_from_this();
    auto func = [this, lptr] () { ThrPtr->sltComputeLine (lptr); };
    QMetaObject::invokeMethod (ThrPtr.get(), func, Qt::QueuedConnection);
}
