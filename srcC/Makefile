# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g
OBJ = main.o helper.o parser.o lagrange.o graph.o solver.o
TARGET = executable

# Default rule
all: $(TARGET)

# Link the object files into the final executable
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

# Compile each .c file to .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJ)
