3CC = gcc
CFLAGS = -I./include -Wall
OBJ = obj/mat.o obj/matop.o
BIN = bin/matop

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) -o $@ $^

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f obj/*.o bin/*

run: all
	./bin/matop -s -x 3 -y 3 
	./bin/matop -m -x 5 -y 5
	./bin/matop -t -x 5 -y 5