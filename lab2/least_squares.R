#!/usr/bin/env Rscript

library(polynom)

stdin <- file("stdin")
open(stdin)
line <- readLines(stdin, n=1)
coefs <- scan(text=line)

png("least_squares.png")
plot(polynomial(coefs))
dev.off()

