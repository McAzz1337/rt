#include "scene.h"

Scene::Scene() {}

void Scene::add(Object* o) {

    objects.push_back(o);
}

void Scene::hit(const Ray& ray, PoI& poi, bool shortCuircuit, Object* ignore) {

    for (Object* o : objects) {

        if (o == ignore) continue;

        o->hit(ray, poi);

        if (shortCuircuit && poi.exists) {

            break;
        }
    }
}
