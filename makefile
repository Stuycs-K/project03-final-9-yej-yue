compile: main.o _server _client

main.o: main.c list.h lib.h connect.h err.h
	@gcc -c -L/SDL/include/SDL3 -lSDL3 main.c list.h lib.h connect.h err.h
_server: server.o connect.o
	gcc -o server server.o connect.o
_client: client.o connect.o
	gcc -o client client.o connect.o
server: _server	
	./server
client: _client
	./client 
main: main.o
	gcc -o main main.o
	./main
audio.o: audio.c err.h
	@gcc -c audio.c -I/SDL/include/SDL3
connect.o: connect.c err.h
	@gcc -c connect.c
server.o: server.c err.h list.h lib.h
	@gcc -c server.c
client.o: client.c err.h list.h lib.h
	@gcc -c client.c
lib.o: lib.c err.h
	@gcc -c lib.c
list.o: list.c err.h
	@gcc -c list.c
clean:
	rm -f *.o
	rm -f runme
	rm -f *.h.gch
	rm -f server
	rm -f client