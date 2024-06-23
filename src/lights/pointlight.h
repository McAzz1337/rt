#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "light.h"

struct PointLight: public Light
{
public:
    PointLight(const Vec3& position);
    PointLight(const PointLight& l);

    virtual double intensity(const Vec3& point, const Vec3& normal, double ambient) const override;
    virtual bool inLight(const Vec3& point, const Vec3& normal) const override;

};

#endif // POINTLIGHT_H
