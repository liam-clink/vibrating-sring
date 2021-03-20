import matplotlib
matplotlib.rcParams['text.usetex'] = True
import matplotlib.pyplot as plt
import numpy as np

data = np.loadtxt('data.tsv')

name_length = int(np.ceil(np.log10(data.shape[0])))

xmax = max(data[:,1])
xmin = min(data[:,1])
ymax = max(data[:,2])
ymin = min(data[:,2])

#Complete Track
plt.plot(data[:,2],data[:,3])
plt.savefig('all.png')
plt.show()
plt.clf()

'''
#Spectrum of vertical oscillation
spectrum = np.fft.fft(data[:,3])
freq = np.fft.fftfreq(data[:,0].shape[0],data[1,0]-data[0,0])
plt.plot(freq,np.abs(spectrum))
plt.show()
'''

'''
#Vertical force vs vertical displacement
plt.plot(data[:,3],data[:,7],label="Vertical Force")
plt.plot(data[:,3],data[:,6],label="Horizontal Force")
plt.legend()
plt.xlabel("Vertical Displacement")
plt.ylabel("Force")
plt.title(r"Force along the line from $(1,-2) \to (1,2)$")
plt.show()
'''

'''
for i in range(data.shape[0]):
    steps = min(100,i)
    plt.plot(data[i-steps:i,1],data[i-steps:i,2])
#    plt.ylim(ymin,ymax)
#    plt.xlim(xmin,xmax)
    plt.savefig('frames/'+str(i).zfill(name_length)+'.png')
    plt.clf()
'''

index_filter = data[:,0] <= 23.
plt.plot(data[index_filter,0],data[index_filter,1])
plt.xlabel("time")
plt.ylabel("energy")
plt.show()

xmax = max(data[index_filter,1])
xmin = min(data[index_filter,1])
ymax = max(data[index_filter,2])
ymin = min(data[index_filter,2])

'''
#plt.plot(data[index_filter,2],data[index_filter,3])
for i in range(data[index_filter,:].shape[0]):
    plt.quiver(data[i,2],data[i,3],data[i,4],data[i,5])
    #plt.xlim(xmin,xmax)
    #plt.ylim(ymin,ymax)
    plt.savefig("arrow/"+str(i).zfill(name_length)+'.png')
    plt.clf()
'''
