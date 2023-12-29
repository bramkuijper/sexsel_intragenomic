#ifndef _PARAMETERS_HPP_
#define _PARAMETERS_HPP_

#include <string>

class Parameters
{
    public:
        unsigned int n{2};
        unsigned int max_time{100};
        unsigned int max_ecol_time{10'000};

        // dispersal, d[0] = df (female), d[1] = dm (male)
        double d[2]{0.1,0.8};

        // fecundity values of matings with 
        // low and high quality males
        double k[2]

        std::string filename{"iter_sexsel_intra"};
};

#endif
