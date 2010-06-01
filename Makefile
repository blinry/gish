default: main.c
	gcc main.c -lGL -lopenal -lSDL -lvorbisfile -o gish

clean:
	rm gish
