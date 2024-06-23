#include "app.h"


#include "poi/poi.h"
#include "lights/pointlight.h"
#include "lights/spotlight.h"
#include "math/mat4.h"

#include "surface/material.h"
#include "models/model.h"


RegisterThrd(App);


void App::Initialize() {

    Material::init();
    SRR::init();

    white = RGB(1, 1, 1);
    red = RGB(1, 0, 0);
    green = RGB(0, 1, 0);
    blue = RGB(0, 0, 1);
    magenta = RGB(1, 0, 1);
    teal = RGB(0, 1, 1);
    darkGray = RGB(0.1, 0.1, 0.1);

    depth = fmin(width(), height());
    Vec3 pos(width() * 0.5, height() * 0.5, 0);
    light = new PointLight({width() * 0.4, height() * 0.5, depth * 0.2});

    focus = Vec3(0.5 * width(), 0.5 * height(), -0.1);
/*
    tri = Tri({width() * 0.7, height() * 0.15, depth * 0.35}, Material::materials["glass"],  depth * 0.5);
    tri.getSRR().refraction = 1;

    pir = Piramid({width() * 0.5, height() * 0.8, depth * 0.5}, Material::materials["ruby"], width() * 0.3, height() * 0.45);
    pir.getSRR().reflection = 1;
    {
        Vec3 dir = depth * 0.6 * reflect((focus - pir[3].getPosition()).normalized(), pir[3].getNormal());
        Vec3 p = pir.getPosition();
        cc = ClosedCylinder(p + dir, Material::materials["obsidian"], width() * 0.15, height() * 0.25);
        cc.getSRR().reflection = 1;

        dir = depth * 0.5 * reflect((focus - pir[0].getPosition()).normalized(), pir[0].getNormal()) + Vec3(0, 100, -100);
        dir = dir + Vec3(0, 300, 0);
        crys = Crystal(p + dir, Material::materials["pearl"], depth * 0.1, depth * 0.5, depth * 0.2);
        crys.getSRR().reflection = 1;
    }
    {
        Vec3 center = tri.getPosition() + Vec3(depth * 0.1, 0, depth);
        double size = 400;
        double h = 0.5 * size;
        q1 = Quad({center.x - h, center.y - h, center.x}, Material::materials["pearl"], size);
        q2 = Quad({center.x + h, center.y - h, center.x}, Material::materials["obsidian"], size);
        q3 = Quad({center.x - h, center.y + h, center.x}, Material::materials["ruby"], size);
        q4 = Quad({center.x + h, center.y + h, center.x}, Material::materials["brass"], size);
    }


    sphere1 = Sphere(
        {width() * 0.2, height() * 0.1, depth * 0.5},
        depth * 0.15,
        Material::materials["jade"]
        );

    scene.add(&tri);
    scene.add(&sphere1);
    scene.add(&pir);
    scene.add(&cc);
    scene.add(&q1);
    scene.add(&q2);
    scene.add(&q3);
    scene.add(&q4);
    scene.add(&crys);
*/


    model = Model(pos, "D:/HSLU/FS_24/Ray Tracing/Ta/Test/models/cube.obj");
    scene.add(&model);
}


RGB App::trace(const Ray& ray, PoI& poi, int iter, Object* ignore) {

    if (iter >= MAX_BOUNCES) return RGB(0.3, 0.3, 0.3);

    scene.hit(ray, poi);

    if (poi.exists) {

        //return RGB(1, 1, 1);
        SRR& srr = poi.object->getSRR();
        Material* mat = poi.object->getMaterial();
        RGB shadingColor(0, 0, 0);
        RGB refractionColor(0, 0, 0);
        RGB reflectionColor(0, 0, 0);

        char flag = 0;
        srr.buildFlag(flag);

        double i = 1;
        if (srr.filterFlag(flag, SHADING_FLAG)) {

            i = isInShadow(poi, poi.object) ?
                0:
                light->intensity(poi.point, poi.normal, mat->ambientIntensity);

            shadingColor = mat->diffuse * i;
        }

        if (srr.filterFlag(flag, REFLECTION_FLAG)) {

            Ray reflected(poi.point, reflect(-ray.dir.normalized(), poi.normal));
            PoI next;
            reflectionColor = trace(reflected, next, iter + 1) * mat->shininess;

        }
        else if (srr.filterFlag(flag, REFRACTION_FLAG)) {

            std::optional<Ray> refracted = refractRay(ray, poi, SRR::refraction_values[RefractionIndex::ICE]);
            if (refracted.has_value()) {

                PoI next;
                refractionColor = trace(refracted.value(), next, iter + 1);
                shadingColor = shadingColor * 0.5;
            }
        }

        return shadingColor + reflectionColor + refractionColor;
    }

    return RGB(0.3, 0.3, 0.3);
}

RGB App::ComputePixel(int x, int y) {

    Vec3 pix = Vec3((double) x, (double) y, 0);

    PoI poi;
    Ray ray(pix, pix - focus);

    return trace(ray, poi, 0);
}

void App::EndOfImage()  {

}

bool App::isInShadow(const PoI& poi, Object* ignore) {


    if (!light->inLight(poi.point, poi.normal))
        return false;

    Ray ray(poi.point, (light->position - poi.point).normalized());
    PoI lightHit;
    scene.hit(ray, lightHit, false, ignore);

    if (lightHit.exists) {

        if ((lightHit.lambda * ray.dir).length() < (light->position - poi.point).length()) {

            return true;
        }
    }

    return false;
}


Vec3 App::refract(const Vec3& incident, const Vec3& normal, double refractiveIndexRatio) {
    double cosTheta = dot(-incident, normal);
    double sinThetaSquared = 1.0 - refractiveIndexRatio * refractiveIndexRatio * (1.0 - cosTheta * cosTheta);

    if (sinThetaSquared < 0.0) {
        return Vec3(0.0, 0.0, 0.0); // Total internal reflection, no refracted ray
    }

    return refractiveIndexRatio * incident + (refractiveIndexRatio * cosTheta - sqrt(sinThetaSquared)) * normal;
}

std::optional<Ray> App::refractRay(const Ray& incidentRay, const PoI& poi, double refractiveIndexRatio) {
    Vec3 incidentDir = incidentRay.dir.normalized();
    Vec3 normal = poi.normal.normalized();

    Vec3 refractedDir = refract(incidentDir, normal, refractiveIndexRatio);

    if (refractedDir == Vec3(0.0, 0.0, 0.0)) {

        return {};
    }

    Ray refractedRay(poi.point, refractedDir);


    return refractedRay;
}


