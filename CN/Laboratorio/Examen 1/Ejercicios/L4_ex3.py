# -*- coding: utf-8 -*-
"""
L4 ex3
"""
import numpy as np
np.set_printoptions(precision = 2)   # only two decimals
np.set_printoptions(suppress = True) # do not use exponential format

def triangularizar(Ar,b):
    At = np.copy(Ar)
    bt = np.copy(b)
    
    n = len(bt)
    
    for i in range(n-1):
        f = At[i+1,0] / At[i,1]
        At[i+1,0] -= f * At[i,1]
        At[i+1,1] -= f * At[i,2]
        bt[i+1]   -= f *bt[i]
        
    return At, bt 
#----------------------------
def sust_regr(At,bt):
    x = np.zeros_like(bt)
    n = len(x)
    
    x[n-1] = bt[n-1] / At[n-1,1]
    for i in range(n-2,-1,-1):
        x[i] = (bt[i] - At[i,2]*x[i+1]) / At[i,1]
        
    return x
#----------------------------
n = 7 

Ar = np.zeros((n,3))
Ar[:,0] = np.concatenate((np.array([0]),np.ones((n-1),)))
Ar[:,1] = np.ones((n),)*3
Ar[:,2] = np.concatenate((np.ones((n-1),),np.array([0])))

b = np.arange(n,2*n)*1.

At, bt = triangularizar(Ar,b)

x = sust_regr(At,bt)

print('-------------  DATOS  -------------')
print('Ar')
print(Ar)
print('b')
print(b)
print('\n-------  SISTEMA TRIANGULARIZADO -------')
print('At')
print(At)
print('\n-----------  SOLUCIÓN  -----------')
print('x')
print(x)
#----------------------------
n = 8

np.random.seed(3)
Ar = np.zeros((n,3))
Ar[:,1] = np.random.rand(n)
Ar[:,0] = np.concatenate((np.array([0]),np.random.rand(n-1)))
Ar[0:n-1,2] = Ar[1:n,0]

b = np.random.rand(n)

At, bt = triangularizar(Ar,b)

x = sust_regr(At,bt)

print('\n\n\n-------------  DATOS  -------------')
print('Ar')
print(Ar)
print('b')
print(b)
print('\n-------  SISTEMA TRIANGULARIZADO -------')
print('At')
print(At)
print('\n-----------  SOLUCIÓN -----------')
print('x')
print(x)