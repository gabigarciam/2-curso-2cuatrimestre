import numpy as np
import sympy as sym
import matplotlib.pyplot as plt
import scipy.optimize as op

x = sym.Symbol('x', real=True)

f_sim = x**2 + sym.log(2*x + 7) * sym.cos(3*x) + 0.1
df_sim  = sym.diff(f_sim,x)
d2f_sim = sym.diff(df_sim,x)
d3f_sim = sym.diff(df_sim,x)

f   = sym.lambdify([x], f_sim,'numpy') 
df  = sym.lambdify([x], df_sim,'numpy') 
d2f = sym.lambdify([x], d2f_sim,'numpy') 
d3f = sym.lambdify([x], d3f_sim,'numpy') 

a = -1
b = 4

x = np.linspace(a, b, 500)

x0= np.array([-1.,0., 1., 2., 3.])
raiz = op.newton(df, x0, tol = 1.e-6,maxiter=100)
#print(raiz)

x0= np.array([-0.5,0.5, 1.5, 2.5, 3.5])
raiz2 = op.newton(d2f, x0, tol = 1.e-6,maxiter=100)
#print(raiz2)

x = np.linspace(a, b, 1000)


maximos = np.array([])
minimos = np.array([])
ptosInflexion = np.array([])
for i in range (len(raiz)):
    if(d2f(raiz[i]) < 0):
        maximos = np.append(maximos, raiz[i])
    elif(d2f(raiz[i]) > 0):
        minimos = np.append(minimos, raiz[i])
for i in range(len(raiz2)):
    if(d3f(raiz[i]) != 0):
        ptosInflexion= np.append(ptosInflexion, raiz[i])

print(maximos, '\n')
print(minimos, '\n')
print(ptosInflexion)        