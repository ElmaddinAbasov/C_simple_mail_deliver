#include "socket_lib.h"
#include "deliver_system.h"
enum {composer_port = 5000};
enum {server_port = 5001};
enum {size = 512};
main(int argc, char** argv)
{
	my_socket sock_composer;
	int is_found;
	size_t len;
	struct sockaddr_in server;
	socklen_t slen;
	char recipient_path[size];
	int i;
	if (argc < 3)
	{
		fprintf(stderr, "ERROR: Provide recipient name and mail message");
		exit(1);
	}	
	init(&sock_composer, composer_port);
	creat_socket(&sock_composer);
	bind_socket(&sock_composer);
	reuse_port(sock_composer.sfd);
	is_found = 0;
	find_recipient(".", *(argv + 1), &is_found, recipient_path);
	if (!is_found)
	{	
		fprintf(stderr, "ERROR: No such recipient\n");
		close_socket(sock_composer.sfd);
		exit(2);
	}	
	printf("Recipient was found\n%s\n", recipient_path);
	strcpy(sock_composer.msg, recipient_path);
	len = strlen(sock_composer.msg);
	*(sock_composer.msg + len) = 0;
	len = strlen(sock_composer.msg);
	if (len >= datagram_cap)
	{
		fprintf(stderr, "ERROR: Composer tries to send a mail that is too long\n");
		exit(3);
	}	
	server.sin_port = htons(server_port);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htons(INADDR_ANY);
	slen = sizeof(server);
	for (i = 1; i < argc; i++)
	{
		send_datagram(sock_composer.sfd, sock_composer.msg, len, (const struct sockaddr*)&server, slen);
		*(sock_composer.msg) = 0;
		strcpy(sock_composer.msg, *(argv + 2));
		len = strlen(sock_composer.msg);
		*(sock_composer.msg + len) = 0;
	}
	close_socket(sock_composer.sfd);
	exit(0);
}
