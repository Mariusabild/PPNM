# Examination project by Marius Abildgaard Brødbæk
s
Author: Marius Abildgaard Brødbæk
Studienummer: 202308011
Examination project: One-sided Jacobi algorithm for Singular Value Decomposition (index number 19)
Link: 

Link to my github repo: https://github.com/Mariusabild/PPNM

# Task description 
from https://fedorov.sdfeu.org/prog/projex/svd-one-sided.htm

## Introduction
The singular value decomposition (SVD) of a (real square, for simplicity) matrix A is a representation of the matrix in the form
A = U D VT ,

where matrix D is diagonal with non-negative elements and matrices U and V are orghogonal. The diagonal elements of matrix D can always be chosen non-negative by multiplying the relevant columns of matrix U with (-1).
SVD can be used to solve a number of problems in linear algebra.

Problem
Implement the one-sided Jacobi SVD algorithm.

Algorithm
In this method the elementary iteration is given as
A → A J(θ,p,q)

where the indices (p,q) are swept cyclicly (p=1..n, q=p+1..n) and where the angle θ is chosen such that the columns number p and q of the matrix AJ(θ,p,q) are orthogonal. One can show that the angle should be taken from the following equation (you should use atan2 function),
tan(2θ)=2apTaq /(aqTaq - apTap)

where ai is the i-th column of matrix A (check this).
After the iterations converge and the matrix A'=AJ (where J is the accumulation of the individual rotations) has orthogonal columns, the SVD is simply given as

A=UDVT

where
V=J, Dii=||a'i||, ui=a'i/||a'i||,

where a'i is the i-th column of matrix A' and ui us the i-th column of matrix U.

# Proof/check of formula for theta


