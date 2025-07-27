#include "delivery_server.h"

static volatile sig_atomic_t flag = 0;
static char path[buf_len];

static void handler(int sig)
{
	flag = 1;
}

static clear_buffer(msg, len)
char* msg;
int len;
{
	int i;
	for (i = 0; i < len; i++)
		*(msg + i) = 0;
}

static path_concat(path, path1, path2)
char* path;
const char* path1;
const char* path2;
{
        size_t len;
	if (path1)
	{	
        	strcpy(path, path1);
        	len = strlen(path1);
        	*(path + len) = back_slash;
        	*(path + len + 1) = 0;
	}
	if (path2)
	{	
        	strcat(path, path2);
        	len = strlen(path);
        	*(path + len) = 0;
	}
}

init_server(ms, pnum)
my_socket* ms;
int pnum;
{
        socklen_t slen;
        size_t len;
        sighandler_t old_handler, new_handler;
        my_socket client;
        new_handler = handler;
        errno = 0;
        old_handler = signal(SIGALRM, new_handler);
        if (old_handler == SIG_ERR)
        {
                perror("init_server::signal()");
                exit(1);
        }       
        init(ms, pnum);
        creat_socket(ms);
        bind_socket(ms);
        reuse_port(ms->sfd);	
}

shut_server(sfd)
int sfd;
{
	close_socket(sfd);
}

static server_creat_file(path)
const char* path;
{
	int fd, res;
	errno = 0;
	fd = open(path, O_CREAT | O_RDONLY | O_WRONLY, 0666);
	if (fd == -1)
	{
		perror("server_creat_file()\n");
		exit(2);
	}
	close(fd);
}

run_server(ms, pnum, state, msg)
my_socket* ms;
int pnum;
int state;
char* msg;
{
	socklen_t slen;
	size_t len;
	int i;
	my_socket client;
	i = 0;
	alarm(time_to_wait);
	for (;;)
	{
		if (i == 2)
		{	
			printf("server path : %s\n", path);
			server_creat_file(path);
			break;
		}	
		recieve_datagram(ms->sfd, msg, datagram_cap, (struct sockaddr*)&(client.sin), &slen);
		len = strlen(msg);
		*(msg + len) = 0;
		if (len > 0)
		{	
			printf("Got the message : %s\n", msg);
			if (!i)
				path_concat(path, msg, NULL);
			else
				path_concat(path, NULL, msg);
			clear_buffer(msg, len);
			i++;
			continue;
		}		
		if (flag)
		{
			fprintf(stderr, "ERROR: Time expired\n");
			shut_server(ms->sfd);
			exit(2);
		}	
	}
}	
