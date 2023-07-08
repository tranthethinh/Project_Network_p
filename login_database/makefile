all: server client

server: tcp_server.c
	gcc -o server tcp_server.c -L/usr/local/mysql/lib -lmysqlclient

client: tcp_client.c
	gcc -o client tcp_client.c

clean:
	rm -f server client
