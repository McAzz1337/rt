//  self

    #include "io.h"


//  qt

    #include <QRect>


//  c++

    using namespace std;



istream &operator >> (istream & file, QRect & rect)
{
    int x, y, w, h;
    if (file >> x >> y >> w >> h)
        rect = QRect (x, y, w, h);
    return file;
}



ostream & operator << (std::ostream & file, const QRect & rect)
{
    file << rect.x() << " " << rect.y() << " " << rect.width() << " " << rect.height();
    return file;
}
