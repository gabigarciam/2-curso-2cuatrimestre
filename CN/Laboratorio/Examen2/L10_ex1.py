# -*- coding: utf-8 -*-
"""
Jacobi
"""
import numpy as np
np.set_printoptions(precision = 8)   
np.set_printoptions(suppress = True)

def jacobi(A,b,tol,maxiter=1000):
    n = len(b)
    x  = np.zeros_like(b)
    
    error = np.inf
    k = 0
    
    while k < maxiter and error > tol:
        xp = np.copy(x)
        for i in range(n):
            x[i] = b[i]
            
            for j in range(i):
                x[i] -= A[i,j]*xp[j]
            
            for j in range(i+1,n):
                x[i] -= A[i,j]*xp[j]
                
            x[i] /= A[i,i]
            
        error = np.linalg.norm(x-xp)    
        k +=1
        
    return x, k    
                

#%%----------------------------------------------
A = np.array([[5.,1.,-1.,-1.],[1.,4.,-1.,1.],[1.,1.,-5.,-1.],[1.,1.,1.,-4.]])
b = np.array([1.,1.,1.,1.])
tol = 1.e-6

x, num_iter = jacobi(A,b,tol)

print('\n------------- Sistema 1 -------------')  
print('\n---- Datos ----')
print('A')
print(A)
print('b')
print(b)
print('\n---- Solución ----')
print('\n', num_iter,' iteraciones')

print('\nx aproximada ')
print(x)    

xs = np.linalg.solve(A,b)
print('\nx exacta ')
print(xs)
#%%----------------------------------------------
n = 9 

A1 = np.diag(np.ones(n))*2 
A2 = np.diag(np.ones(n-1),1)
A = A1 + A2 + A2.T 

b = np.concatenate((np.arange(1,6),np.arange(4,0,-1)))*1.

tol = 1.e-6

x, num_iter = jacobi(A,b,tol)


print('\n------------- Sistema 2 -------------')
print('\n---- Datos ----')
print('A')
print(A)
print('b')
print(b)
print('\n---- Solución ----')
print('\n', num_iter,' iteraciones')
print('\nx aproximada ')
print(x)    

xs = np.linalg.solve(A,b)
print('\nx exacta ')
print(xs)