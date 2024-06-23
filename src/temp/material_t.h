#ifndef MATR_H
#define MATR_H

#include "math/vec3.h"

struct Matr
{

    Vec3 ambient;
    Vec3 diffuse;
    Vec3 specular;
    double shininess;
    double refraction;
    double shading;

    Matr();
    Matr(const Matr& m);
    Matr(const Vec3& ambient, const Vec3& diffuse, const Vec3& specular, double shininess, double refraction, double shading);

    inline void operator=(const Matr& m) {

        ambient = m.ambient;
        diffuse = m.diffuse;
        specular = m.specular;
        shininess = m.shininess;
        refraction = m.refraction;
    }

};

#endif // MATERIAL_H
