#include "sphere.h"

#include <cmath>

Sphere::Sphere() {}



Sphere::Sphere(const Sphere& s): Object(s.position, s.mat),  radius(s.radius) {


}

Sphere::Sphere(const Vec3& center, double radius, Material* mat)
    : Object(center, mat),  radius(radius)  {}

bool Sphere::hit(const Ray& ray, PoI& poi) {


    Vec3 v = ray.origin - position;

    double a = dot(ray.dir, ray.dir);
    double b = 2 * dot(ray.dir, v);
    double c = dot(v, v) - radius * radius;

    double d = b * b - 4 * a * c;

    if (d < 1e-6) {

        return false;
    }

    double pos = (-b + sqrt(d)) / (2 * a);
    double neg = (-b - sqrt(d)) / (2 * a);
    double lambda = neg < 1e-6 ? pos : neg;
    //-b - sqrt(d / 2 * a);
    if ((poi.exists && lambda >= poi.lambda) || lambda <= 1e-6)
        return false;


    Vec3 point = ray.point(lambda);
    poi.adjust(point, lambda, (point - position).normalized(), this);
    return true;
}
