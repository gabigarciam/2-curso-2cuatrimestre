# -*- coding: utf-8 -*-
"""
ejercicio 2
"""
import numpy as np
import matplotlib.pyplot as plt
import numpy.polynomial.polynomial as pol
import pandas as pd

df = pd.read_csv('http://www.unioviedo.es/compnum/labs/new/cars.csv',sep=',')


x = df['weight']
y = df['horsepower']
z = df['origin']

p = pol.polyfit(x,y,1)
# linea
xp = np.linspace(min(x),max(x))
yp = pol.polyval(xp,p)
# punto
xpunto = 3000
ypunto = pol.polyval(xpunto,p)
print(int(ypunto), 'hp')

plt.figure()
plt.plot(x[z==1],y[z==1],'yo',label='Americano')
plt.plot(x[z==2],y[z==2],'bo',label='Europeo')
plt.plot(x[z==3],y[z==3],'co',label='Asiático')
plt.legend()
plt.xlabel('weight')
plt.ylabel('horsepower')

plt.plot(xp,yp,'r')
plt.plot(xpunto,ypunto,'ro')

plt.show()
#%%

x = df['horsepower']
y = df['mpg']
z = df['origin']

p = pol.polyfit(x,y,2)
# linea
xp = np.linspace(min(x),max(x))
yp = pol.polyval(xp,p)
# punto
xpunto = ypunto
ypunto = pol.polyval(xpunto,p)
print(int(ypunto),' mpg')


plt.figure()
plt.plot(x[z==1],y[z==1],'yo',label='Americano')
plt.plot(x[z==2],y[z==2],'bo',label='Europeo')
plt.plot(x[z==3],y[z==3],'co',label='Asiático')
plt.legend()
plt.xlabel('horsepower')
plt.ylabel('mpg')
plt.plot(xp,yp,'r-')
plt.plot(xpunto,ypunto,'ro')
plt.show()