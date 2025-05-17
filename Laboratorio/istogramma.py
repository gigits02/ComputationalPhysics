import numpy as np
import math 
import matplotlib.pyplot as plt
#x = np.darray((25,2), dtype = np.double)
x = np.ndarray((24), dtype = np.double)
y= np.ndarray((24), dtype = np.double)

x = [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25]
y = np.loadtxt("risultati.dat")

print(x)


plt.plot(x, y, 'b--')
plt.bar(x,y)





