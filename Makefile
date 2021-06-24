# CC = g++
 
# # compiler flags:
# #  -g     - this flag adds debugging information to the executable file
# #  -Wall  - this flag is used to turn on most compiler warnings
# CFLAGS  = -g -Wall -o chess-engine -lsfml-graphics -lsfml-window -lsfml-system -std=c++11

# # The build target 
# TARGET = main move_generator

# all: $(TARGET)

# $(TARGET): $(TARGET).cpp
# 			$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp

# clean:
# 			$(RM) $(TARGET)

CC = g++
CFLAGS  = -g -Wall -lsfml-graphics -lsfml-window -lsfml-system -std=c++11
DEPS = graphics.h helper_functions.h game.h
OBJ = main.o move_generator.o game.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	$(RM) $(OBJ)