#!/usr/bin/env Rscript

library(deSolve)

pow <- function(b, e) {
    return(b^e)
}

args <- commandArgs(trailingOnly=TRUE)

func <- eval(parse(text=paste("function(t, y, params) with(params, list(", args[1], "))")))

output <- args[2]
if (is.na(output) || output == '') {
    output <- "plot.png"
}

stdin <- file("stdin", "r")
data <- read.table(stdin)

left  <- data[1, 1]
right <- data[nrow(data), 1]
start <- data[1, 2]

png(output, width=900, height=600)

plot(data, type='l', lty=1, col='blue', xlab="t", ylab="y")

real <- ode(start, seq(left, right, (right - left) / 1e5), func, list())
lines(real, lty=2, col='red')

invisible(dev.off())

