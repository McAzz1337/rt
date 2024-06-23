#include "poi.h"

PoI::PoI() {}

void PoI::adjust(const Vec3& point, double lambda, const Vec3& normal, Object* object) {

    this->point = point;
    this->lambda = lambda;
    this->normal = normal;
    this->object = object;

    exists = true;
}
