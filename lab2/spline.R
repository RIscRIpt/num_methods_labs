#!/usr/bin/env Rscript

args <- commandArgs(trailingOnly=TRUE)
outputFile <- args[1]

stdin <- file("stdin", "r")
splines <- invisible(read.table(stdin))
stopifnot(length(splines) == 5)
colnames(splines) <- c("x", "a", "b", "c", "d")

xs <- splines[, "x"]
ys <- splines[, "a"]

xlim <- c(xs[1], xs[length(xs)])
ylim <- c(min(ys), max(ys))

png(outputFile)
plot(0, type='n', axes=TRUE, ann=FALSE, xlim=xlim, ylim=ylim)
points(xs, ys, col="red", pch=19)

for (i in 1:(nrow(splines) - 1)) {
    x_left <- splines[i, "x"]
    x_right <- splines[i + 1, "x"]
    a <- splines[i, "a"]
    b <- splines[i, "b"]
    c <- splines[i, "c"]
    d <- splines[i, "d"]
    spline <- function(x) { a + b * (x - x_left) + c * (x - x_left)^2 + d * (x - x_left)^3 }
    curve(spline, from=x_left, to=x_right, col="blue", add=TRUE)
}

invisible(dev.off())

