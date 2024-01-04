library("tidyverse")
library("pracma")

# vary ornament
t <- linspace(0,5,50)
q <- c(0,1)
bg <- c(0.01, 0.1, 0.5)

all.data <- as_tibble(expand.grid(t=t,q=q,bg=bg))

cs <- 0.1
k <- 1 

cost.function <- function(t, q, b)
{
    
    return(b + (1.0 - b) * (1.0 - exp(-cs * t * t / (1.0 + k * q))))    
}

#results <- apply(X=all.data, MARGIN = 1, FUN = cost.function)
all.data <- mutate(all.data, 
       cost=cost.function(t,q, bg),
       qf=as_factor(q))


ggplot(data=all.data
       ,mapping=aes(x=t,y=cost)) +
    geom_line(mapping=aes(colour=qf)) +
    theme_classic() +
    xlab("Ornament size, t") +
    ylab("Mortality probability") +
    facet_grid(~bg)

ggsave(filename = "plot_cost_function.pdf")

