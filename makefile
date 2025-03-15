# The name of the source files
SOURCES = main.c $(wildcard user/src/*.c)

# The name of the executable
TARGET = build/prog

# Flags for compilation (adding warnings are always good)
CFLAGS = -Wall -g -Iuser/lib

# Flags for linking (none for the moment)
LDFLAGS =

# Libraries to link with (none for the moment)
LIBS = 

# Use the GCC frontend program when linking
LD = gcc

# This creates a list of object files from the source files
OBJECTS = $(SOURCES:.c=.o)

# Default target
default: all

# "all" target, builds the program
all: $(TARGET)

# Link the object files into the final executable
$(TARGET): $(OBJECTS)
	$(LD) $(LDFLAGS) $(OBJECTS) -o $(TARGET) $(LIBS)

# Compile each .c file into a .o file
%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

# Clean up generated files
clean:
	-rm -f $(TARGET) $(OBJECTS)
