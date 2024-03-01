CC = gcc
CFLAGS = -Wall
SRC = gol_2d.c
EXECUTABLE = gol

all: $(EXECUTABLE)

$(EXECUTABLE): $(SRC)
	$(CC) $(CFLAGS) -o $@ $<
clean:
	-rm -f $(EXECUTABLE)
