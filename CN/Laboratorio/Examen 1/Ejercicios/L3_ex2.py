# -*- coding: utf-8 -*-
"""
L3 Ex2
"""
import numpy as np
import matplotlib.pyplot as plt

def HornerV(x, p):
    n = len(p)
    q = np.zeros_like(p)
    y = np.zeros_like(x)
    
    q[-1] = p[-1]
    for k in range(len(x)):
        for i in range(n-2,-1,-1):
            q[i] = p[i] + q[i+1]*x[k]        
        y[k] = q[0]
    return y
#-------------------------------
# Para usar en el ejercicio 6
def main():
    x = np.linspace(-1,1)        
    
    
    p = np.array([1., -1, 2, -3, 5, -2])
    yp = HornerV(x,p)
    
    plt.figure()
    plt.plot(x,yp)
    plt.plot(x,0*x,'k')
    plt.title('P')
    plt.show()
    
    r = np.array([1., -1, -1, 1, -1, 0, -1, 1])
    yr = HornerV(x,r)
    
    plt.figure()
    plt.plot(x,yr)
    plt.plot(x,0*x,'k')
    plt.title('R')
    plt.show()
    
if __name__ == "__main__":
    main()    