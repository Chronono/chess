	CC=gcc

HEADERS_PATH=./headers/
SOURCES_PATH=./sources/
BUILD_PATH=./build/

build: main board piece debug move notation game
	$(CC) -o exe $(BUILD_PATH)main.o $(BUILD_PATH)board.o $(BUILD_PATH)piece.o $(BUILD_PATH)debug.o $(BUILD_PATH)move.o $(BUILD_PATH)notation.o $(BUILD_PATH)game.o

main: main.c
	$(CC) -c main.c
	mv main.o $(BUILD_PATH)

game: $(SOURCES_PATH)game.c
	$(CC) -c $(SOURCES_PATH)game.c
	mv game.o $(BUILD_PATH)

notation: $(SOURCES_PATH)notation.c
	$(CC) -c $(SOURCES_PATH)notation.c
	mv notation.o $(BUILD_PATH)

debug: $(SOURCES_PATH)debug.c
	$(CC) -c $(SOURCES_PATH)debug.c
	mv debug.o $(BUILD_PATH)

board: $(SOURCES_PATH)board.c
	$(CC) -c $(SOURCES_PATH)board.c
	mv board.o $(BUILD_PATH)

piece: $(SOURCES_PATH)piece.c
	$(CC) -c $(SOURCES_PATH)piece.c
	mv piece.o $(BUILD_PATH)

move: $(SOURCES_PATH)move.c
	$(CC) -c $(SOURCES_PATH)move.c
	mv move.o $(BUILD_PATH)

clean:
	rm exe

