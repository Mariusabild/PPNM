# Examination project by Marius Abildgaard Brødbæk

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

From  equation (13) in the book https://fedorov.sdfeu.org/prog/book/eigen.pdf 

a_p' = c*a_p - s*a_q
a_q' = s*a_p + c*a_q

Which are the collums after a Jacobi rotation.

We require these to be orthogornal after a rotation:

(a_p')^T*a_q' = 0

We insert our expressions which yields:

(c*a_p - s*a_q)^T*(s*a_p + c*a_q) = 0

Now we can expand and rearrange:

(c^2 -s^2)*a_p^Ta_q+c*s*(a_p^T*a_p - a_q^Ta_q) = 0

Now we can use the trigonometric identities:

c^2-s^2=cos(2*theta)
2*c*s= sin(2*theta)

This yields:

cos(2*theta)*a_p^Ta_q+1/2*sin(2*theta)(a_p^T*a_p - a_q^Ta_q) = 0

Divide by cos(2*theta) to obtain:

a_p^Ta_q+1/2*sin(2*theta)/cos(2*theta)*(a_p^T*a_p - a_q^Ta_q) = 0

Use the definition of tan(theta) = sin(theta)/cos(theta), and isolate tan(2*theta):

a_p^Ta_q+1/2*tan(2*theta)*(a_p^T*a_p - a_q^Ta_q) = 0

Rearrange:

tan(2*theta) = -2*(a_p^Ta_q)/(a_p^T*a_p - a_q^Ta_q)

Multiply by -1:

tan(2*theta) = 2*(a_p^Ta_q)/(a_q^T*a_q - a_p^Ta_p)

# Implementation of code