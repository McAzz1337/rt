#include "spotlight.h"

SpotLight::SpotLight(const Vec3& position, const Vec3& direction, double angle, double fadeAngle)
    : Light(position), direction(direction), angle(angle * 0.5), fadeAngle(fadeAngle) {


    v = Vec3(0, sin(this->angle), cos(this->angle));
}

SpotLight::SpotLight(const SpotLight& l): Light(l.position), direction(l.direction), angle(l.angle), fadeAngle(l.fadeAngle), v(l.v) {

}

double SpotLight::intensity(const Vec3& point, const Vec3& normal, double ambient) const  {

    Vec3 toPoint = (point - position).normalized();

    double d = dot(toPoint, direction);
    double i = 0;
    if (d > dot(direction, v)) {

        i = dot(-toPoint, normal);
    }
    else {

        i = fmax(d, ambient);
    }
    return i;
}

bool SpotLight::inLight(const Vec3& point, const Vec3& normal) const  {

    Vec3 toPoint = (point - position).normalized();

    double d = dot(toPoint, direction);
    if (d > dot(direction, v)) {

        return false;
    }

    return true;
}
