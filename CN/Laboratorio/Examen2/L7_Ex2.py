#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Lagrange interpolation polynomial
"""
import numpy as np
import matplotlib.pyplot as plt
from L7_Ex1 import lagrange_fund

def polinomio_lagrange(x,y,z):
    n = len(x)
    
    s = 0.
    for k in range(n):
        s += y[k] * lagrange_fund(k,x,z)
    
    return s    
#-------------------------------------------    
# first example    
    
x = np.array([-1., 0, 2, 3, 5])
y = np.array([ 1., 3, 4, 3, 1])

xp = np.linspace(min(x),max(x))
yp = polinomio_lagrange(x,y,xp)

plt.figure()
plt.plot(x,y,'ro',label='puntos')
plt.plot(xp,yp,label='P')
plt.legend()
plt.show()
#-------------------------------------------    
# second example  
x1 = np.array([-1., 0, 2, 3, 5, 6, 7])
y1 = np.array([ 1., 3, 4, 3, 2, 2, 1])

xp = np.linspace(min(x1),max(x1))
yp = polinomio_lagrange(x1,y1,xp)

plt.figure()
plt.plot(x1,y1,'ro',label='puntos')
plt.plot(xp,yp,label='P')
plt.legend()
plt.show()