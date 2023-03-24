import numpy as np

def secante(f,x0,x1,tol = 1.e-6,maxiter=100):
    error = np.inf
    k = 0
    xk = x0
    xant1 = 0
    while (error > tol and k < maxiter):
        xant2 = xant1
        xant1 = xk
        xk = xant1 - f(xant1) * ((xant1 - xant2)/
                                 (f(xant1)- f(xant2)))
        error = np.abs(xk - xant1)
        k += 1
    r = xk
    return r
        
        
f1 = lambda x: x**5 - 3 * x**2 + 1.6
a1 = -0.7
b1 = -0.6
sol1 = secante(f1, a1, b1)
a2 = 0.8
b2 = 0.9
sol2 = secante(f1, a2, b2)
a3 = 1.2
b3 = 1.3
sol3 = secante(f1, a3, b3)
print(sol1, "\n", sol2, "\n" , sol3)

