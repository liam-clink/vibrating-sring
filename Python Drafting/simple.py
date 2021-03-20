import numpy as np

number_of_particles = 10
dimension = 2
positions = np.zeros((number_of_particles,dimension),dtype=np.float64)
separations = np.zeros((number_of_particles+1,dimension),dtype=np.float64)
distances = np.zeros((separations.shape[0]),dtype=np.float64)
velocities = np.zeros_like(positions)
masses = np.ones((number_of_particles),np.float64)
forces = np.zeros_like(velocities)

system_length = 11.*1.5
spring_stiffness = 10.
# The masses partition the string into number_of_particles+1 pieces
partition_length = system_length/(number_of_particles+1)
spring_length = 1.

endpoints = np.zeros((2,dimension),dtype=np.float64)
endpoints[1,0] = system_length

for i in range(number_of_particles):
    positions[i,0] = (i+1)*partition_length

def force(positions):
    
    separations[0,:] = positions[0,:]-endpoints[0,:]
    separations[-1,:] = endpoints[-1,:]-positions[-1,:]
    if positions.shape[0] > 1:
        for i in range(separations.shape[0]-2):
            separations[i+1,:] = positions[i+1,:] - positions[i,:]
    distances = np.linalg.norm(separations,axis=1)

    forces[:,:] = 0.
    for i in range(forces.shape[0]):
        forces[i,:] += -spring_stiffness * \
            ((separations[i,:]/distances[i])*(distances[i]-spring_length) + \
             (-separations[i+1,:]/distances[i+1])*(distances[i+1]-spring_length))

    return forces

def energy(pos,vel):
    E = 0
    global masses
    global spring_stiffness
    global spring_length

    for i in range(vel.shape[0]):
        E += .5*masses[i]*np.dot(vel[i,:],vel[i,:])
     
    separations[0,:] = pos[0,:]-endpoints[0,:]
    separations[-1,:] = pos[-1,:]-endpoints[-1,:]
    distances = np.linalg.norm(separations,axis=1)
    for i in range(pos.shape[0]):
        E += .5*spring_stiffness*(distances[i]-spring_length)**2
    E += .5*spring_stiffness*(distances[-1]-spring_length)**2
    
    return E

def update(delta_time):
    global positions, velocities

    #Euler Cromer (semi-implicit Euler)
    for i in range(positions.shape[0]):
        positions[i] += velocities[i]*delta_time
        
    forces = force(positions)

    for i in range(positions.shape[0]):
        # forces[i] is from the left neighboring spring, forces[i+1] is from the right
        velocities[i] += forces[i]/masses[i]*delta_time

def output_data(fname,t,pos,vel,force):
    output_string = ''
    output_string += str(t) + '\t'
    #output_string += str(E) + '\t'

    for i in range(pos.shape[0]):
        for j in range(dimension):
            output_string += str(pos[i,j]) + '\t'
        for j in range(dimension):
            output_string += str(vel[i,j]) + '\t'
        for j in range(dimension):
            output_string += str(force[i,j]) + '\t'
    output_string = output_string[0:-1]+'\n'

    fname.write(output_string)

dt = .1
duration = 1000.
time = np.linspace(0,duration,int(duration//dt))
f = open("data.tsv",'w')

#Modify Initial Conditions
for i in range(positions.shape[0]):
    positions[i] += [0.1,0.1]

for i in range(len(time)):
    update(dt)
    output_data(f,time[i],positions,velocities,force(positions))
    
f.close()
