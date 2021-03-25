all: game


game: final.c  gfx.c letters.c numbers.c
	gcc $? -o game -I/usr/X11R6/include -L/usr/X11R6/lib -lX11 -lm

.PHONY: clean
clean:
	rm game
