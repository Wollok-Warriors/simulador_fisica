CC     = gcc
CFLAGS = -Wall -Wextra -std=c11 `pkg-config --cflags sdl3`
LIBS   = `pkg-config --libs sdl3` -lm
SRC    = main.c physics.c render.c
TARGET = out

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LIBS)

clean:
	rm -f $(TARGET)
