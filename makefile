compile runme: main.o lib.o list.o
	@gcc -o runme main.o lib.o list.o
run: runme
	@./runme
main.o: main.c list.h lib.h
	@gcc -c main.c list.h lib.h
lib.o: lib.c
	@gcc -c lib.c
list.o: list.c
	@gcc -c list.c
clean:
	rm -f *.o
	rm -f runme
	rm -f *.h.gch