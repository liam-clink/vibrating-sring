CC = g++ -std=c++17
OPT = -O2 -funroll-loops -finline-functions
LIBS = -lpthread
INCLUDES = -I /usr/local/inlcude

CFLAGS = $(OPT) $(INCLUDES) $(LIBS) 
threading_practice: threading_practice.cpp
	$(CC) -o $@ $< $(CFLAGS) -MMD

string_simulation.x : string_simulation.cpp
	$(CC) -MMD -o $@ $< $(CFLAGS) 