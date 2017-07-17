#include "sql.h"
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <string>


void send_200()
{
	string stat = "HTTP/1.0 200 OK\r\n";
	cout << stat;
	string type = "ContenType: text/html\r\n\r\n";
	cout << type;
}
void send_404()
{
	string stat = "HTTP/1.0 404 NOT FOUND\r\n";
	cout << stat;
	string type = "ContenType: text/html\r\n\r\n";
	cout << type;
}

bool get_arg(char* buf)
{
	char* method = NULL;
	char* arg_string = NULL;
	char* content_length = NULL;

	method = getenv("METHOD");
	if(method && strcasecmp(method, "GET") == 0){
		arg_string = getenv("QUERY_STRING");
		if( !arg_string)
			return false;
		strcpy(buf, arg_string);
	}
	else if (method && strcasecmp(method, "POST") == 0){
		content_length = getenv("CONTENT_LENGTH");
		if( ! content_length){
			return false;
		}
		int i = 0;
		char c = 0;
		int nums = atoi(content_length);
		for(; i < nums; ++i){
			read(0, &c, 1);
			buf[i] = c;
		}
		buf[i] = 0;
		return true;
	}
	return false;
}


int main()
{
	char buf[1024];
	get_arg(buf);
	send_200();
	cout << "<HTML><H1>  ALL user </H1><br>"<<endl;
	SqlConnector mysql;
	if( mysql.connect())
	{
		mysql.select();
	}
	cout << " </HTML>";
	return 0;
}
