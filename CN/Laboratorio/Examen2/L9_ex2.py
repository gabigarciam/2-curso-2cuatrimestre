#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Gaussian
"""
import numpy as np
import sympy as sym
from L9_ex1 import dibujo
#-----------------------------------------------------

def gauss(f,a,b,n,p=False):
    
    [x, w] = np.polynomial.legendre.leggauss(n)
    y = (b-a) / 2 * x  +  (a+b) / 2
    Ia = (b-a)/2 * np.sum(w * f(y))
    
    if p == True:
        dibujo(f,a,b,y)
    
    return Ia
#----------------------------------------------------- 
#%%
def main():
    
    # VALOR EXACTO
    x = sym.Symbol('x', real=True) 
    f_sym = sym.log(x)
    Ie = sym.integrate(f_sym,(x,1,3))
    Ie = float(Ie)
    
    # DATOS
    f = lambda x: np.log(x)
    a = 1; b = 3 
    
    for n in range(1,4):
        Ia = gauss(f,a,b,n,p=True)
        if n == 1:
            print('\n',n,' nodo')
        else:    
            print('\n',n,' nodos')
        print('El valor aproximado es ',Ia)
        print('El valor exacto es     ',Ie)
        
if __name__ == "__main__":
    main()        
