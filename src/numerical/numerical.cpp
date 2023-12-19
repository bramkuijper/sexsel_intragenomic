#include <string>
#include "numerical.hpp"
#include "parameters.hpp"

SexSelIntra::SexSelIntra(Parameters const &parms) :
    params{parms}
    ,data_file(parms.filename.c_str())
{}

void SexSelIntra::run()
{

}
