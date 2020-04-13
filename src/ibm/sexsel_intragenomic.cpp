// sexual selection in a spatially structured population
// assessing the scope for intragenomic conflict
//


#include <iostream>
#include <ostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cassert>
#include <random>


// set up the random number generator using a good way of getting random seed
std::random_device rd;
unsigned seed = rd();
std::mt19937 rng_r(seed);
std::uniform_real_distribution<> uniform(0.0,1.0);

// parameters
int const nm_max = 10; // max males per patch
int const nf_max = 10; // max females per patch
int const clutch_max = 50; // maximum clutch size
int const n_patches = 5000; // maximum number patches

int nm = 5; // actual number of males/patch
int nf = 5; // actual number of females/patch
double init_t = 0.0; // initial value of baseline ornament
double init_p = 0.0; // initial value of preference
double init_tprime = 0.0; // initial value of ornament cond-dep 
double p_high = 0.0; // prob male is high quality
double l = 0.0; // probability female mates locally

// declare an individual
// with evolvable genetic loci
// and nonevolving traits determining
// condition
struct Individual {

    // baseline ornament investment
    double t[2];

    // quality-dependent ornament investment
    double tprime[2];

    // preference locus, where p = 0 means random mating
    double p[2];

    // total size of the ornament
    double s;
    
    bool envt_quality_high;
};

// an individual patch of the metapopulation
struct Patch {

    Individual breedersF[nf_max];
    Individual breedersM[nm_max];
    
    Individual phil_juvsF[nf_max * clutch_max];
    Individual phil_juvsM[nf_max * clutch_max];
};

// create a metapopulation of patches
Patch meta_population[n_patches];

// initialize the population by creating individuals
// and assigning them traits
void initialize_population()
{
    for (int patch_idx = 0; patch_idx < n_patches; ++patch_idx)
    {
        for (int female_idx = 0; female_idx < nf; ++female_idx)
        {
            for (int allele_idx = 0; allele_idx < 2; ++allele_idx)
            {
                meta_population[patch_idx].breedersF[female_idx].t[allele_idx] = init_t;
                meta_population[patch_idx].breedersF[female_idx].p[allele_idx] = init_p;
                meta_population[patch_idx].breedersF[female_idx].tprime[allele_idx] = init_tprime;
            }

        }
        
        for (int male_idx = 0; male_idx < nm; ++male_idx)
        {
            for (int allele_idx = 0; allele_idx < 2; ++allele_idx)
            {
                meta_population[patch_idx].breedersM[male_idx].t[allele_idx] = init_t;
                meta_population[patch_idx].breedersM[male_idx].p[allele_idx] = init_p;
                meta_population[patch_idx].breedersM[male_idx].tprime[allele_idx] = init_tprime;
            }

            meta_population[patch_idx].breedersM[male_idx].envt_quality_high = 
                uniform(rng_r) < p_high;
        }
    }
} // end initialize_population()

// function to write parameters 
// as a two column table
// to file data_file
void write_parameters(std::ofstream &data_file)
{
    data_file << 
        std::endl << 
        std::endl <<
        "p_high;" << p_high << std::endl <<
        "init_tprime;" << init_tprime << std::endl <<
        "init_t;" << init_t << std::endl <<
        "init_p;" << init_p << std::endl <<
        "seed;" << seed << std::endl <<
        "nm;" << nm << std::endl <<
        "nf;" << nf << std::endl <<
        std::endl;
}

// write statistics to file data_file
void write_stats_per_timestep(int time_step, std::ofstream &data_file)
{
    double mean_t = 0.0;
    double mean_tprime = 0.0;
    double mean_p = 0.0;
    double ss_t = 0.0;
    double ss_tprime = 0.0;
    double ss_p = 0.0;

    double z;

    for (int patch_idx = 0; patch_idx < n_patches; ++patch_idx)
    {
        for (int female_idx = 0; female_idx < nf; ++female_idx)
        {
            for (int allele_idx = 0; allele_idx < 2; ++allele_idx)
            {
                z = meta_population[patch_idx].breedersF[female_idx].t[allele_idx];
                mean_t += z;
                ss_t += z * z;

                z = meta_population[patch_idx].breedersF[female_idx].p[allele_idx];
                mean_p += z;
                ss_p += z * z;

                z = meta_population[patch_idx].breedersF[female_idx].tprime[allele_idx];
                mean_tprime += z;
                ss_tprime += z * z;
            }
        }
        
        for (int male_idx = 0; male_idx < nm; ++male_idx)
        {
            for (int allele_idx = 0; allele_idx < 2; ++allele_idx)
            {
                z = meta_population[patch_idx].breedersM[male_idx].t[allele_idx];
                mean_t += z;
                ss_t += z * z;

                z = meta_population[patch_idx].breedersM[male_idx].p[allele_idx];
                mean_p += z;
                ss_p += z * z;

                z = meta_population[patch_idx].breedersM[male_idx].tprime[allele_idx];
                mean_tprime += z;
                ss_tprime += z * z;
            }
        }
    } // end for (int patch_idx

    mean_t /= (nm + nf) * n_patches;
    mean_p /= (nm + nf) * n_patches;
    mean_tprime /= (nm + nf) * n_patches;

    double var_t = ss_t / ((nm + nf) * n_patches) - mean_t * mean_t;
    double var_p = ss_p / ((nm + nf) * n_patches) - mean_p * mean_p;
    double var_tprime = ss_tprime / ((nm + nf) * n_patches) - mean_tprime * mean_tprime;

    data_file << time_step << ";"
        << mean_t <<  ";"
        << mean_p <<  ";"
        << mean_tprime <<  ";"
        << var_t <<  ";"
        << var_p <<  ";"
        << var_tprime <<  ";" << std::endl;
} // end void write_stats_per_timestep()

// survive dependent on ornament size
void mate_produce_offspring()
{
    for (int patch_idx = 0; patch_idx < n_patches; ++patch_idx)
    {
        for (int female_idx = 0; female_idx < nf; ++female_idx)
        {
            for (int egg_i = 0; egg_i < clutch_max; ++egg_i)
            {
                // choose mate


            }

        }
    }
}



int main(int argc, char **argv)
{

    return(0);
}
