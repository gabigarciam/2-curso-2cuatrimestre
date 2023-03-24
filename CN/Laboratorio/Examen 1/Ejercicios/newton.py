#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
L5 ex2
"""
import numpy as np
import matplotlib.pyplot as plt
import sympy as sym

def newton(f,df,x0,tol=1.e-6,maxiter=100):

    error = np.inf
    k = 0
    x = x0
    
    while error > tol and k < maxiter:
        
        xant = x
        x = xant - f(xant) / df(xant) 
        
        error = np.abs(x - xant)
        k += 1
        
    return x, k 
#------------------------ 
 
f =  lambda x: x**5 - 3 * x**2 + 1.6
df = lambda x: 5 * x**4 - 6 * x  

x1 = -0.7
sol1, i1 = newton(f,df,x1)
print(sol1, i1)

x2 = 0.8
sol2, i2 = newton(f,df,x2)
print(sol2, i2)

x3 = 1.2
sol3, i3 = newton(f,df,x3)
print(sol3, i3)
#--------------------------------
print(' ')
x = sym.Symbol('x', real=True)
f_sim   = sym.cos(x)*(x**3+1)/(x**2+1)
df_sim  = sym.diff(f_sim,x)

f   = sym.lambdify([x], f_sim,'numpy') 
df  = sym.lambdify([x], df_sim,'numpy')

x = np.linspace(-3,3,100)

plt.figure()
plt.plot(x,f(x))
plt.plot(x,0*x,'k')
plt.show()

x0 = -2.
sol1, i1 = newton(f,df,x0)
print('%.5f' % sol1)

x0 = -0.5
sol2, i2 = newton(f,df,x0)
print('%.5f' % sol2)

x0 = 2.
sol3, i3 = newton(f,df,x0)
print('%.5f' % sol3)

   
