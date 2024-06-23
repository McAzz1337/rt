#ifndef RGB_H_INCLUDED
#define RGB_H_INCLUDED



//  qt

    class QColor;



class RGB
{
        double R, G, B;


    public:

        RGB ();
        RGB (double r, double g, double b);
        RGB (const QColor & c);

        double r () const { return R; }
        double g () const { return G; }
        double b () const { return B; }

        RGB mix(double f, const RGB& color);

        bool operator==(const RGB& r) const;
        bool operator!=(const RGB& r) const;
        RGB operator*(double i) const;
        RGB operator+(const RGB& c) const;
};



#endif
