#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>
#include "../shapes/triangle.h"
#include "../shapes/object.h"
#include "../math/vec3.h"
#include "../math/mat4.h"

class Model: public Object {

    std::vector<Triangle> triangles;

public:
    Model();
    Model(const Vec3& pos, const std::string& path);
    bool loadFromFile(const std::string& path);

    virtual bool hit(const Ray& ray, PoI& poi) override;
};


#endif // MODEL_H
