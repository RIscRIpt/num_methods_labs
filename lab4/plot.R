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

real <- ode(start, seq(left, right, (right - left) / 1e5), func, list())

png(output, width=900, height=600)
par(mfrow=c(1, 2))

plot(x=real[,1], y=real[,2], type='l', lty=2, lwd=3, col='red', xlab='t', ylab='y')
lines(data, lty=1, col='blue')

real.trimmed <- approx(real[,1], real[,2], xout=data[,1])$y

err.ylim <- min(100, max(abs(head(real.trimmed - data[,2], -1))))
plot(x=head(data[,1], -1), y=head(data[,2]-real.trimmed, -1), type='l', lty=1, xlab="t", ylab="delta y", ylim=c(-err.ylim, err.ylim))

invisible(dev.off())

