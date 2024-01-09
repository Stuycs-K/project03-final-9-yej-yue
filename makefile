compile: main.o lib.o list.o err.o  _server _client
#audio not included anywhere yet
main: main.o
	gcc -o main main.o
	./main

main.o: main.c list.h lib.h connect.h err.h
	@gcc -c -L/SDL/include/SDL3 -lSDL3 main.c 
_server: server.o connect.o lib.o list.o err.o
	gcc -o server server.o connect.o lib.o list.o err.o
_client: client.o connect.o err.o
	gcc -o client client.o connect.o err.o 
server: _server	
	./server
client: _client
	./client 
audio.o: audio.c err.h
	@gcc -c audio.c -I/SDL/include/SDL3
connect.o: connect.c err.h 
	@gcc -c connect.c
server.o: server.c err.h lib.h list.h
	@gcc -c server.c 
client.o: client.c err.h list.h lib.h
	@gcc -c client.c 
lib.o: lib.c list.h err.h
	@gcc -c lib.c list.c
list.o: list.c err.h
	@gcc -c list.c 
err.o: err.c err.h
	@gcc -c err.c 
clean:
	rm -f *.o
	rm -f runme
	rm -f *.h.gch
	rm -f server
	rm -f client