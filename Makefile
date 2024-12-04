EXEC = exe
SRC = proyecto.c
CC = gcc
CFLAGS = -lm

p2: $(EXEC)

$(EXEC): $(SRC) 
	$(CC) -o $(EXEC) $(SRC) $(CFLAGS)

clean:
	rm -f $(EXEC)