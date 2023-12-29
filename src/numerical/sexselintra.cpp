#include <string>
#include "sexselintra.hpp"
#include "parameters.hpp"

SexSelIntra::SexSelIntra(Parameters const &parms) :
    params{parms}
    ,data_file(parms.filename.c_str())
{}

double SexSelIntra::wff()
{
    double val{1.0 - mu(p)};

    val += 0.25 * (1.0 - params.d[female]) * 


    return(val);
}

// calculate equilibrium values of the 
// reproductive values and relatedness
void SexSelIntra::ecological_equilibrium()
{
    double vftplus1, vmtplus1, umtplus1, uftplus1;

    for (unsigned ecol_time_step = 0; 
            ecol_time_step < params.max_ecol_time; ++ecol_time_step)
    {
        vftplus1
    }
}

void SexSelIntra::run()
{
    for (unsigned time_step = 0; time_step < params.max_time; ++time_step)
    {
        ecological_equilibrium();
    }
}
