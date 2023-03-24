#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Ex 4
"""
import numpy as np

a = np.array([1., 2, 3])
#%%
b = np.append(a, 0)
b = b[::-1]
b = np.append(b, 0)
b = b[::-1]
print('1.')
print('\nb = ', b)
#%%
b = np.zeros(5)
b[1:-1] = a 
print('2.')
print('\nb = ', b)
#%%
c = np.zeros(1)
b = np.concatenate((a,c))
b = np.concatenate((c,b))
print('3.')
print('\nb = ', b)