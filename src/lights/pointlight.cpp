#include "pointlight.h"

PointLight::PointLight(const Vec3& position): Light(position) {

}

PointLight::PointLight(const PointLight& l): Light(l.position) {

}

double PointLight::intensity(const Vec3& point, const Vec3& normal, double ambient) const  {

    Vec3 toLight = (position - point).normalized();


    return fmax(dot(toLight, normal), ambient);
}

bool PointLight::inLight(const Vec3& point, const Vec3& normal) const  {

    return dot((position - point).normalized(), normal) > 1e-6;
}

