#ifndef DELIVER_SYSTEM_H
#define DELIVER_SYSTEM_H
#include "socket_lib.h"
#include <dirent.h>
#include <string.h>
enum {back_slash = '/'};
void find_recipient(const char* dir_name, const char* recipient_name, int* is_found, char* recipient_path);
#endif
