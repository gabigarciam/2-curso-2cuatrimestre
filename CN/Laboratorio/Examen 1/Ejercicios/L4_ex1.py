# -*- coding: utf-8 -*-
"""
L4 Ex1
"""
import numpy as np
np.set_printoptions(precision = 2)   # only two decimals
np.set_printoptions(suppress = True) # do not use exponential format

def triangulariza(A,b):
    At = np.copy(A)
    bt = np.copy(b)
    
    n = len(bt)
    
    for i in range(n-1):
        f = At[i+1,i] / At[i,i]
        At[i+1,i]   -= f * At[i,i]
        At[i+1,i+1] -= f * At[i,i+1]
        bt[i+1]     -= f *bt[i]
        
    return At, bt 
#--------------------   
def main():
    n = 7 
    
    A1 = np.diag(np.ones(n))*3
    A2 = np.diag(np.ones(n-1),1) 
    A = A1 + A2 + A2.T 
    
    b = np.arange(n,2*n)*1.
    
    At, bt = triangulariza(A,b)
     
    print('-------------  DATOS  -------------')
    print('A')
    print(A)
    print('b')
    print(b)
    print('\n-------  SISTEMA TRIANGULARIZADO -------')      
    print('At')
    print(At)
    print('bt')
    print(bt)   
    #------------------------
    n = 8 
    
    np.random.seed(3)
    A1 = np.diag(np.random.rand(n))
    A2 = np.diag(np.random.rand(n-1),1)
    A = A1 + A2 + A2.T 
    
    b = np.random.rand(n)
    
    At, bt = triangulariza(A,b) 
    
    print('\n-------------  DATOS  -------------')
    print('A')
    print(A)
    print('b')
    print(b)
    print('\n-------  SISTEMA TRIANGULARIZADO -------')      
    print('At')
    print(At)
    print('bt')
    print(bt)
    
if __name__ == "__main__":
    main()    