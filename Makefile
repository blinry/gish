default: gish

gish: main.c
	gcc main.c -lopenal -lSDL -lGL -lvorbisfile -o gish

clean:
	rm gish
