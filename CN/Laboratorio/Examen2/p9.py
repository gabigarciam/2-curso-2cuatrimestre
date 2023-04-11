import numpy as np
import matplotlib.pyplot as plt
import sympy as sym
import numpy.polynomial.polynomial as pol
import inspect

def dibujo(f,a,b,nodos):
    xx = np.linspace(a,b,500) 
    p = pol.polyfit(nodos, f(nodos), len(nodos) - 1)
    plt.figure(figsize = (6*2.9, 4*2.9))
    plt.plot(xx, f(xx), 'b-', linewidth = 7, label = 'Área exacta')
    plt.plot([a,a,b,b], [f(a),0,0, f(b)], 'b-', linewidth = 7)
    plt.plot(xx, pol.polyval(xx,p), 'r--', linewidth = 4, label ='Área aprox')
    plt.plot([a,a,b,b],[pol.polyval(a,p), 0,0, pol.polyval(b,p)], 'r-', linewidth = 4)
    plt.plot(nodos, pol.polyval(nodos,p), 'r.', markersize = 35, label=f'nodos ({len(nodos)})')
    plt.legend(fontsize=20)
    plt.tick_params(labelsize=20)
    plt.title(inspect.getsource(f).lstrip().rstrip(), fontsize =20)
    plt.grid(visible =True)
    plt.show()

def punto_medio(f,a,b):
    nodos=np.array([(a+b)/2])
    pm=(b-a)*f((a+b)/2)
    print(f'pm = {pm}')
    dibujo(f,a,b, nodos)
    return pm

def trapecio(f,a,b):
    nodos=np.array([a,b])
    t=((b-a)/2)*(f(a) + f(b))
    print(f't = {t}')
    dibujo(f,a,b, nodos)
    return t

def simpson(f,a,b):
    nodos=np.array([a,(a+b)/2,b])
    s = (b-a)/6*(f(a) + 4 * f((a+b)/2) + f(b))
    print(f's = {s}')
    dibujo(f,a,b, nodos)
    return s

def punto_medio_comp(f,a,b,n):
    h = (b-a)/n
    x_ant = a
    count = 0
    for i in range(1, n+1):
        xi = a + i * h
        Xi = (x_ant + xi) / 2
        x_ant = xi
        count=f(Xi) + count 
    pm=h*count
    print(f'pm = {pm}')
    return pm



f = lambda x: np.log(x)
a = 1; b = 3; nodos = np.array([1,2,2.5])
#dibujo(f,a,b,nodos)
#punto_medio(f, a, b)
#trapecio(f, a, b)
#simpson(f, a, b)
punto_medio_comp(f, a, b, 5)

#f = lambda x: np.cos(x) + 1.5
#a = -3.; b = 3; nodos = np.array([-3.,-1,0,1,3])
#dibujo(f,a,b,nodos)

