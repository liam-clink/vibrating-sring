# vibrating-string
This code simulates a realistic string, which we model as several 100,000 tiny masses connected by springs.
The code allows you to simulate a string of uniform mass density.

# How to run
Clone the directory and navigate to the `Cpp_Implementation` directory.
You can specify the simulation parameters by editing the `params.txt` file.
To run the simulations itself, you first should run the `make command`, then the `make run` command.

For graphics to work, OpenGL, GLEW and GLFW need to be installed.
Important to note, when installing GLEW the README says to run `make`
straight away, but you first have to run `make extensions`. This
uses the "OpenGL-Registry" and "EGL-Registry" GitHub repositories
to test the capabilities of your graphics card and generate the
appropriate header file.