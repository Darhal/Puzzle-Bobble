SRC1=GameManager.c
SRC2=Ball.c
SRC3=utils.c
SRC4=list.c
SRC5=Animation.c
SRC6=Board.c
BIN=puzzle

$(BIN): $(SRC1) $(SRC2) defines.h GameManager.h Ball.h list.h Animation.h Board.h
	gcc -Wall -g -std=c99 $(SRC1) $(SRC2) $(SRC3) $(SRC4) $(SRC5) $(SRC6) main.c -lm `sdl-config --cflags --libs` -lSDL_ttf -o $(BIN)

clean:
	rm -f $(BIN)
