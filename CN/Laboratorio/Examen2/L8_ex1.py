# -*- coding: utf-8 -*-
"""
ejercicio 1
"""
import numpy as np
import matplotlib.pyplot as plt
import numpy.polynomial.polynomial as pol

def aprox1(f,g,a,b,n):
    # 1. construir n puntos equiespaciados en (a,b)
    x = np.linspace(a,b,n)
    y = f(x)
    
    # 2. Construir el sistema (C y d)
    # Construir V
    V = np.ones((n,g+1))
    for i in range(n):
        for j in range(1,g+1):
            V[i,j] = x[i]**j          
    
    C = np.dot(V.T,V)
    d = np.dot(V.T,y)
    
    # 3. Resolver el sistema
    p = np.linalg.solve(C,d)
    
    # 4. Dibujar los puntos y el polinomio de ajuste
    xp = np.linspace(a,b)
    yp = pol.polyval(xp,p)
    
    plt.figure()
    plt.plot(xp,yp,'b-', label = 'polinomio de ajuste')
    plt.plot( x, y,'ro', label = 'puntos')
    plt.legend()
    plt.show()
#---------------------------------------
# primer ejemplo
f = lambda x: np.sin(x)
a = 0.; b = 2.; n = 5; g = 2
aprox1(f,g,a,b,n)    
#---------------------------------------
# segundo ejemplo    
f = lambda x: np.cos(np.arctan(x)) - np.log(x+5)
a = -2.; b = 0.; n = 10; g = 4
aprox1(f,g,a,b,n) 