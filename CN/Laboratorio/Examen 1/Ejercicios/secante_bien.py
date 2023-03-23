import numpy as np

def secante(f,x0,x1,tol = 1.e-6,maxiter=100):
    a = x0 
    b = x1
    for k in range(maxiter):
        c = b - f(b) * (b - a)/(f(b) - f(a))
        if (abs(c-b) < tol):
            
            break
        a,b =b,c    
    else:
        return c, str(maxiter) + str('el máximo')    
    return c, k+1


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