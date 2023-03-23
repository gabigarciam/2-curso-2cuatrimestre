#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
L3 Ex3a
"""
import numpy as np
from L3_ex1 import horner

def polDer(x0,p):
    n = len(p)
    d = np.zeros_like(p)
    c = np.copy(p)
    for i in range(n):
        c, d[i] = horner(x0,c)
    return d
#%%
p = np.array([1., -1, 2, -3,  5, -2])
x0 = 1.

print('Restos de dividir P una y otra vez por (x-x0)')        
d0 = polDer(x0,p)
print(d0)

r = np.array([1., -1, -1, 1, -1, 0, -1, 1])
x1 = -1.

print('\nRestos de dividir R una y otra vez por (x-x0)')        
d1 = polDer(x1,r)
print(d1)