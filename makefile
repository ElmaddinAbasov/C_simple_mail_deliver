CC=gcc
CCFLAGS=-Wall -Wextra -O1
socket_lib.o:socket_lib.c
	$(CC) $(CCFLAGS) -g -c $< -o $@
delivery_server.o:delivery_server.c
	$(CC) $(CCFLAGS) -g -c $< -o $@	
deliver_system.o:deliver_system.c
	$(CC) $(CCFLAGS) -g -c $< -o $@	
daemon.o:daemon.c
	$(CC) $(CCFLAGS) -g -c $< -o $@	
composer:composer.c socket_lib.o deliver_system.o
	$(CC) $(CCFLAGS) -g $^ -o $@	
delivers1:delivers1.c socket_lib.o delivery_server.o
	$(CC) $(CCFLAGS) -g $^ -o $@

