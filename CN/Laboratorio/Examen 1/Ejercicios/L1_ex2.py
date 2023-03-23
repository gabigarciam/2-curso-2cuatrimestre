#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Ex 2
"""
import numpy as np
np.set_printoptions(precision=2,suppress=True)

"""
np.arange
"""
a = np.arange(7, 16, 2)
print('a = ', a)
#%%
b = np.arange(10, 5, -1)
print('b = ', b)
#%%
c = np.arange(15,-1,-5)
print('c = ', c)
#%%
n = 11              # number of points
ni = n - 1         # number of intervals
step = (1-0) / ni
d = np.arange(0, 1.1, step)
print('d = ', d)
#%%
ni = 10             # number of intervals
step = (1-(-1)) / ni
e = np.arange(-1, 1.1, step)
print('e = ', e)
#%%
f = np.arange(1, 2.1, 0.1)
print('f = ', f)
#%%
"""
np.linspace
"""
a = np.linspace(7, 15, 5)
print('\na = ', a)
#%%
b = np.linspace(10, 6, 5)
print('b = ', b)
#%%
c = np.linspace(15, 0, 4)
print('c = ', c)
#%%
n = 11              # number of points
d = np.linspace(0, 1, n)
print('d = ', d)
#%%
ni = 10             # number of intervals
n = ni + 1          # number of points
e = np.linspace(-1, 1, n)
print('e = ', e)
#%%
step = 0.1
ni = (2-1) / step
n = int(ni + 1)
f = np.linspace(1, 2, n)
print('f = ', f)