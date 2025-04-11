CC = gcc
CFLAGS = -ansi -Wall
LDFLAGS = -lMLV
SRC = src/main.c src/entity.c src/game.c src/gate.c src/graph.c src/position.c src/fichier.c src/player.c    
OBJ = bin/main.o bin/entity.o bin/game.o bin/gate.o bin/graph.o bin/position.o bin/fichier.o bin/player.o
EXEC = exec

$(EXEC) : $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

bin/main.o : src/main.c
	$(CC) -o $@ -c $^ $(CFLAGS) $(LDFLAGS)

bin/entity.o : src/entity.c
	$(CC) -o $@ -c $^ $(CFLAGS)

bin/game.o : src/game.c
	$(CC) -o $@ -c $^ $(CFLAGS)

bin/player.o : src/player.c
	$(CC) -o $@ -c $^ $(CFLAGS)

bin/fichier.o : src/fichier.c
	$(CC) -o $@ -c $^ $(CFLAGS)

bin/graph.o : src/graph.c
	$(CC) -o $@ -c $^ $(CFLAGS) $(LDFLAGS)

bin/gate.o : src/gate.c
	$(CC) -o $@ -c $^ $(CFLAGS)

bin/position.o : src/position.c
	$(CC) -o $@ -c $^ $(CFLAGS)

clean :
	rm -rf bin/*.o

mrpoper : clean
	rm -rf $(EXEC)

	
