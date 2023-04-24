#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Aproximación polinómica continua
"""
import numpy as np
import matplotlib.pyplot as plt
import numpy.polynomial.polynomial as pol
from scipy.integrate import quad
np.set_printoptions(precision = 2)   
np.set_printoptions(suppress = True) 

def approx2(f,deg,a,b,prin=False):
    # 1. Construye el sistem
    C = np.zeros((deg+1,deg+1))
    d = np.zeros(deg+1)
    
    for i in range(deg+1):
        g = lambda x: x**i * f(x)
        d[i] = quad(g,a,b)[0]
        for j in range(deg+1):
            g = lambda x: x**(i+j)
            C[i,j] = quad(g,a,b)[0]               
    
    # 2. Resuelve el sistema
    p = np.linalg.solve(C,d)
    
    if prin == True:
        print('Matriz de coeficientes')
        print(C)
        print('\nTérminos independientes')
        print(d)
        print('\nSolución del sistema')
        print(p)
        
    # 3. Plot
    xp = np.linspace(a,b)
    yp = pol.polyval(xp,p)

    plt.figure()
    plt.plot(xp,f(xp),'r',label='función')
    plt.plot(xp,yp,label = 'polinomio de ajuste')
    plt.legend()
    plt.show()        
    
# -------------------------------------------------
# first example
f1 = lambda x: np.sin(x)
a1 = 0.; b1 = 2.; deg1 = 2
approx2(f1,deg1,a1,b1,prin=True)    
# -------------------------------------------------
# second example
f2 = lambda x: np.cos(np.arctan(x)) - np.log(x+5)
a2 = -2.; b2 = 0.; deg2 = 4
approx2(f2,deg2,a2,b2)  




