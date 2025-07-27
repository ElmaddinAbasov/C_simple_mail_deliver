#ifndef DELIVERY_SERVER_H
#define DELIVERY_SERVER_H
#include "socket_lib.h"
#include <signal.h>
#include <string.h>
#include <fcntl.h>
enum {server_send, server_recieve};
enum {time_to_wait = 5};
enum {buf_len = 1024};
enum {back_slash = '/'};
typedef void (*sighandler_t)(int);
init_server(ms, pnum);
run_server(ms, pnum, state, msg);
shut_server(sfd);
#endif
