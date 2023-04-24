#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Degree of precision
"""
import numpy as np
import sympy as sym
from L9_ex1 import punto_medio, trapecio, simpson
from L9_ex2 import gauss
#-----------------------------------------------------

def newton_cotes(f,a,b,n):
    if n == 1:
        Ia = punto_medio(f,a,b)
    elif n == 2:
        Ia = trapecio(f,a,b)
    elif n == 3:
        Ia = simpson(f,a,b)
        
    return Ia
#-----------------------------------------------------
def grado_de_precision(formula,n):
    k = 0
    error = 0.
    while error < 1.e-10:
        # EXACT VALUE
        x = sym.Symbol('x', real=True) 
        Ie = sym.integrate(x**k,(x,1,3))
        Ie = float(Ie) 
        
        # APPROXIMATE VALUE
        f = lambda x: x**k
        Ia = formula(f,1,3,n)
        
        error = np.abs(Ia-Ie)
        
        print('f(x) = x^'+str(k)+'   error =  ',error)
        k += 1
        
    print('\nEl grado de precisión es',k-2)    
#-----------------------------------------------------
print('----  Fórmula del punto medio (n = 1) ----\n') 
grado_de_precision(newton_cotes,1)

print('\n----  Fórmula del trapecio (n = 2) ----\n')       
grado_de_precision(newton_cotes,2) 

print('\n----  Fórmula de Simpson (n = 3) ----\n')  
grado_de_precision(newton_cotes,3)   

print('\n----  Fórmula Gauss n = 1  ----\n')
grado_de_precision(gauss,1)

print('\n----  Fórmula Gauss n = 2  ----\n')
grado_de_precision(gauss,2)

print('\n----  Fórmula Gauss n = 3  ----\n')
grado_de_precision(gauss,3)

print('\n----  Fórmula Gauss n = 4  ----\n')
grado_de_precision(gauss,4)