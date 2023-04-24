#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Newton Cotes
"""
import numpy as np
import matplotlib.pyplot as plt
import numpy.polynomial.polynomial as pol
import sympy as sym
#-----------------------------------------------------

def dibujo(f,a,b,nodos):
    xp = np.linspace(a,b)
    
    plt.figure()
    
    # Área exacta
    plt.plot(xp,f(xp),'b',label = 'Área exacta')
    plt.plot([a,a,b,b],[f(a),0,0,f(b)],'b')
    
    # Puntos de interpolación
    plt.plot(nodos,f(nodos),'ro',label = 'Puntos de interpolación')
    
    # Área aproximada
    p  = pol.polyfit(nodos,f(nodos),len(nodos)-1)
    yp = pol.polyval(xp,p)
    pa = pol.polyval(a,p)
    pb = pol.polyval(b,p)
    
    plt.plot(xp,yp,'r--',label='Área aproximada')
    plt.plot([a,a,b,b],[pa,0,0,pb],'r--')
    
    plt.legend()
    plt.show()
    
#-----------------------------------------------------
def punto_medio(f,a,b,p=False):
    m = (a+b)/2
    I = (b-a) * f(m)
    if p == True:
        nodos = np.array([m])
        dibujo(f,a,b,nodos)
        
    return I 
   
#----------------------------------------------------- 
def trapecio(f,a,b,p=False):
    I = (b-a) * (f(a) + f(b)) * 0.5
    if p == True:
        nodos = np.array([a,b])
        dibujo(f,a,b,nodos)
                
    return I

#----------------------------------------------------- 
def simpson(f,a,b,p=False):
    m = (a+b)/2
    I = (b-a) * (f(a) + 4*f(m) + f(b)) / 6
    if p == True:
        nodos = np.array([a,m,b])
        dibujo(f,a,b,nodos)
                
    return I

#----------------------------------------------------- 
def punto_medio_comp(f,a,b,n):
    h = (b-a) / n
    x = np.arange(a,b+h/2,h)
    Ia = 0.
    for i in range(n):
        Ia += punto_medio(f,x[i],x[i+1])
    
    return Ia 
           
#----------------------------------------------------- 
def trapecio_comp(f,a,b,n):
    h = (b-a) / n
    x = np.arange(a,b+h/2,h)
    Ia = 0.
    for i in range(n):
        Ia += trapecio(f,x[i],x[i+1])
    
    return Ia 

#-----------------------------------------------------     
def simpson_comp(f,a,b,n):
    h = (b-a) / n
    x = np.arange(a,b+h/2,h)
    Ia = 0.
    for i in range(n):
        Ia += simpson(f,x[i],x[i+1])
    
    return Ia 
#----------------------------------------------------- 
#%%
def main():
    print('=======  Ejercicio 1 plot  =======')  
    # Ejemplo 1
    f = lambda x: np.exp(x)
    a = 0.; b = 3; nodos = np.array([1,2,2.5])
    dibujo(f,a,b,nodos)
    
    # Ejemplo 2
    f = lambda x: np.cos(x) + 1.5
    a = -3.; b = 3; nodos = np.array([-3.,-1,0,1,3])
    dibujo(f,a,b,nodos)
    
    # VALOR EXACTO
    x = sym.Symbol('x', real=True) 
    f_sym = sym.log(x)
    Ie = sym.integrate(f_sym,(x,1,3))
    Ie = float(Ie)
    
    # DATOS
    f = lambda x: np.log(x)
    a = 1; b = 3 
    
    
    print('\n=======  Ejercicio 1a  =======') 
    Ia = punto_medio(f,a,b,p=True)
    print('El valor aproximado es ',Ia)
    print('El valor exacto es     ',Ie)
    
    
    print('\n=======  Ejercicio 1b  =======') 
    Ia = trapecio(f,a,b,p=True)
    print('El valor aproximado es ',Ia)
    print('El valor exacto es     ',Ie)
    
    
    print('\n=======  Ejercicio 1c  =======') 
    Ia = simpson(f,a,b,p=True)
    print('El valor aproximado es ',Ia)
    print('El valor exacto es     ',Ie)
    
    
    print('\n=======  Ejercicio 1d  =======') 
    Ia = punto_medio_comp(f,a,b,5)
    print('El valor aproximado es ',Ia)
    print('El valor exacto es     ',Ie)
    
    
    print('\n=======  Ejercicio 1e  =======') 
    Ia = trapecio_comp(f,a,b,4)
    print('El valor aproximado es ',Ia)
    print('El valor exacto es     ',Ie)
    
    
    print('\n=======  Ejercicio 1f  =======') 
    Ia = simpson_comp(f,a,b,4)
    print('El valor aproximado es ',Ia)
    print('El valor exacto es     ',Ie)
    
if __name__ == "__main__":
    main()    
        