all: game

run: game
	./game

game: mechanics.o main.o score_panel.o display.o savedata.o opening.o
	gcc *.o -lncurses -o game

mechanics.o: source/mechanics.c dir/mechanics.h
	gcc -c source/mechanics.c -Idir

main.o: source/main.c dir/mechanics.h dir/display.h dir/score_panel.h dir/savedata.h dir/opening.h
	gcc -c source/main.c -Idir

score_panel.o: source/score_panel.c dir/score_panel.h dir/mechanics.h
	gcc -c source/score_panel.c -Idir

display.o: source/display.c dir/display.h
	gcc -c source/display.c -Idir

savedata.o: source/savedata.c dir/savedata.h
	gcc -c source/savedata.c -Idir

opening.o: source/opening.c dir/opening.h
	gcc -c source/opening.c -Idir

clean:
	rm -f *.o game
