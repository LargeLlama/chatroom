all: client server

client: client.o client_dashboard.o chatroom.h
	gcc -o client client.o  client_dashboard.o

server: server.o subserver.o dashboard.o chatroom.h 
	gcc -o server server.o subserver.o dashboard.o

client.o: client.c chatroom.h
	gcc -c client.c

server.o: server.c chatroom.h
	gcc -c server.c

subserver.o: subserver.c chatroom.h
	gcc -c subserver.c

dashboard.o: dashboard.c chatroom.h
	gcc -c dashboard.c 

client_dashboard.o: client_dashboard.c chatroom.h
	gcc -c client_dashboard.c 

clean:
	rm *.o
	rm *~
