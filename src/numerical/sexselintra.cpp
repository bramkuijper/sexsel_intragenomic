#include <string>
#include <iostream>
#include <cmath>
#include <cassert>
#include <vector>
#include "sexselintra.hpp"
#include "parameters.hpp"

SexSelIntra::SexSelIntra(Parameters const &parms) :
    params{parms}
    ,data_file(parms.filename.c_str())
    ,t{params.t_init}
    ,tpr{params.tpr_init}
    ,ornament{t, t + tpr}
    ,p{params.p_init}
{
    for (unsigned i = 0; i <= params.n[male]; ++i)
    {
        for (unsigned k = 0; k <= params.n[male]; ++k)
        {
            std::cout << "nnewh: " << i << " kvacant: " << k << " z: " << z(i,k) << std::endl;
        }
    }
}

// https://www.geeksforgeeks.org/binomial-coefficient-dp-9/
// calculate a semi-optimal version of a binomial coefficient
// we could use boost libraries too, but too much of a pain if this 
// works too

// Function to find binomial 
// coefficient
int binomialCoeff(int n, int r)
{
 
    if (r > n)
        return 0;
    long long int m = 1000000007;
    long long int inv[r + 1];
    for (long int r_i = 0; r_i < r+1; ++r_i)
    {
        inv[r_i] = 0;
    }
    inv[0] = 1;
    if(r+1>=2)
    inv[1] = 1;
 
    // Getting the modular inversion
    // for all the numbers
    // from 2 to r with respect to m
    // here m = 1000000007
    for (int i = 2; i <= r; i++) {
        inv[i] = m - (m / i) * inv[m % i] % m;
    }
 
    int ans = 1;
 
    // for 1/(r!) part
    for (int i = 2; i <= r; i++) {
        ans = ((ans % m) * (inv[i] % m)) % m;
    }
 
    // for (n)*(n-1)*(n-2)*...*(n-r+1) part
    for (int i = n; i >= (n - r + 1); i--) {
        ans = ((ans % m) * (i % m)) % m;
    }
    return ans;
} // end binomialCoefficient

// mortality rate of a female with preference p
double SexSelIntra::mu_f(double const p)
{
    return(params.bg_mort[female] + 
                (1.0 - params.bg_mort[female]) * 
                (1.0 - std::exp(-params.cp * std::pow(p, params.gammap)))
            );
}

// mortality rate of a male with ornament s and quality x
double SexSelIntra::mu_m(double const s, Quality const q)
{
    double quality = static_cast<double>(q);
    // see eq. (2a) in Iwasa & Pomiankowski (1999) JTB
    // todo:build in baseline mortality
    return(params.bg_mort[male] + 
                (1.0 - params.bg_mort[male]) * 
                (1.0 - std::exp(-params.cs * s * s/(1.0 + params.ks * quality)))
          );
}

// probability that out of nvacant breeding positions
// a number of nnewh will be usurped by high-quality males
double SexSelIntra::z(unsigned const nnewh
    ,unsigned const nvacant)
{
    assert(nvacant >= 0);
    assert(nnewh >= 0);

    return(
            binomialCoeff(nvacant, nnewh) *
                std::pow(params.bh, nnewh) *
                std::pow(1.0 - params.bh, nvacant - nnewh)
          );
} // end z()

// probability that k mortalities take place
// among the nm_q male breeders of quality q
double SexSelIntra::y(unsigned const k
        ,Quality const q
        ,unsigned const nm_q)
{
    return(
            binomialCoeff(nm_q, k) * 
                std::pow(mu_m(ornament[hq], q), k) * 
                    std::pow(1.0 - mu_m(ornament[lq], q), nm_q - k)
          );
}

double SexSelIntra::xfocf(unsigned const nh_t, 
        unsigned const nh_tplus1, 
        Quality const q)
{
    double val{0.0};
    

} // xfoc



// probability that a patch which currently contains
// nh_t high-quality males will contain 
// nh_tplus1 high-quality males in the next time step
double SexSelIntra::x(
        unsigned const nh_t
        ,unsigned const nh_tplus1)
{
    double val{0.0};

    assert(params.n[male] - nh_t >= 0);
    assert(nh_t >= 0);
    assert(nh_tplus1 >= 0);
    assert(nh_t < params.n[male]);

    // go through 
    for (unsigned k = 0; k <= nh_t; ++k)
    {
        for (unsigned j = 0; j <= params.n[male] - nh_t; ++j)
        {
            val += y(k, hq, nh_t) * 
                y(j, lq, params.n[male] - nh_t) * 
                z(nh_tplus1 - nh_t - k, k + j);
        }
    }

    return(val);
} //  end x
        

// resident transition probabilities from female to female
// from a patch with nh_t hiqh-quality males 
// to a patch with nh_tplus1 high-quality males
double SexSelIntra::wff(
        unsigned const nh_t, 
        unsigned const nh_tplus1)
{
    double val{0.0};

    val += x(nh_t, nh_tplus1) * (
            (1.0 - mu_f(p))
             + 0.25 * (1.0 - params.d[female]) * mu_f(p) 
            );

    // note re the latter term of 0.25 * (1.0 - params.d[female]) * mu_f(p) 
    // this is, shorthand for 0.25 * (1.0 - params.d[female]) * mu_f(p) * f(p) / ((1-df) * f(p) + df * f(p))   

    double sum_remote_frequencies{0.0};

    for (unsigned nu_h_tau = 0; 
            nu_h_tau <= params.n[male]; ++nu_h_tau)
    {
        sum_remote_frequencies += u[nu_h_tau] * x(nu_h_tau, nh_tplus1);
    }

    val += 0.25 * params.d[male] * sum_remote_frequencies * mu_f(p);

    return(val);
} // end wff

double wfmh(unsigned const nh_t
        ,unsigned const nh_tplus1)
{
    double val{0.0};

    val += 0.0;

} // end wfmh

// calculate equilibrium values of the 
// reproductive values and relatedness
void SexSelIntra::ecological_equilibrium()
{
    double vftplus1, vmtplus1, umtplus1, uftplus1;

    for (unsigned ecol_time_step = 0; 
            ecol_time_step < params.max_ecol_time; ++ecol_time_step)
    {
    }
}

// function to update the resident
// ornament values after each generation
void SexSelIntra::update_ornament()
{
    ornament[0] = t + tpr * static_cast<double>(lq);
    ornament[1] = t + tpr * static_cast<double>(hq);
}

void SexSelIntra::run()
{
    for (unsigned time_step = 0; time_step < params.max_time; ++time_step)
    {
        update_ornament();
        ecological_equilibrium();
    }
}
