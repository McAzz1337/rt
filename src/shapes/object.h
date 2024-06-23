#ifndef OBJECT_H
#define OBJECT_H


#include "math/ray.h"
#include "surface/material.h"
#include "surface/srr.h"
#include "poi/poi.h"

class Object
{

protected:
    Vec3 position;
    Material* mat = nullptr;
    SRR srr;

public:
    Object() = default;
    Object(const Vec3& position, Material* mat);
    virtual ~Object();

    virtual bool hit(const Ray& ray, PoI& poi) = 0;

    inline const Vec3& getPosition() const {

        return position;
    }
    
    inline Material* getMaterial() const {

        return mat;
    }

    inline SRR& getSRR() {

        return srr;
    }

};

#endif // OBJECT_H
