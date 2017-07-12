#include "http.h"



static void http_usage(const char* proc)
{
	printf("Usage:%s [server_ip] [ server_Port]\n");
}

int main(int argc, char*argv[])
{
	if( argc != 3)
	{
		http_usage(argv[0]);
		return ERROR_USE;
	}

	int listen_sock = http_startup(argv[1], atoi(argv[2]));


	while(1)
	{
		struct sockaddr_in client;
		socklen_t len = sizeof(client); 
		int new_sock = accept(listen_sock, (struct sockaddr*)&client, &len);

		if(new_sock < 0 )
		{
			perror("error:accept()");
			continue;
		}

		pthread_t tid;
		pthread_create(&tid, NULL, http_handler_request, (void*)new_sock);
		pthread_detach(tid);

	}

	return 0;
}
