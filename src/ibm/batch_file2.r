library("simulation.utils")

params <- list()

params$nm <- seq(2,10,1)
params$init_t <- 0.01
params$init_p <- 0.05
params$init_tprime <- 0.1
params$p_high <- 0.5
params$dm <- 0.8
params$df <- 0.2
params$base_surv <- 0.02
params$base_mort <- 0.02
params$a <- c(2)
params$cp <- 0.01
params$cs <- 0.01
params$k <- 0.5
params$fl <- 0.1
params$fh <- 1.0
params$control_t <- seq(0,4,1)
#params$control_p <- seq(0,4,1)
params$control_p <- 0
#params$control_tprime <- seq(0,4,1)
params$control_tprime <- 0
params$mu_t <- 0.02
params$mu_p <- 0.02
params$mu_tprime <- 0.02
params$sdmu_t <- 0.1
params$sdmu_p <- 0.1
params$sdmu_tprime <- 0.1
params$max_generations <- 50000
params$clutch_max <- 50


# make filenames with date and time, to prevent previous-run overwrites
timestamp.now <- format(Sys.time(),format="%Y%m%d_%H%M%S")

# expand all parameter combinations to one data frame
all_params = as.data.frame(expand.grid(params))

# rather than vary nf and nm independently, we 
# focus on a scenario where nf is high and nm low
# and vice versa. Hence, if nm = 10, nf = 1
# if nm = 1, nf = 10 and all values in between:
all_params["nf"] <- 12 - all_params["nm"]

# finally, we keep population size constant
# and only vary the number of patches, which
# decrease the more inhabitants there are
all_params["n_patches"] <- round(5000 / all_params$nf)


#setwd("/Users/bram/Projects/sexsel_intragenomic/src/ibm" )

# make the batch file
make.batch.file.yaml(
  parameter_list = all_params
  ,executable_path = "./sexsel_intragenomic.exe"
  ,n_replicates = 3
  ,output_file_yaml_key = "file_basename"
  ,yaml_file_prefix=paste0("parameters",timestamp.now,"_")
  ,output_file_prefix=paste0("output_",timestamp.now,"_")
)

