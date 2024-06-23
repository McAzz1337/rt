#include "material_t.h"


Matr::Matr(): Matr({1.0, 1.0, 1.0}, {1.0, 1.0, 1.0}, {1.0, 1.0, 1.0}, 1.0, 1.0, 1.0) {}


Matr::Matr(const Matr& m): Matr(m.ambient, m.diffuse, m.specular, m.shininess, m.refraction, m.shading) {}

Matr::Matr(const Vec3& ambient, const Vec3& diffuse, const Vec3& specular, double shininess, double refraction, double shading)
    : ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess), refraction(refraction), shading(shading) {}
