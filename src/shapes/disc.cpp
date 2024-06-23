#include "disc.h"

Disc::Disc() {}

Disc::Disc(const Disc& d): Object(d.position, d.mat), radius(d.radius), normal(d.normal) {
}

Disc::Disc(const Vec3& pos, double radius, const Vec3& normal): radius(radius), normal(normal) {

    position = pos;
    aggregated = true;
}

Disc::Disc(const Vec3& pos, Material* mat, double radius, const Vec3& normal)
    : Object(pos, mat), radius(radius), normal(normal) {

}

bool Disc::hit(const Ray& ray, PoI& poi) {

    double d = dot (ray.dir, normal);
    if (d > 0) //WTF
        return false;

    double lambda = dot (position - ray.origin, normal) / d;
    if ((poi.exists && lambda >= poi.lambda) || lambda < 1e-6)
        return false;

    Vec3 c = ray.point(lambda);

    if ((c - position).length() < radius) {

        if (aggregated) {
            poi.point = c;
            poi.lambda = lambda;
            poi.normal = normal;
            poi.exists = true;
        }
        else {

            poi.adjust(c, lambda, normal, this);
        }

        return true;
    }

    return false;
}

