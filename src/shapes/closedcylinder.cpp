#include "closedcylinder.h"

#include "math/mat4.h"

ClosedCylinder::ClosedCylinder() {}

ClosedCylinder::ClosedCylinder(const ClosedCylinder& c) : Object(c.position, c.mat), c(c.c), top(c.top), bottom(c.bottom) {}

ClosedCylinder::ClosedCylinder(const Vec3& pos, Material* mat, double radius, double height)
    : Object(pos, mat), c(pos, radius, height), top(pos, radius, {0, -1, 0}) {

    Vec3 p = Vec3(pos.x, pos.y + height, pos.z);
    bottom = Disc(p, radius, {0, 1, 0});
}

bool ClosedCylinder::hit(const Ray& ray, PoI& poi) {

    double lambda = pow(2, 63);
    bool hit = false;
    if (c.hit(ray, poi) && poi.lambda < lambda) {

        lambda = poi.lambda;
        hit = true;
    }

    if (top.hit(ray, poi) && poi.lambda < lambda) {

        lambda = poi.lambda;
        hit = true;
    }

    if (bottom.hit(ray, poi) && poi.lambda < lambda) {

        lambda = poi.lambda;
        hit = true;
    }

    if (hit) {

        poi.object = this;
    }

    return hit;
}
