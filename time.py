import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

t1=np.genfromtxt("time1.txt")
t2=np.genfromtxt("time2.txt")
t4=np.genfromtxt("time4.txt")

p=np.array([1,2,4])
t=np.array([t1,t2,t4])

fig1=plt.figure()
plt.plot(p,t,marker='o')
plt.xlim(0,5)
plt.ylabel('Tiempo (s)')
plt.xlabel('Numero de procesadores')
plt.savefig('t_proc.pdf')
plt.close()
