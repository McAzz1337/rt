#ifndef IO_H_INCLUDED
#define IO_H_INCLUDED



//  qt

    class QRect;


//  c++

    #include <istream>


std::istream & operator >> (std::istream & file, QRect & rect);
std::ostream & operator << (std::ostream & file, const QRect & rect);



#endif
