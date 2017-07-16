#include "sql.h"

int main()
{
	cerr << mysql_get_client_info() << endl;
	cerr << "hello insert_cgi" << endl;

	SqlConnector mysql;
	mysql.connect();


	mysql.insert("Jack","man", "playing", "XPU");

	return 0;
}
