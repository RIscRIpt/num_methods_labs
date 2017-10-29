#!/usr/bin/env Rscript

library(polynom)
args <- commandArgs(trailingOnly=TRUE)
outputFile <- args[1]
stdin <- file("stdin")
coefs <- scan(stdin, quiet=TRUE)
png(outputFile)
plot(polynomial(coefs))
invisible(dev.off())

