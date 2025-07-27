#include "deliver_system.h"
enum {path_len = 255};
enum {stack_cap = 255};
typedef char path_t[path_len];
typedef struct dirent ent_t;
typedef struct
{
	path_t stk[stack_cap];
	int sp;
}stack;

static char path[path_len << 1];
static stack s;

static void path_contact(char* path, const char* path1, const char* path2)
{
	size_t len;
	strcpy(path, path1);
	len = strlen(path1);
	*(path + len) = back_slash;
	*(path + len + 1) = 0;
	strcat(path, path2);
	len = strlen(path);
	*(path + len) = 0;
}

static void stack_init(stack* s)
{
	s->sp = 0;
}

static void is_overflow(stack* s)
{
	return s->sp >= stack_cap ? 1 : 0;
}
static void is_underflow(stack* s)
{
	return s->sp < 0 ? 1 : 0;
}
static void push(stack* s, path_t v)
{
	size_t len;
	if (is_overflow(s))
	{
		fprintf(stderr, "ERROR: Stack overflow\n");
		exit(1);
	}
	len = strlen(v);
	strcpy(s->stk[s->sp], v);
	*(s->stk[s->sp] + len) = 0;
	(s->sp)++;
}

static void pop(stack* s)
{
	if (is_underflow(s))
	{
		fprintf(stderr, "ERROR: Stack underflow\n");
		exit(2);
	}
	(s->sp)--;
}

static char* top(stack* s)
{
	return s->stk[s->sp - 1];
}

static void open_dir(DIR** dir, const char* dir_name)
{
	errno = 0;
	*dir = opendir(dir_name);
	if (!dir)
	{
		perror("open_dir");
		exit(3);
	}	
}

static void close_dir(DIR* dir)
{
        int res;
        errno = 0;
        res = closedir(dir);
        if (res == -1)
        {
                perror("closedir()");
                exit(4);
        }
}

static void read_dir(const char* dir_name, const char* recipient_name, stack* s, int* is_found, char* recipient_path)
{
	ent_t* ent;
	size_t len;
	DIR* dir;
	open_dir(&dir, dir_name);
	while ((ent = readdir(dir)))
	{
		if (0 == strcmp(".", ent->d_name) || 0 == strcmp("..", ent->d_name))
			continue;
		if (ent->d_type == DT_DIR)
		{	
			if (0 == strcmp(ent->d_name, recipient_name))
			{	
				*is_found = 1;
				path_concat(recipient_path, top(s), recipient_name);
				break;
			}	
			path_concat(path, top(s), ent->d_name);
			push(s, path);
			read_dir(top(s), recipient_name, s, is_found, recipient_path);
		}
	}
	pop(s);
	close_dir(dir);	
}

void find_recipient(const char* dir_name, const char* recipient_name, int* is_found, char* recipient_path)
{
	stack_init(&s);
	push(&s, dir_name);
	read_dir(dir_name, recipient_name, &s, is_found, recipient_path);
}	
