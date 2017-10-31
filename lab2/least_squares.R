#!/usr/bin/env Rscript

library(polynom)

args <- commandArgs(trailingOnly=TRUE)
outputFile <- args[1]

stdin <- file("stdin", "r")

n_points <- scan(stdin, what=numeric(0), n=1, quiet=TRUE)
xs <- c()
ys <- c()
for (i in 1:n_points) {
    xs <- append(xs, scan(stdin, what=numeric(0), n=1, quiet=TRUE))
    ys <- append(ys, scan(stdin, what=numeric(0), n=1, quiet=TRUE))
}

xlim   <- c(xs[1], xs[length(xs)])
ylim   <- c(min(ys), max(ys))
xamp   <- xlim[2] - xlim[1]
yamp   <- ylim[2] - ylim[1]
liminc <- 0.1
xlim   <- c(xlim[1] - xamp * liminc, xlim[2] + xamp * liminc)
ylim   <- c(ylim[1] - yamp * liminc, ylim[2] + yamp * liminc)

coefs <- scan(stdin, quiet=TRUE)

png(outputFile, width=900, height=600)

polyfx <- as.function(polynomial(coefs))

plot(0, type='n', axes=TRUE, ann=FALSE, xlim=xlim, ylim=ylim)
curve(polyfx, from=xlim[1], to=xlim[2], add=TRUE)
points(xs, ys, col="red", pch=19)

invisible(dev.off())

