#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "shapes/object.h"

class Scene
{


    std::vector<Object*> objects;

public:
    Scene();

    void add(Object* o);

    void hit(const Ray& ray, PoI& poi, bool shortCuircuit = false, Object* ignore = nullptr);

};

#endif // SCENE_H
