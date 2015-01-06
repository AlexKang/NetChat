all: 
	gcc host.c chat.c -o host
	gcc client.c chat.c -o client

clean:
	rm host && rm client
