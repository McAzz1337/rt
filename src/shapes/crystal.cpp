#include "crystal.h"

#include "math/mat4.h"
#include "qmath.h"

Crystal::Crystal() {}

Crystal::Crystal(const Crystal& c)
    : Object(c.position, c.mat), radius(c.radius), baseHeight(c.baseHeight), pointHeight(c.pointHeight) {

    memcpy_s(tris, TRI_COUNT * sizeof(Triangle), c.tris, TRI_COUNT * sizeof(Triangle));
}

Crystal::Crystal(const Vec3& pos, Material* mat, double radius, double baseHeight, double pointHeight)
    : Object(pos, mat), baseHeight(baseHeight), pointHeight(pointHeight) {

    Mat4 m;
    m.rotate({0, 1, 0}, M_PI * 0.2);
    m.translate(pos);

    double cosa = cos(0);
    double cosb = cos(M_PI * 0.4);
    double sina = sin(0);
    double sinb = sin(M_PI * 0.4);
    tris[0] = Triangle(
        m * Vec3(cosb * radius, 0, sinb * radius),
        m * Vec3(cosa * radius, 0, sina * radius),
        m * Vec3(cosa * radius, -baseHeight, sina * radius)
        );

    tris[1] = Triangle(
        m * Vec3(cosb * radius, 0, sinb * radius),
        m * Vec3(cosa * radius, -baseHeight, sina * radius),
        m * Vec3(cosb * radius, -baseHeight, sinb * radius)
        );

    cosa = cos(M_PI * 0.4);
    cosb = cos(M_PI * 0.8);
    sina = sin(M_PI * 0.4);
    sinb = sin(M_PI * 0.8);
    tris[2] = Triangle(
        m * Vec3(cosb * radius, 0, sinb * radius),
        m * Vec3(cosa * radius, 0, sina * radius),
        m * Vec3(cosa * radius, -baseHeight, sina * radius)
        );

    tris[3] = Triangle(
        m * Vec3(cosb * radius, 0, sinb * radius),
        m * Vec3(cosa * radius, -baseHeight, sina * radius),
        m * Vec3(cosb * radius, -baseHeight, sinb * radius)
        );


    cosa = cos(M_PI * 0.8);
    cosb = cos(M_PI * 1.2);
    sina = sin(M_PI * 0.8);
    sinb = sin(M_PI * 1.2);
    tris[4] = Triangle(
        m * Vec3(cosb * radius, 0, sinb * radius),
        m * Vec3(cosa * radius, 0, sina * radius),
        m * Vec3(cosa * radius, -baseHeight, sina * radius)
        );

    tris[5] = Triangle(
        m * Vec3(cosb * radius, 0, sinb * radius),
        m * Vec3(cosa * radius, -baseHeight, sina * radius),
        m * Vec3(cosb * radius, -baseHeight, sinb * radius)
        );


    cosa = cos(M_PI * 1.2);
    cosb = cos(M_PI * 1.6);
    sina = sin(M_PI * 1.2);
    sinb = sin(M_PI * 1.6);
    tris[6] = Triangle(
        m * Vec3(cosb * radius, 0, sinb * radius),
        m * Vec3(cosa * radius, 0, sina * radius),
        m * Vec3(cosa * radius, -baseHeight, sina * radius)
        );

    tris[7] = Triangle(
        m * Vec3(cosb * radius, 0, sinb * radius),
        m * Vec3(cosa * radius, -baseHeight, sina * radius),
        m * Vec3(cosb * radius, -baseHeight, sinb * radius)
        );


    cosa = cos(M_PI * 1.6);
    cosb = cos(0);
    sina = sin(M_PI * 1.6);
    sinb = sin(0);
    tris[8] = Triangle(
        m * Vec3(cosb * radius, 0, sinb * radius),
        m * Vec3(cosa * radius, 0, sina * radius),
        m * Vec3(cosa * radius, -baseHeight, sina * radius)
        );

    tris[9] = Triangle(
        m * Vec3(cosb * radius, 0, sinb * radius),
        m * Vec3(cosa * radius, -baseHeight, sina * radius),
        m * Vec3(cosb * radius, -baseHeight, sinb * radius)
        );


    int j = 1;
    int k = 0;
    for (int i = 10; i < 15; ++i) {

        tris[i] = Triangle(
            tris[j][2],
            tris[j][1],
            m * Vec3(0, -baseHeight - pointHeight, 0)
            );
        j += 2;

        tris[i + 5] = Triangle(
            m * Vec3(0, pointHeight, 0),
            tris[k][1],
            tris[k][0]
            );

        k += 2;
    }

    /*
    j = 0;
    for (int i = 15; i < TRI_COUNT; ++i) {
        tris[i] = Triangle(
            tris[j][0],  // Use the bottom right vertex of the current triangle
            tris[j][1],  // Use the bottom left vertex of the current triangle
            m * Vec3(0, pointHeight, 0)  // Use the specified top vertex
            );
        j += 2;
    }
    */
}



bool Crystal::hit(const Ray& ray, PoI& poi) {

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
