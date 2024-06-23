#include "star.h"

#include "math/mat4.h"
#include "qmath.h"

Star::Star() {}

Star::Star(const Star& s): Star(s.position, s.mat, s.triSize) {

}

Star::Star(const Vec3 pos, Material* mat, double triSize)
    : Object(pos, mat), triSize(triSize) {

    Mat4 model;
    model.translate(pos);

    double h = 0.5 * triSize;
    double size = triSize * 1.15;
    Triangle t = Triangle(
        Vec3( h,  h,  -h),
        Vec3(-h,  h,  -h),
        Vec3( 0, -h,  0)
        );
    //top front
    {
        Mat4 m;
        m.translate({0, -size, 0});

        tris[0] = Triangle(
            model * m * t[0],
            model * m * t[1],
            model * m * t[2]
            );
    }
    //left fornt
    {
        Mat4 m;
        m.translate({0, -size,  0});
        model.rotate({0, 0, 1}, -M_PI * 0.4);

        tris[1] = Triangle(
            model * m * t[0],
            model * m * t[1],
            model * m * t[2]
            );
    }
    //left bottom fornt
    {
        Mat4 m;
        m.translate({0, -size, 0});
        model.rotate({0, 0, 1}, -M_PI * 0.8);

        tris[2] = Triangle(
            model * m * t[0],
            model * m * t[1],
            model * m * t[2]
            );
    }
    //right bottom fornt
    {
        Mat4 m;
        m.translate({0, -size, 0});
        model.rotate({0, 0, 1}, -M_PI * 1.2);

        tris[3] = Triangle(
            model * m * t[0],
            model * m * t[1],
            model * m * t[2]
            );
    }
    //right
    {
        Mat4 m;
        m.translate({0, -size, 0});
        model.rotate({0, 0, 1}, -M_PI * 1.6);

        tris[4] = Triangle(
            model * m * t[0],
            model * m * t[1],
            model * m * t[2]
            );
    }

    //mid
    tris[5] = Triangle(
        tris[0][0],
        tris[2][1],
        tris[0][1]
        );

    //mid left
    tris[6] = Triangle(
        tris[0][1],
        tris[2][1],
        tris[1][1]
        );

    tris[7] = Triangle(
       tris[2][1],
        tris[0][0],
        tris[3][1]
        );

    Mat4 rot;
    rot.rotate({0, 1, 0}, M_PI);
    int half = TRI_COUNT * 0.5;
    for (int i = half + 1; i < TRI_COUNT; ++i) {

        tris[i] = Triangle(
            rot * tris[(int) (i - half)][0],
            rot * tris[(int) (i - half)][1],
            rot * tris[(int) (i - half)][2]
            );
    }
}


bool Star::hit(const Ray& ray, PoI& poi) {

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
