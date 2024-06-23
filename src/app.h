
#include "thrd.h"
#include "rgb.h"

#include <optional>

#include "shapes/sphere.h"
#include "shapes/tri.h"
#include "shapes/piramid.h"
#include "shapes/cylinder.h"
#include "shapes/closedcylinder.h"
#include "shapes/star.h"
#include "shapes/crystal.h"
#include "shapes/disc.h"
#include "shapes/quad.h"
#include "lights/light.h"
#include "scene/scene.h"
#include "models/model.h"

class App : public Thrd {

    static constexpr int MAX_BOUNCES = 2;
    RGB white, red, green, blue, magenta, teal, darkGray;

    Scene scene;

    double depth;
    Sphere sphere1;
    Sphere sphere2;
    Sphere sphere3;

    Light* light;
    Vec3 focus;

    Tri tri;
    Piramid pir;
    Cylinder cyl;
    ClosedCylinder cc;
    Star star;
    Crystal crys;
    Disc disc;
    Quad q1;
    Quad q2;
    Quad q3;
    Quad q4;
    Model model;

    std::vector<Object*> objects;
    std::vector<Light*> lights;

    virtual void Initialize() override;
    RGB trace(const Ray& ray, PoI& poi, int iter, Object* ignore = nullptr);
    virtual RGB ComputePixel(int x, int y) override;
    virtual void EndOfImage() override;
    bool isInShadow(const PoI& poi, Object* ignore = nullptr);

    Vec3 refract(const Vec3& incident, const Vec3& normal, double refractiveIndexRatio);
    std::optional<Ray> refractRay(const Ray& incidentRay, const PoI& poi, double refractiveIndexRatio);
};
