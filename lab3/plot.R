#!/usr/bin/env Rscript

pow <- function(b, e) {
    return(b^e)
}

args <- commandArgs(trailingOnly=TRUE)

func <- eval(parse(text=paste("function(x) { return(", args[1], ") }")))
left <- eval(parse(text=args[2]))
right <- eval(parse(text=args[3]))
output <- args[4]
if (is.na(output) || output == '') {
    output <- "plot.png"
}

stdin <- file("stdin", "r")
roots <- scan(stdin, quiet=TRUE)

png(output, width=900, height=600)

curve(func, left, right, ylab=args[1], n=1001)
points(roots, func(roots), pch=19, col="red")
abline(h=0, col="gray")
abline(v=roots, col="gray")
invisible(dev.off())

