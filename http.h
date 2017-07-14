#ifndef HTTP_H
#define HTTP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/sendfile.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define BUFSIZE 1024

enum STATUS
{
	ERROR_USE,
	ERROR_SOCKET,
	ERROR_BIND,
	ERROR_LISTEN
};



int http_startup(const char* ip, int port);
int http_getline(int sockfd, char* buf, int length);
void* http_handler_request(void* new_sock);
int http_execute_cgi(int sockfd, const char* path, const char* query_string);

int http_send_html(int sockfd, const char* path, int file_size);
void http_clear_head(int sockfd);
void http_echo_error(int sockfd, int state);

#endif /* HTTP_H */
