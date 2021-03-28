CC = g++ -std=c++17 -Wall#-g3 -fsanitize=address
OPT = -O2 -funroll-loops -finline-functions -fopenmp
LIBS = -lpthread
INCLUDES = -I /usr/local/include 

SRC = ./source/
INC = ./include/
OBJ = ./build/

FILES := $(shell find $(SRC) -name '*.cpp')
OBJ_FILES := $(patsubst $(SRC)%.cpp,$(OBJ)%.o,$(FILES))

CFLAGS = $(OPT)

all: string_simulation.x

string_simulation.x: $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS) $(INCLUDE)

$(OBJ)%.o: $(SRC)%.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -MMD -c -o $@ $< 