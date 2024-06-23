#include "triangle.h"

Triangle::Triangle() {}

Triangle::Triangle(const Triangle& t): a(t.a), b(t.b), c(t.c), position(t.position) {

}

Triangle::Triangle(const Vec3& a, const Vec3& b,const Vec3& c): a(a), b(b), c(c) {

    position = (a + b + c) / 3.0;
}



bool Triangle::hit(const Ray& ray, PoI& poi) {

    Vec3 edge1 = b - a;
    Vec3 edge2 = c - a;
    Vec3 normal = cross(edge1, edge2).normalized();

    double divisor = dot(normal, ray.dir);

    if (std::abs(divisor) < 1e-6) {

        return false;
    }

    double lambda = dot(normal, a - ray.origin) / divisor;

    if (lambda < 1e-6 || (poi.exists && lambda >= poi.lambda)) {

        return false;
    }

    Vec3 intersectionPoint = ray.point(lambda);

    Vec3 vp0 = intersectionPoint - a;
    Vec3 vp1 = intersectionPoint - b;
    //Vec3 vp2 = intersectionPoint - c;

    double d00 = dot(edge1, edge1);
    double d01 = dot(edge1, edge2);
    double d11 = dot(edge2, edge2);
    double d20 = dot(vp0, edge1);
    double d21 = dot(vp1, edge2);
    double denom = d00 * d11 - d01 * d01;
    double v = (d11 * d20 - d01 * d21) / denom;
    double w = (d00 * d21 - d01 * d20) / denom;
    double u = 1.0 - v - w;

    if (v >= 0 && w >= 0 && u >= 0 && u + v <= 1) {

        poi.adjust(intersectionPoint, lambda, normal, nullptr);
        return true;
    }

    return false;
}

Vec3 Triangle::getNormal() const {

    Vec3 normal = cross(b - a, c - a).normalized();
    normal.z = -normal.z;
    normal.y = -normal.y;
    normal.x = -normal.x;

    return normal;
}
