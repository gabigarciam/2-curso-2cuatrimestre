#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
L3 Ex3b
"""
import numpy as np
from L3_ex1 import horner
np.set_printoptions(suppress = True)

def polDer(x0,p):
    n = len(p)
    d = np.zeros_like(p)
    c = np.copy(p)
    factorial = 1.
    for i in range(n):
        c, d[i] = horner(x0,c)
        d[i] *= factorial
        factorial *= i+1
    return d
#%%
p = np.array([1., -1, 2, -3,  5, -2])
x0 = 1.

print('Derivadas sucesivas de P en x0 = 1')        
d0 = polDer(x0,p)
print(d0)

r = np.array([1., -1, -1, 1, -1, 0, -1, 1])
x1 = -1.

print('\nDerivadas sucesivas de R en x1 = -1')        
d1 = polDer(x1,r)
print(d1)