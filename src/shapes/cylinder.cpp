#include "cylinder.h"

Cylinder::Cylinder() {}

Cylinder::Cylinder(const Vec3& pos, double radius, double height) : radius(radius), height(height) {

    position = pos;
    aggregated = true;
}

Cylinder::Cylinder(const Cylinder& c): Object(c.position, c.mat), radius(c.radius), height(c.height) {}

Cylinder::Cylinder(const Vec3& pos, Material* mat, double radius, double height)
    : Object(pos, mat), radius(radius), height(height) {

    }

    bool Cylinder::hit(const Ray& ray, PoI& poi)  {


        Vec3 v = ray.origin - position;
        Vec3 dir = ray.dir;

        double a = dir.x * dir.x + dir.z * dir.z;
        double b = 2.0 * (v.x * dir.x + v.z * dir.z);
        double c = v.x * v.x + v.z * v.z - radius * radius;

        double d = b * b - 4 * a * c;

        if (d > 0) {

            double root = sqrt(d);
            double neg = (-b - root) / (2 * a);
            double pos = (-b + root) / (2 * a);
            double lambda = neg < 1e-6 ?pos : neg;

            if (poi.exists && lambda > poi.lambda)
                return false;

            double y_min = position.y;
            double y_max = position.y + height;

            Vec3 point = ray.point(lambda);

            if (point.y < y_min || point.y > y_max)
                return false;

            Vec3 n = (Vec3(point.x, 0, point.z) - Vec3(position.x, 0, position.z)).normalized();
            if (aggregated) {

                poi.point = point;
                poi.lambda = lambda;
                poi.normal = n;//(point - position).normalized(),
                poi.exists = true;
            }
            else {

                poi.adjust(point,
                           lambda,
                           n,//(point - position).normalized(),
                           this);
            }

            return true;
        }


        return false;
    }
