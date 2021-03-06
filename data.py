import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

E1=np.genfromtxt("proc1.txt")
E2=np.genfromtxt("proc2.txt")
E4=np.genfromtxt("proc4.txt")

t=np.arange(len(E1))

fig1=plt.figure()
plt.plot(t,E1[:,0],marker='x',label='E_1')
plt.plot(t,E1[:,1],marker='x',label='E_2')
plt.plot(t,E1[:,2],marker='x',label='E_3')
plt.legend()
plt.xlabel('Numero de iteracion')
plt.ylabel('Energia')
plt.title('Energia de los tres primero modos (1 procesador)')
plt.savefig('ek_1proc.pdf')
plt.close()

fig2=plt.figure()
plt.plot(t,E2[:,0],marker='x',label='E_1')
plt.plot(t,E2[:,1],marker='x',label='E_2')
plt.plot(t,E2[:,2],marker='x',label='E_3')
plt.legend()
plt.xlabel('Numero de iteracion')
plt.ylabel('Energia')
plt.title('Energia de los tres primero modos (2 procesadores)')
plt.savefig('ek_2proc.pdf')
plt.close()

fig3=plt.figure()
plt.plot(t,E4[:,0],marker='x',label='E_1')
plt.plot(t,E4[:,1],marker='x',label='E_2')
plt.plot(t,E4[:,2],marker='x',label='E_3')
plt.legend()
plt.xlabel('Numero de iteracion')
plt.ylabel('Energia')
plt.title('Energia de los tres primero modos (4 procesadores)')
plt.savefig('ek_4proc.pdf')
plt.close()
