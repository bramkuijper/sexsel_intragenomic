#include <string>
#include "numerical.hpp"
#include "parameters.hpp"

// default constructor accepting a parameter object
SexSelIntra::SexSelIntra(Parameters const &parms) :
    params{parms}
    ,data_file(parms.filename.c_str())
{}

void SexSelIntra::run()
{
    for (
}
