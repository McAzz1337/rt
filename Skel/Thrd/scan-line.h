#ifndef SCAN_LINE_H_INCLUDED
#define SCAN_LINE_H_INCLUDED



//  app

    class RGB;

    #include "thrd-ptr.h"


//  qt

    #include <QRgb>


//  c++

    #include <vector>



class ScanLine
    : public std::enable_shared_from_this <ScanLine>
{
    ThrdPtr ThrPtr;
        std::vector <QRgb> Line;
        int Y;


        static int D2B (double d);


    public:
        
        ScanLine (ThrdPtr tptr, int wd);

        int width () const { return int (Line.size()); }
        int y () const { return Y; }

        QRgb qrgb (int x) const;
        void setQrgb (int x, const QRgb & qrgb);
        void setRgb (int x, const RGB & c);

        void compute (int y);
};



#endif
