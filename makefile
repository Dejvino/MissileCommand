all: game


game: game.c  gfx.c 
	gcc game.c gfx.c -o game -lX11

clean: rm -rf game
