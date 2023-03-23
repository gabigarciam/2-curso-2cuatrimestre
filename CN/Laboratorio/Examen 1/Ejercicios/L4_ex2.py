# -*- coding: utf-8 -*-
"""
L4 ex2
"""
import numpy as np
np.set_printoptions(precision = 2)   # only two decimals
np.set_printoptions(suppress = True) # do not use exponential format
from L4_ex1 import triangulariza

def sust_reg(At,bt):
    x = np.zeros_like(bt)
    n = len(x)
    
    x[n-1] = bt[n-1] / At[n-1,n-1]
    for i in range(n-2,-1,-1):
        x[i] = (bt[i] - At[i,i+1]*x[i+1]) / At[i,i]
        
    return x
#----------------------------
n = 7 

A1 = np.diag(np.ones(n))*3
A2 = np.diag(np.ones(n-1),1) 
A = A1 + A2 + A2.T 

b = np.arange(n,2*n)*1.

At, bt = triangulariza(A,b)
x = sust_reg(At,bt)

print('x')
print(x)
#----------------------------
n = 8 

np.random.seed(3)
A1 = np.diag(np.random.rand(n))
A2 = np.diag(np.random.rand(n-1),1)
A = A1 + A2 + A2.T 

b = np.random.rand(n)

At, bt = triangulariza(A,b) 
x = sust_reg(At,bt)

print('\nx')
print(x)