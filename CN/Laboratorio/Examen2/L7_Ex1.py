#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Polinomios fundamentales de Lagrange
"""
import numpy as np
import matplotlib.pyplot as plt

def lagrange_fund(k,x,z):
    n = len(x)
    
    p = 1.
    for i in range(n):
        if i != k:
            p *= (z - x[i]) / (x[k] - x[i])
            
    return p        

def main():
    x = np.array([-1., 0, 2, 3, 5])
    
    # Ejemplo 1
    k = 2
    z = 1.3
    yz = lagrange_fund(k,x,z)
    print(yz)
    print(' ')

    # Ejemplo 2
    k = 2
    z = np.array([1.3, 2.1, 3.2])
    yz = lagrange_fund(k,x,z)
    print(yz)
    
    # Ejemplo 3
    n = len(x)
    e = np.eye(n)
    xp = np.linspace(min(x),max(x)) 
    for k in range(n):
        plt.figure()
        yp = lagrange_fund(k,x,xp)
        plt.plot(xp,yp)
        plt.plot(x,e[k],'o')
        plt.plot(x,0*x,'k')
        plt.title('L'+str(k))
        
        

if __name__ == "__main__":
    main()