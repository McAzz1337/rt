#ifndef SRR_H
#define SRR_H

#define SHADING_FLAG 1
#define REFLECTION_FLAG 2
#define REFRACTION_FLAG 4

enum RefractionIndex {

    VACUME,
    HELIUM,
    AIR,
    ICE,
    WATER,
    HUMAN_EYE_LENSE,
    ETHANOL,
    QUART_GLASS,
    CRON_GLASS,
    WINDOW_GLASS,
    PLASTIC_GLASS,
    MINERAL_GLASS,
    GLASS,
    DIAMOND,
    NONE
};


struct SRR
{
    static double refraction_values[RefractionIndex::NONE];

    double shading = 1;
    double refraction = 0;
    double reflection = 0;

    SRR();
    SRR(double shading, double refraction, double reflection);

    void buildFlag(char& flag) const;
    bool filterFlag(const char& flag, int comp) const;

    static void init();
};

#endif // SRR_H
