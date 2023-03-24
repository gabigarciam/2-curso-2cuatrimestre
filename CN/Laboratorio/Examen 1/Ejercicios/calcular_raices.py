import scipy.optimize as op
import numpy as np
import matplotlib.pyplot as plt
import scipy.optimize as op


f  = lambda x: np.sin(x) - 0.1*x - 0.1
df = lambda x: np.cos(x) - 0.1

x = np.linspace(-1,20,1000)

#plt.figure(figsize=(15,4))
#plt.plot(x,f(x))
#plt.plot(x,0*x,'k-')
#plt.show()

x0 = np.array([0., 2., 7., 8.])
x1 = x0 + 1
raiz = np.zeros_like(x0)
for i in range(len(raiz)):
    raiz[i]= op.bisect(f,x0[i],x1[i],xtol=1.e-6,maxiter=100)       
    print(raiz[i])
    
x = np.linspace(-1,9)



plt.figure()
plt.plot(x,f(x),x,x*0,'k',raiz,raiz*0,'ro')
plt.show()