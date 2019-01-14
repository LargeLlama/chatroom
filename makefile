all: client server

client: client.o chatroom.h
	gcc -o client client.o  

server: server.o subserver.o chatroom.h 
	gcc -o server server.o subserver.o

client.o: client.c chatroom.h
	gcc -c client.c

server.o: server.c chatroom.h
	gcc -c server.c

subserver.o: subserver.c chatroom.h
	gcc -c subserver.c


clean:
	rm *.o
	rm *~
