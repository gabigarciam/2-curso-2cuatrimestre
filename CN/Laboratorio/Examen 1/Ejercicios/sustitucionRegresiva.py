import numpy as np

def triangulariza(A,b):
    m,n = A.shape
    At = np.copy(A)
    bt = np.copy(b)
    for i in range(m - 1):
        f = At[i+1][i] / At[i][i]
        At[i + 1][i] = At[i + 1][i] - f * At[i][i]
        At[i+1][i+1] = At[i+1][i+1] - f * At[i][i+1]
        bt[i + 1] = bt[i+1] - f * bt[i]
    return At, bt 

def sust_reg(A,b):
    n1 = len(b)
    n2 = 0
    x = np.copy(b)
    for k in range(n1 - 1, n2 - 1, -1):
        if(k == n1 - 1):
            x[k] = b[k] / A[k][k]
        else:
            x[k] = (b[k] - A[k][k+1] * x[k+1] ) / A[k][k]
    return x

        
np.set_printoptions(precision = 2)   # solo dos decimales
np.set_printoptions(suppress = True) # no usar notación exponencial   
    
n = 7 

A1 = np.diag(np.ones(n))*3
A2 = np.diag(np.ones(n-1),1) 
A = A1 + A2 + A2.T
b = np.arange(n,2*n)*1.
At, bt = triangulariza(A,b)

print("At", At)
print("bt", bt)

x = sust_reg(At,bt)

print("x", x, "\n")
n = 8 

np.random.seed(3)
A4 = np.diag(np.random.rand(n))
A5 = np.diag(np.random.rand(n-1),1)
A3 = A4 + A5 + A5.T 

b1 = np.random.rand(n)

At2, bt2 = triangulariza(A3,b1)

print("At", At2)
print("bt", bt2)

x2 = sust_reg(At2,bt2)

print("x", x2)