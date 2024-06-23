#include "model.h"
#include "../load/objparser.h"

Model::Model(): Object() {}

Model::Model(const Vec3& pos, const std::string& path): Object(pos, Material::materials["jade"]) {

    loadFromFile(path);
    //printf("tringles: %i\n", triangles.size());


    Mat4 m;
    m.translate(pos);

    for (Triangle& t : triangles) {

        t.translate(m);
    }

}

bool Model::loadFromFile(const std::string& path) {

    return loadOBJ(path, triangles);
}

bool Model::hit(const Ray& ray, PoI& poi) {


    bool hit_anything = false;
    for (Triangle& triangle : triangles) {

        if (triangle.hit(ray, poi)) {

            hit_anything = true;
        }
    }

    if (hit_anything) {

        poi.object = this;
    }

    return hit_anything;
}
