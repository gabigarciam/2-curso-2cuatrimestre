# -*- coding: utf-8 -*-
"""
L4 Ex1
"""
import numpy as np

def busquedaIncremental(f,a,b,n):
    x = np.linspace(a,b,n+1)
    # Another way
    # dx = (b-a)/n
    # x = np.arange(a,b+dx,dx)
    intervalos = np.zeros((n,2))
    
    c = 0
    for i in range(n):
        if f(x[i])*f(x[i+1]) < 0:
            intervalos[c,:] = (x[i], x[i+1]) 
            c += 1
    
    return intervalos[:c,:]   
#-------------------------

f1 = lambda x: x**5 - 3 * x**2 + 1.6
a1 = -1; b1 = 1.5; n1 = 25

intervalos1 =  busquedaIncremental(f1,a1,b1,n1)   
print('Intervalos que contienen raíces de f1\n')
print(intervalos1) 

#-------------------------
f2 = lambda x: (x + 2) * np.cos(2*x)
a2 = 0; b2 = 10; n2 = 100

intervalos2 =  busquedaIncremental(f2,a2,b2,n2)   
print('\nIntervalos que contienen raíces de f2\n')
print(intervalos2)
    
   