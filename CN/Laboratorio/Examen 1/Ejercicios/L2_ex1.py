# -*- coding: utf-8 -*-
"""
L2 Ex1
"""
import numpy as np

f = lambda x: np.exp(x)
x0 = - 0.4
tol = 1.e-8
maxNumSum = 100

polynomial = 0.
factorial = 1.
term = np.inf
i = 0

while np.abs(term) > tol and i < maxNumSum:
    term = x0**i/factorial
    polynomial += term
    factorial *= i+1
    i += 1

print('Function value in -0.4      = ', f(x0))
print('Approximation value in -0.4 = ', polynomial)
print('Number of iterations        = ', i)

