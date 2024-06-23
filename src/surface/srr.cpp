#include "srr.h"

double SRR::refraction_values[RefractionIndex::NONE];

SRR::SRR()  {

}

SRR::SRR(double shading, double refraction, double reflection)
    : shading(shading), refraction(refraction), reflection(reflection) {

}

void SRR::buildFlag(char& flag) const {

    if (shading >= 1e-6) flag |= SHADING_FLAG;
    if (refraction >= 1e-6) flag |= REFRACTION_FLAG;
    if (reflection >= 1e-6) flag |= REFLECTION_FLAG;
}

bool SRR::filterFlag(const char& flag, int comp) const {


    return (flag & comp) > 0;
}

void SRR::init() {

    SRR::refraction_values[RefractionIndex::VACUME] = 1;
    SRR::refraction_values[RefractionIndex::HELIUM] = 1.000034911;
    SRR::refraction_values[RefractionIndex::AIR] = 1.000292;
    SRR::refraction_values[RefractionIndex::ICE] = 1.31;
    SRR::refraction_values[RefractionIndex::WATER] = 1.333;
    SRR::refraction_values[RefractionIndex::HUMAN_EYE_LENSE] = 1.39;
    SRR::refraction_values[RefractionIndex::ETHANOL] = 1.3614;
    SRR::refraction_values[RefractionIndex::QUART_GLASS] = 1.46;
    SRR::refraction_values[RefractionIndex::CRON_GLASS] = 1.54;
    SRR::refraction_values[RefractionIndex::WINDOW_GLASS] = 1.52;
    SRR::refraction_values[RefractionIndex::PLASTIC_GLASS] = 1.76;
    SRR::refraction_values[RefractionIndex::MINERAL_GLASS] = 1.0;
    SRR::refraction_values[RefractionIndex::GLASS] = 2.0;
    SRR::refraction_values[RefractionIndex::DIAMOND] = 2.42;
}













