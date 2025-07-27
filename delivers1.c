#include "socket_lib.h"
#include "delivery_server.h"
enum {serv1_port = 5001};
char dg[datagram_cap];
main(int argc, char** argv)
{
	my_socket ms;
	init_server(&ms, serv1_port);
	run_server(&ms, serv1_port, server_recieve, dg);
	shut_server(ms.sfd);
	exit(0);
}
