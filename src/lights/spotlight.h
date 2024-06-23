#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include "light.h"

struct SpotLight: public Light
{

    Vec3 direction;
    double angle;
    double fadeAngle;
    Vec3 v;

public:
    SpotLight(const Vec3& position, const Vec3& direction, double angle, double fadeAngle);
    SpotLight(const SpotLight& l);

    virtual double intensity(const Vec3& point, const Vec3& normal, double ambient) const override;
    virtual bool inLight(const Vec3& point, const Vec3& normal) const override;
};

#endif // SPOTLIGHT_H
