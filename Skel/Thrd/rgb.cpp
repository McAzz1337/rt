//  self

    #include "rgb.h"


//  qt

    #include <QColor>


//  c++

    using namespace std;



RGB :: RGB ()
    : R (0)
    , G (0)
    , B (0)
{
}



RGB :: RGB (double r, double g, double b)
    : R (clamp (r, 0.0, 1.0))
    , G (clamp (g, 0.0, 1.0))
    , B (clamp (b, 0.0, 1.0))
{
}



RGB :: RGB (const QColor & c)
    : R (c.redF())
    , G (c.greenF())
    , B (c.blueF())
{
}

RGB RGB::mix(double f, const RGB& color) {

    double g = 1 - f;

    return RGB(g * R + f * color.r(), g * G + f * color.g(), g * B + f * color.b());

}
bool RGB::operator==(const RGB& r) const {

    return R == r.r() && G == r.g() && B == r.b();
}
bool RGB::operator!=(const RGB& r) const {

    return !(*this == r);
}

RGB RGB::operator*(double i) const {

    return RGB(i * R, i * G, i *B);
}

RGB RGB::operator+(const RGB& c) const {

    return RGB(R + c.r(), G + c.b(), B + c.b());
}
