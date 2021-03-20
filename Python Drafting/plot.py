import matplotlib.pyplot as plt
import numpy as np

data = np.loadtxt('data.tsv')
dimension = 2
name_length = int(np.ceil(np.log10(data.shape[0])))

# Get bounds for consistent frames
xmax = max(data[:,1])
xmin = min(data[:,1])
ymax = max(data[:,2])
ymin = min(data[:,2])

# Plot the complete track in space
initial_offset = 1
particle_offset = 6
fig = plt.figure()
ax = fig.add_subplot(111)
for i in range((data.shape[1]-initial_offset)//particle_offset):
    ax.plot(data[:,0+initial_offset+i*particle_offset],\
            data[:,1+initial_offset+i*particle_offset])
ax.set_xlabel("x")
ax.set_ylabel("y")
ax.set_title("Complete Track")
ax.set_aspect("equal")
fig.savefig('complete_track_space.svg')
#plt.show()

# Plot the x displacement in time
initial_offset = 1
particle_offset = 6
fig = plt.figure()
ax = fig.add_subplot(111)
for i in range((data.shape[1]-initial_offset)//particle_offset):
    ax.plot(data[:,0],data[:,0+initial_offset+i*particle_offset])
ax.set_xlabel("time")
ax.set_ylabel("x displacement")
ax.set_title("X Displacements")
fig.savefig('x_track_time.svg')
#plt.show()

# Plot the y displacement in time
initial_offset = 1
particle_offset = 6
fig = plt.figure()
ax = fig.add_subplot(111)
for i in range((data.shape[1]-initial_offset)//particle_offset):
    ax.plot(data[:,0],data[:,1+initial_offset+i*particle_offset])
ax.set_xlabel("time")
ax.set_ylabel("y displacement")
ax.set_title("Y Displacements")
fig.savefig('y_track_time.svg')
#plt.show()

# Play waveform directly
#import sounddevice as sd 
#sd.play(100*data[:,0+initial_offset+1*particle_offset],44100,blocking=True,loop=True)

# Save to WAV so that low sample rate can be used
# This library is used instead of wave because it supports float
import scipy.io.wavfile
x_audio = data[:,0+initial_offset+5*particle_offset]
x_audio -= np.average(x_audio)
scipy.io.wavfile.write('testx.wav', 15000, x_audio)

y_audio = data[:,1+initial_offset+5*particle_offset]
y_audio -= np.average(y_audio)
scipy.io.wavfile.write('testy.wav', 15000, y_audio)