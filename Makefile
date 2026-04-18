# 1. Variables - Makes it easy to change compilers or flags later
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 `pkg-config --cflags sdl3`
LIBS = `pkg-config --libs sdl3`
SRC = main.c
TARGET = out

# 2. The default rule (runs when you just type 'make')
all: $(TARGET)

# 3. Rule to build the executable
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LIBS)

# 4. Utility rule to clean up the folder
clean:
	rm -f $(TARGET)
