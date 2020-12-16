library("simulation.utils")

params <- list()

params$nm <- seq(1,10,1)
params$init_t <- 0.01
params$init_p <- 0.2
params$init_tprime <- 0.01
params$p_high <- 0.2
params$dm <- 0.2
params$df <- 0.2
params$base_surv <- 0.0
params$base_mort <- 0.0
params$a <- c(0,1)
params$cp <- 0.1
params$cs <- 0.5
params$k <- 0.5
params$fl <- 0.9
params$fh <- 1.0
params$control_t <- seq(0,4,1)
params$control_p <- 0
params$control_tprime <- 0
params$mu_t <- 0.01
params$mu_p <- 0.01
params$mu_tprime <- 0.01
params$sdmu_t <- 0.01
params$sdmu_p <- 0.01
params$sdmu_tprime <- 0.01
params$max_generations <- 500
params$clutch_max <- 50

# expand all parameter combinations to one data frame
all_params = as.data.frame(expand.grid(params))

all_params["n_patches"] <- 8000 / all_params$nf  

# rather than vary nf and nm independently, we 
# focus on a scenario where nf is high and nm low
# and vice versa. Hence, if nm = 10, nf = 1
# if nm = 1, nf = 10 and all values in between:
all_params["nf"] <- 11 - all_params["nm"]

#setwd("/Users/bram/Projects/sexsel_intragenomic/src/ibm" )

# make the batch file
make.batch.file.yaml(
  parameter_list = all_params
  ,executable_path = "./sexsel_intragenomic.exe"
  ,n_replicates = 3
  ,output_file_yaml_key = "file_basename"
)

