compile: main.o _server _client
	gcc -o runme main.o
main.o: main.c list.h lib.h 
	@gcc -c main.c list.h lib.h 
_server: server.o connect.o
	gcc -o server server.o connect.o
_client: client.o connect.o
	gcc -o client client.o connect.o
server: _server	
	./server
client: _client
	./client 
# audio.o: audio.c
# 	@gcc -c audio.c -ISDL
connect.o: connect.c
	@gcc -c connect.c
server.o: server.c
	@gcc -c server.c
client.o:  client.c
	@gcc -c client.c
lib.o: lib.c
	@gcc -c lib.c
list.o: list.c
	@gcc -c list.c
clean:
	rm -f *.o
	rm -f runme
	rm -f *.h.gch