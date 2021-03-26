CC = g++ -std=c++17 -Wall#-g3 -fsanitize=address
OPT = -O2 -funroll-loops -finline-functions -fopenmp
LIBS = -lpthread
INCLUDES = -I /usr/local/include 

CFLAGS = $(OPT)
threading_practice.x: threading_practice.cpp
	$(CC) $(CFLAGS) -MMD -o $@ $< 

string_simulation.x: string_simulation.cpp
	$(CC) $(CFLAGS) -MMD -o $@ $< $(INCLUDE) $(LIBS)