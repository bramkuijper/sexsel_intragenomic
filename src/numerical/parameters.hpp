#ifndef _PARAMETERS_HPP_
#define _PARAMETERS_HPP_

#include <string>

enum Sex
{
    female = 0,
    male = 1
};

enum Quality
{
    lq = 0,
    hq = 1
};

// enum spelling out genetic control
enum Control
{
    offspring = 0,
    mother = 1,
    father = 2,
    maternal_allele = 3,
    paternal_allele = 4
};

// parameter object
class Parameters
{
    public:
        unsigned int n[2]{5,5}; // patch size, first entry female
        unsigned int max_time{100};
        unsigned int max_ecol_time{10'000};

        // the c coefficient in eq. (2a) of Iwasa & Pomiankowski 1999 JTB
        double cs{0.1};
        // the k coefficient in eq. (2a) of Iwasa & Pomiankowski 1999 JTB
        double ks{0.1};

        // background mortality for males and females
        double bg_mort[2]{0.05,0.05};

        // the cost coefficient of a female pref in the eq. of Wf on p100 
        // of Iwasa & Pomiankowski 1999 JTB
        double cp{0.01};
        double gammap{2.0};

        // probability that a male offspring becomes high quality
        double bh{0.5};

        // dispersal, d[0] = df (female), d[1] = dm (male)
        double d[2]{0.1,0.8};

        // fecundity values of matings with 
        // low and high quality males
        double fec[2]{1.0,1.0};

        double t_init{3.0};
        double p_init{3.0};
        double tpr_init{0.0};

        std::string filename{"iter_sexsel_intra"};
};

#endif
