#include "piramid.h"

#include "math/mat4.h"

#define _USE_MATH_DEFINES
#include <math.h>

Piramid::Piramid() {}

Piramid::Piramid(const Piramid& p): Object(p.position, p.mat) {

    memcpy_s(this->tris, 6 * sizeof(Triangle), tris, 6 * sizeof(Triangle));
}

Piramid::Piramid(const Vec3& pos, Material* mat, double side, double height): Object(pos, mat) {

    Mat4 m;
    m.rotate({0.0, 1.0, 0.0}, M_PI * 0.25);
    m.translate(pos);

    double hs = 0.5 * side;
    double hh = 0.5 * height;
    //Front
    tris[0] = Triangle(
        m * Vec3( hs,  hh, -hs),
        m * Vec3(-hs,  hh, -hs),
        m * Vec3(  0, -hh,   0)
    );
    //Back
    tris[1] = Triangle(
        m * Vec3(-hs,  hh,  hs),
        m * Vec3( hs,  hh,  hs),
        m * Vec3(  0, -hh,   0)
    );
    //Left
    tris[2] = Triangle(
        m * Vec3(-hs,  hh, -hs),
        m * Vec3(-hs,  hh,  hs),
        m * Vec3(  0, -hh,   0)
    );
    //Right
    tris[3] = Triangle(
        m * Vec3( hs,  hh,  hs),
        m * Vec3( hs,  hh, -hs),
        m * Vec3(  0, -hh,   0)
    );
    //Bottom
    tris[4] = Triangle(
        m * Vec3( hs,  hh,  hs),
        m * Vec3(-hs,  hh,  hs),
        m * Vec3(-hs,  hh, -hs)
    );
    tris[5] = Triangle(
        m * Vec3( hs,  hh,  hs),
        m * Vec3(-hs,  hh, -hs),
        m * Vec3( hs,  hh, -hs)
    );

}

bool Piramid::hit(const Ray& ray, PoI& poi) {

    double l = pow(2, 63);
    int index;
    bool hit = false;

    for (int i = 0; i < TRI_COUNT; ++i) {

        if (tris[i].hit(ray, poi) && poi.lambda < l) {

            hit = true;
            l = poi.lambda;
            index = i;
        }
    }

    if (hit) {

        poi.adjust(ray.point(l), l, tris[index].getNormal(), this);
        return true;
    }

    return false;
}
