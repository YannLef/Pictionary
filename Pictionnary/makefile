main: main.o structures.o affichage.o calcul.o libisentlib.a
	gcc -Wall -o main main.o structures.o calcul.o affichage.o libisentlib.a -lm -lglut -lGL -lX11

main.o: main.c GFX/GfxLib.h  structures.h affichage.h calcul.h GFX/BmpLib.h
	gcc -c -Wall main.c
	
structures.o: structures.c GFX/GfxLib.h affichage.h calcul.h
	gcc -Wall -c structures.c
	
affichage.o: affichage.c GFX/GfxLib.h affichage.h calcul.h GFX/BmpLib.h
	gcc -Wall -c affichage.c
	
calcul.o: calcul.c GFX/GfxLib.h affichage.h calcul.h GFX/BmpLib.h
	gcc -Wall -c calcul.c

libisentlib.a: BmpLib.o ErreurLib.o ESLib.o GfxLib.o OutilsLib.o SocketLib.o ThreadLib.o VectorLib.o WavLib.o
	ar r libisentlib.a BmpLib.o ErreurLib.o ESLib.o GfxLib.o OutilsLib.o SocketLib.o ThreadLib.o VectorLib.o WavLib.o
	ranlib libisentlib.a

BmpLib.o: GFX/BmpLib.c GFX/BmpLib.h GFX/OutilsLib.h
	gcc -Wall -O2 -c GFX/BmpLib.c

ESLib.o: GFX/ESLib.c GFX/ESLib.h GFX/ErreurLib.h
	gcc -Wall -O2 -c GFX/ESLib.c

ErreurLib.o: GFX/ErreurLib.c GFX/ErreurLib.h
	gcc -Wall -O2 -c GFX/ErreurLib.c

GfxLib.o: GFX/GfxLib.c GFX/GfxLib.h GFX/ESLib.h
	gcc -Wall -O2 -c GFX/GfxLib.c -I/usr/include/GL

OutilsLib.o: GFX/OutilsLib.c GFX/OutilsLib.h
	gcc -Wall -O2 -c GFX/OutilsLib.c

SocketLib.o: GFX/SocketLib.c GFX/SocketLib.h
	gcc -Wall -O2 -c GFX/SocketLib.c

ThreadLib.o: GFX/ThreadLib.c GFX/ThreadLib.h
	gcc -Wall -O2 -c GFX/ThreadLib.c

VectorLib.o: GFX/VectorLib.c GFX/VectorLib.h
	gcc -Wall -O2 -c GFX/VectorLib.c -msse3

WavLib.o: GFX/WavLib.c GFX/WavLib.h GFX/OutilsLib.h
	gcc -Wall -O2 -c GFX/WavLib.c -Wno-unused-result

zip:
	tar -cvzf libisentlib.tgz *.[ch] *.bmp *.pdf makefile

clean:
	rm -f *~ *.o

deepclean: clean
	rm -f main libisentlib.a

