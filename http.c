#include "http.h"



int http_startup(const char* ip, int port)
{
	int listen_sock = socket(AF_INET, SOCK_STREAM, 0);

	if(listen_sock < 0)
	{
		perror("error: socket()");
		exit(ERROR_SOCKET);
	}

	int opt = 1;
	setsockopt(listen_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	struct sockaddr_in server;
	bzero(&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(ip);
	server.sin_port = htons(port);

	if(bind(listen_sock, (struct sockaddr*)&server, sizeof(server)) < 0)
	{
		perror("error:bind()");
		exit(ERROR_BIND);
	}

	if(listen(listen_sock, 10)<0)
	{
		perror("error:listen()");
		exit(ERROR_LISTEN);
	}
		
	return listen_sock;
}

int http_getline(int sockfd, char *buf, int buf_length)
{
	char read_char = '\0';
	int  read_idx = 0;

	while( read_char != '\n' && read_idx < buf_length - 1 )
	{
		ssize_t s = recv(sockfd, &read_char, 1, 0); 

		if ( s > 0)
		{
			if ( read_char == '\r')
			{
				recv(sockfd, &read_char, 1, MSG_PEEK);
				if (read_char == '\n')
				{
					recv(sockfd, &read_char, 1, 0);
				}
				else
				{
					read_char = '\n';
				}
			}
			buf [read_idx] = read_char;
			read_idx++;
		}
	}

	buf[read_idx] = '\0';
	return read_idx;
}

void* http_handler_request(void* new_sock)
{
	int sockfd = (int)new_sock;
	char read_buf[BUFSIZE];
	int  read_length = 0;

	read_length = http_getline(sockfd, read_buf, sizeof(read_buf));

#ifdef _DEBUG_
	printf("============================\n");
	printf("GET LINE:\n%s\n", read_buf);
	printf("============================\n");
#else
	printf("release\n");

	char method_buf[BUFSIZE];
	char url_buf[BUFSIZE];
	char path_buf[BUFSIZE];
	// 获取方法字段
	int idx_buf = 0;
	int idx_method = 0;
	while(!isspace(read_buf[idx_buf]) && 
		  idx_buf < sizeof(read_buf)  && 
		  idx_method < sizeof(method_buf)) 
	{
		method_buf[ idx_method ] = read_buf[idx_buf];
		idx_method++;
		idx_buf++;
	}

	method_buf[idx_method] = '\0';

	while(isspace(read_buf[idx_buf]) && idx_buf < sizeof(read_buf))
	{
		idx_buf++;
	}
	// 获取 URL 字段
	int idx_url = 0;

	while(!isspace(read_buf[idx_buf]) && idx_buf < sizeof(read_buf) && idx_url < sizeof(url_buf))
	{
		url_buf[idx_url] = read_buf[idx_buf];
		idx_url++;
		idx_buf++;
	}
	url_buf[idx_url] = '\0';

	printf("METHOD : %s\n", method_buf);
	printf("URL: %s\n", url_buf);

end:
	close(sockfd);
#endif
}



