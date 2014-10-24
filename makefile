all: game


game: final.c  gfx.c letters.c numbers.c objects.c 
	gcc final.c gfx.c letters.c numbers.c -o game -I/usr/X11R6/include -L/usr/X11R6/lib -lX11 -lm

clean: rm -rf game
