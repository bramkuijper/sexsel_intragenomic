#ifndef _NUMERICAL_HPP_
#define _NUMERICAL_HPP_

#include <iostream>
#include <fstream>
#include <sstream>
#include "parameters.hpp"

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

class SexSelIntra
{
    private:

        // reproductive values
        double v[2]{1.0,1.0};

        // stable class frequencies
        double u[2]{0.5,0.5};

        // calculate equilibrium values of the 
        // reproductive values and relatedness
        void ecological_equilibrium();

        double wff();
        double wfm();
        double wmf();
        double wmm();

    public:

        Parameters params;

        std::ofstream data_file;
        
        // default constructor
        SexSelIntra(Parameters const &parms);

        // run the actual simulation
        void run();
        
};

#endif
