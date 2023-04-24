#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Chebyshev
"""
import numpy as np
import matplotlib.pyplot as plt
import numpy.polynomial.polynomial as pol

def chebyshev(f,a,b,n):
    # equispaced nodes ---------------------
    # nodes
    xe = np.linspace(a,b,n)
    ye = f(xe)
    
    # interpolant polynomials
    p1 = pol.polyfit(xe,ye,n-1)
    xp = np.linspace(a,b,500)
    yp = pol.polyval(xp,p1)
    
    # plot
    plt.figure()
    plt.plot(xp,f(xp),'b',label='función')
    plt.plot(xe,ye,'ro',label = 'puntos')
    plt.plot(xp,yp,'r',label='polinomio')
    plt.legend()
    plt.title('Nodos equiespaciados')
    plt.axis([-1.05, 1.05, -0.3, 2.3])
    plt.show()
    
    # Chebyshev nodes  ---------------------
    # nodes
    i = np.arange(1,n+1)
    xc = np.cos(((2*i - 1) * np.pi) / (2*n))
    yc = f(xc)
    
        
    # interpolant polynomials
    p2 = pol.polyfit(xc,yc,n-1)
    xp = np.linspace(a,b)
    yp = pol.polyval(xp,p2)
    
    # plot
    plt.figure()
    plt.plot(xp,f(xp),'b',label='función')
    plt.plot(xc,yc,'ro',label = 'puntos')
    plt.plot(xp,yp,'r',label='polinomios')
    plt.legend()
    plt.title('Nodos de Chebyshev')
    plt.axis([-1.05, 1.05, -0.3, 2.3])
    plt.show()
#-----------------------------------------------    
# first example    
f1 = lambda x: 1/(1 + 25 * x**2)
n1 = 11; a1 = -1.; b1 = 1. 

chebyshev(f1,a1,b1,n1)
#-----------------------------------------------    
# second example    
f2 = lambda x: np.exp(-20 * x**2)
n2 = 15; a2 = -1.; b2 = 1. 

chebyshev(f2,a2,b2,n2)  