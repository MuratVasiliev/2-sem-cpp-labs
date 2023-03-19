import matplotlib.pyplot as plt
import numpy as np
import matplotlib.ticker as ticker

x=[]
y=[]
f=open("numbers.txt", 'r')
A=int(f.readline())
for i in range(A-1):
    a=int(f.readline())
    y.append(a)
    b=int(f.readline())
    x.append(b)
#for i in range(A):
#    print(x[i], " " ,y[i])
plt.xlabel('N')
plt.ylabel('T')
plt.plot(x, y, 'bo')
#plt.tick_params (left= False, labelleft=False)
plt.show()