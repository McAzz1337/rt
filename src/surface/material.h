#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>
#include <unordered_map>

#include "math/vec3.h"

struct Material
{

    static std::unordered_map<std::string, Material*> materials;


    std::string name;

    double ambientIntensity;
    Vec3 diffuse;
    Vec3 specular;
    double shininess;
    double refraction;
    double shading;

    Material();
    Material(const Material& m);
    Material(const std::string& name, const Vec3& ambient, const Vec3& diffuse, const Vec3& specular, double shininess, double refraction, double shading);


    static void init();
};

#endif // MATERIAL_H
