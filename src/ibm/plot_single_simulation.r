#!/usr/bin/env Rscript 

#--vanilla

library("ggplot2")
library("gridExtra")

# get command line arguments
args = commandArgs(trailingOnly=TRUE)

# give an error message if you do not provide it with a simulation file name
if (length(args) < 1)
{
    print("provide a simulation file name")
    stop()
}

# find out where the parameter listing starts
# so that we can read in the data part of the file 
# without having it messed up by the subsequent parameter listing
find_out_param_line <- function(filename) {

    f <- readLines(filename)

    # make a reverse sequence
    seqq <- seq(length(f),1,-1)

    # go through each line in the data file and find first line
    # where data is printed (i.e., a line which starts with a digit)
    for (line_i in seqq)
    {
        print(f[[line_i]])
        print(line_i)
        if (length(grep("^\\d",f[[line_i]])) > 0)
        {
            return(line_i)
        }
    }

    return(NA)
}

parameter_row <- find_out_param_line(args[1])

if (is.na(parameter_row))
{
    print("cannot find data...")
    stop()
}

# read in data frame of corresponding simulation
the.data <- read.table(args[1], header=T, nrow=parameter_row - 1, sep=";")

# now use ggplot2 to plot stuff

str(the.data)

p1.a <- ggplot(data=the.data
        ,aes(x=generation)) +
            geom_line(aes(y = t, colour="t")) +
            theme_classic() + 
            xlab("Generation") + 
            ylab("t")

p1.b <- ggplot(data=the.data
        ,aes(x=generation)) +
            geom_line(aes(y = tprime, colour="tprime")) +
            theme_classic() + 
            xlab("Generation") + 
            ylab("tprime")

p2 <- ggplot(data=the.data
        ,aes(x=generation)) +
            geom_line(aes(y = p, colour="preference")) +
            theme_classic() + 
            xlab("Generation") + 
            ylab("preference")


big_plot <- arrangeGrob(p1.a, p1.b, p2, nrow=3,ncol=1)
the.base.name <- basename(args[1])

output_file_name <- paste(
        "graph_"
        ,the.base.name
        ,".pdf"
        ,sep="")

ggsave(output_file_name, big_plot, height = 25)

