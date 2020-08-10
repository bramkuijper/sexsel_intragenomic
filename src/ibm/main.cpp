#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cassert>
#include <random>
#include <unistd.h>
#include <yaml-cpp/yaml.h>
#include "individual.hpp"

// the main part of the code
int main(int argc, char **argv)
{
    // variable storing the name of the yaml parameter file
    std::string yaml_file{};
/* 
    // first
    int opt;

    std::stringstream usage;
    
    usage << "Usage of this programme: " << argv[0] << " -f location_of_yaml_parameter_file.yaml" << std::endl;

    while ((opt = getopt(argc, argv, "f:")) != -1) 
    {
        if (opt == 'f')
        {
            yaml_file = optarg;
        }
        else
        {
            std::cerr << usage.str();

            exit(EXIT_FAILURE);
        }
    } // end while

    if (argc < 2)
    {
        std::cerr << usage.str();
        exit(EXIT_FAILURE);
    }

    init_pars_from_yaml(yaml_file);

//    init_pars_from_cmd(argc, argv);
    // ok parameters initialized, now lets do some work

    // initialize output files
    std::ofstream data_file(file_basename + ".csv");

    // write headers to the data file
    write_stats_headers(data_file);

    initialize_population();

    for (int generation_idx = 0; generation_idx < max_generations; ++generation_idx)
    {
        mate_produce_offspring();
        adult_mortality_replacement();

        if (generation_idx % skip == 0)
        {
            write_stats_per_timestep(generation_idx, data_file);
        }
    }

    write_parameters(data_file);
}
