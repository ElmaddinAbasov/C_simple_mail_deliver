#ifndef SOCKET_LIB_H
#define SOCKET_LIB_H
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
enum {datagram_cap = 512};
typedef struct 
{
	int sfd;
	struct sockaddr_in sin;
	char msg[datagram_cap];
	enum operations{file_creat};
}my_socket;
void init(my_socket* ms, int pnum);
void creat_socket(my_socket* ms);
void bind_socket(my_socket* ms);
void reuse_port(int sfd);
void send_datagram(int sfd, const char* msg, size_t len, const struct sockaddr* dest_addr, socklen_t slen);
void recieve_datagram(int sfd, char* msg, size_t len, struct sockaddr* src_addr);
void close_socket(int sfd);
#endif
