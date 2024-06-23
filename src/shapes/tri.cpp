#include "tri.h"

#include "math/mat4.h"

#define _USE_MATH_DEFINES
#include <math.h>

Tri::Tri(): Object() {
}

Tri::Tri(const Tri& t): Tri(t.pos, t.mat,  t.size) {}

Tri::Tri(const Vec3& pos, Material* mat, double size)
    : Object(pos, mat), pos(pos), size(size) {

    Mat4 m;
    //m.rotate({0, 1, 0}, -M_PI * 0.25 * 0.5);
    m.translate(pos);

    double h = 0.5 * size;
    t = Triangle(
        m * Vec3( h,  h, 0),
        m * Vec3(-h,  h, 0),
        m * Vec3( 0, -h, 0)
    );
}

bool Tri::hit(const Ray& ray, PoI& poi) {

    double l = poi.exists ? poi.lambda :  pow(2, 63);
    if (t.hit(ray, poi) && poi.lambda < l) {

        poi.object = this;
        return true;
    }

    return false;
}
