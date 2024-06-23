#include "quad.h"
#include "math/mat4.h"

Quad::Quad() {}
Quad::Quad(const Quad& q): Object(q.position, q.mat), a(q.a), b(q.b), size(q.size) {

}

Quad::Quad(const Vec3& pos, Material* mat, double size): Object(pos, mat), size(size) {

    Mat4 m;
    m.translate(pos);

    double h = 0.5 * size;
    a = Triangle(
        m * Vec3( h,  h, 0),
        m * Vec3(-h,  h, 0 ),
        m * Vec3(-h, -h, 0 )
        );

    b = Triangle(
        m * Vec3( h,  h, 0 ),
        m * Vec3(-h, -h, 0 ),
        m * Vec3( h, -h, 0 )
        );
}

bool Quad::hit(const Ray& ray, PoI& poi)  {

    double lambda = pow(62, 2);
    bool hit = false;

    if (a.hit(ray, poi) && poi.lambda < lambda) {

        lambda = poi.lambda;
        hit = true;
    }

    if (b.hit(ray, poi) && poi.lambda < lambda) {

        lambda = poi.lambda;
        hit = true;
    }

    if (hit) {

        poi.object = this;
        return true;
    }

    return false;
}
