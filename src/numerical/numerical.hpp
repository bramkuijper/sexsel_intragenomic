#ifndef _NUMERICAL_HPP_
#define _NUMERICAL_HPP_

#include <iostream>
#include <fstream>
#include <sstream>
#include "parameters.hpp"

class SexSelIntra
{
    public:

        Parameters params;

        std::ofstream data_file;
        
        // default constructor
        SexSelIntra(Parameters const &parms);

        void run();
};

#endif
