#include "elipse.h"

Elipse::Elipse() {}

Elipse::Elipse(const Elipse& e): Object(e.position, e.mat),  radiusA(e.radiusA), radiusB(e.radiusB) {

}

Elipse::Elipse(const Vec3& position, Material* mat, double radiusA, double radiusB)
    : Object(position, mat),  radiusA(radiusA), radiusB(radiusB) {

}

bool Elipse::hit(const Ray& ray, PoI& poi) {

    Vec3 v = ray.origin - position;

    double a = dot(ray.dir, ray.dir);
    double b = 2 * dot(ray.dir, v);
    double c = dot(v, v) - pow(radiusA, 2.0) - pow(radiusB, 2.0);

    double d = b * b - 4 * a * c;

    if (d < 1e-6) {

        return false;
    }

    double pos = (-b + sqrt(d)) / (2 * a);
    double neg = (-b - sqrt(d)) / (2 * a);
    double lambda = neg < 1e-6 ? pos : neg;

    Vec3 point = ray.point(lambda);


    Vec3 normal = (position - point).normalized();
    //normal.x /= (radiusA * radiusA);
    //normal.y /= (radiusB * radiusB);



    poi.adjust(point, lambda, normal, this);
    return true;
}
