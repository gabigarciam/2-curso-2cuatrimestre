# -*- coding: utf-8 -*-
"""
L2 Ex2
"""
import numpy as np
import matplotlib.pyplot as plt
#%%---------------------------------
def funExp(x, tol, maxNumSum):
    polynomial = 0.
    factorial = 1.
    term = np.inf
    i = 0
    
    while np.max(np.abs(term)) > tol and i < maxNumSum:
        term = x**i/factorial
        polynomial += term
        factorial *= i+1
        i += 1
        
    return polynomial
#%%---------------------------------    

f = lambda x: np.exp(x)
x = np.linspace(-1,1)
tol = 1.e-8
maxNumSum = 100

y1 = f(x)
y2 = funExp(x, tol, maxNumSum)
OX = 0*x

plt.figure()
plt.plot(x,y1,'y',linewidth=5, label = 'f')
plt.plot(x, y1,'b--',label = 'f approximation')
plt.plot(x, OX,'k')
plt.title('f approximation with McLaurin series')
plt.legend()
plt.show()

