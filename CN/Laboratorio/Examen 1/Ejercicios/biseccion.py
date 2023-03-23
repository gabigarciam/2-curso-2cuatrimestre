#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
L5 ex2
"""
import numpy as np
import matplotlib.pyplot as plt

def biseccion(f,a,b,tol=1e-6,maxiter=100):

    error = np.inf
    k = 0
    x = a
    
    while error > tol and k < maxiter:
        
        xant = x
        x = (a + b) / 2
        
        if   f(a) * f(x) < 0:
            b = x
        elif f(x) * f(b) < 0: 
            a = x
        else:
            return x, k+1
        
        error = np.abs(x - xant)
        k += 1
        
    return x, k 
#------------------------  

f = lambda x: x**5 - 3 * x**2 + 1.6   

a = -0.7; b = -0.6
sol1, i1 = biseccion(f,a,b)
print(sol1, i1)

a = 0.8; b = 0.9
sol2, i2 = biseccion(f,a,b)
print(sol2, i2)

a = 1.2; b = 1.3
sol3, i3 = biseccion(f,a,b)
print(sol3, i3)

#-------------------------
print('')
f = lambda x: np.cos(x)*(x**3+1)/(x**2+1)
x = np.linspace(-3,3,100)

plt.figure()
plt.plot(x,f(x))
plt.plot(x,0*x,'k')
plt.show()

a = -2.; b = -1.5
sol1, i1 = biseccion(f,a,b)
print('%.5f' % sol1)

a = -1.5; b = 0.
sol2, i2 = biseccion(f,a,b)
print('%.5f' % sol2)

a = 1.; b = 2.
sol3, i3 = biseccion(f,a,b)
print('%.5f' % sol3)


  
