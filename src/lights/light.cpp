#include "light.h"

Light::Light(const Vec3& position): position(position) {

}

Light::Light(const Light& l): position(l.position) {

}
