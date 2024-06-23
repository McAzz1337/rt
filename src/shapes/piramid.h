#ifndef PIRAMID_H
#define PIRAMID_H

#include "triangle.h"
#include "object.h"

class Piramid : public Object
{

    static constexpr int TRI_COUNT = 6;
    Triangle tris[TRI_COUNT];

public:
    Piramid();
    Piramid(const Piramid& p);
    Piramid(const Vec3& pos, Material* mat,  double side, double height);

    virtual bool hit(const Ray& ray, PoI& poi) override;

    inline void print(int i) {

        Triangle& t = tris[i];
        printf("%f\t%f\t%f\n", t[0].x, t[0].y, t[0].z);
        printf("%f\t%f\t%f\n", t[1].x, t[1].y, t[1].z);
        printf("%f\t%f\t%f\n", t[2].x, t[2].y, t[2].z);

        Vec3 n = t.getNormal();
        printf("%f\t%f\t%f\n", n.x, n.y, n.z);
    }

    inline const Triangle& operator[](int i) {

        assert(i < TRI_COUNT);

        return tris[i];
    }
};

#endif // PIRAMID_H
