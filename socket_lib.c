#include "socket_lib.h"

void init(my_socket* ms, int pnum)
{
	ms->sin.sin_family = AF_INET;
	ms->sin.sin_port = htons(pnum);
	ms->sin.sin_addr.s_addr = htons(INADDR_ANY);
}

void creat_socket(my_socket* ms)
{
	errno = 0;
	ms->sfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (ms->sfd == -1)
	{
		perror("creat_socket()");
		exit(1);
	}
}

void bind_socket(my_socket* ms)
{
	int res;
	socklen_t slen;
	slen = sizeof(ms->sin);
	errno = 0;
	res = bind(ms->sfd, (const struct sockaddr*)&(ms->sin), slen);
	if (res == -1)
	{
		perror("bind_socket()");
		exit(2);
	}
}

void reuse_port(int sfd)
{
	int res, a = 1;
	errno = 0;
	res = setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &a, sizeof(a));
	if (res == -1)
	{
		perror("reuse_port");
		exit(3);
	}
}

void send_datagram(int sfd, const char* msg, size_t len, const struct sockaddr* dest_addr, socklen_t slen)
{
	ssize_t cnt;
	errno = 0;
	cnt = sendto(sfd, msg, len, 0, dest_addr, slen);
	if (cnt == -1)
	{
		perror("send_datagram()");
		exit(4);
	}
}

void recieve_datagram(int sfd, char* msg, size_t len, struct sockaddr* src_addr)
{
	ssize_t cnt;
	socklen_t slen;
	slen = sizeof(src_addr);
	errno = 0;
	cnt = recvfrom(sfd, msg, len, 0, src_addr, &slen);
	if (cnt == -1)
	{
		perror("recive_datagram()");
		exit(5);
	}
}

void close_socket(int sfd)
{
	int res;
	errno = 0;
	res = close(sfd);
	if (res == -1)
	{
		perror("close_socket()");
		exit(6);
	}
}
