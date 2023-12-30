#include <string>
#include "sexselintra.hpp"
#include "parameters.hpp"

SexSelIntra::SexSelIntra(Parameters const &parms) :
    params{parms}
    ,data_file(parms.filename.c_str())
{}

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
    long long int inv[r + 1] = { 0 };
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

// probability that k mortalities take place
// among the nm_x male breeders of quality x
double SexSelIntra::y(unsigned k, Quality x, unsigned nm_x)
{
    return(
            binomialCoeff(nm_x, k) * std::pow(mu_m[x], k) * std::pow(1.0 - mu_m[x], nm_x - k)
          );
}

// probability that out of nvacant breeding positions
// a number of nnewh will be usurped by high-quality males
double SexSelIntra::z(unsigned nnewh, unsigned nvacant)
{

} // end z()

// probability that a patch which currently contains
// nh_t high-quality males will contain 
// nh_tplus1 high-quality males in the next time step
void SexSelIntra::fill_x(
        unsigned const nh_t
        ,unsigned const nh_tplus1)
{
    double val{0.0};

    assert(n - nh_t >= 0);
    assert(nh_t >= 0);
    assert(nh_t < n);

    for (unsigned k = 0; k < nh_t; ++k)
    {
        for (unsigned j = 0; j < n - nh_t; ++j)
        {
            val += y(k, HQ, nh_t) * y(j, LQ, n - nh_t) * z(
        }
    }

    x[nh_t, nh_tplus1] = val;
} //  end x
        

// resident transition probabilities from female to female
// from a patch with nh_t hiqh-quality males 
// to a patch with nh_tplus1 high-quality males
double SexSelIntra::wff(
        unsigned const nh_t, 
        unsigned const nh_tplus1)
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
