CFLAGS=$(shell pkg-config --cflags dbus-1 -libs)

all:
	@gcc -o bin/server src/server.c $(CFLAGS)
	@gcc -o bin/client src/client.c $(CFLAGS)
