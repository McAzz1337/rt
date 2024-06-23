#ifndef TRI_H
#define TRI_H

#include "triangle.h"
#include "object.h"

class Tri: public Object
{
    Vec3 pos;
    double size;
    Triangle t;
public:
    Tri();
    Tri(const Tri& t);
    Tri(const Vec3& pos, Material* mat, double size);

    virtual bool hit(const Ray& ray, PoI& poi) override;

    inline void print() const {

        Vec3 n = t.getNormal();
        printf("%f\t%f\t%f\n", n.x, n.y, n.z);
    }

    inline const Vec3& getPosition() {

        return pos;
    }
};

#endif // TRI_H
