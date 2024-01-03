#ifndef _NUMERICAL_HPP_
#define _NUMERICAL_HPP_

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "parameters.hpp"

// enums for Quality, Sex and Control are in parameters.hpp

class SexSelIntra
{

    public:

        Parameters params;

        std::ofstream data_file;
        
        // default constructor
        SexSelIntra(Parameters const &parms);

        // run the actual simulation
        void run();
        
    private:

        double t{0.0}; // the resident value of the baseline ornament value
        double tpr{0.0}; // the resident value of the ornament-quality coefficient
        double ornament[2]{0.0,0.0}; // the resident value of the total ornament value for low and hhigh quality males
        double p{0.0}; // the resident value of the preference

        // function to update the resident
        // ornament values after each generation
        void update_ornament(); 

        Control control_t{offspring}; // genetic control over t 
        Control control_p{offspring};  // genetic control over p

        // male reproductive values
        // consisting of vm[j][k] where index j reflects
        // the number of other high-quality males in the patch
        // and the index k reflects whether the focal male is
        // high quality themselves
        std::vector < std::vector < double > > vm;

        // female reproductive values
        // only a function of the number of males in a local patch
        std::vector < double > vf;

        // patch frequencies
        // i.e., the patches containing nh_t high-quality males
        std::vector <double> u;

        // calculate equilibrium values of the 
        // reproductive values and relatedness
        void ecological_equilibrium();

        double wff(unsigned const nh_t, unsigned const nh_tplus1);
        double wfmh(unsigned const nh_t, unsigned const nh_tplus1);
        double wfml(unsigned const nh_t, unsigned const nh_tplus1);
        double wmf();
        double wmm();

        // probability that a patch which currently contains
        // nh_t high-quality males will contain 
        // nh_tplus1 high-quality males in the next time step
        double x(unsigned const nh_t
                ,unsigned const nh_tplus1);

        // probability that k mortalities take place
        // among the nm_x male breeders of quality x
        double y(unsigned const k
                ,Quality const q
                ,unsigned const nm_x);

        // probability that out of nvacant breeding positions
        // a number of nnewh will be usurped by high-quality males
        double z(unsigned const nnewh, 
                unsigned const nvacant);

        // focal female's contribution to a patch which currently contains
        // nh_t high-quality males and will contain 
        // nh_tplus1 high-quality males in the next time step
        double xfocf(unsigned const nh_t
                ,unsigned const nh_tplus1
                ,Quality const q);

        // mortality rate of a male of quality x
        double mu_m(
                double const ornament
                ,Quality const q);

        // mortality of a female with preference p
        double mu_f(double const pref);
};

#endif
