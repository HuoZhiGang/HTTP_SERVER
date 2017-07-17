#include "sql.h"


SqlConnector::SqlConnector(const std::string _user,
					       const std::string _passwd,
						   const std::string _ip,
						   const std::string _db,
						   const int& _port)
	 : user(_user)
	 , passwd(_passwd)
	 , ip(_ip)
	 , db(_db)
	 , port(_port)
{
	connector = mysql_init(NULL);
}

bool SqlConnector::connect()
{
	if(mysql_real_connect(connector, ip.c_str(),\
				         user.c_str(), passwd.c_str(),\
						 db.c_str(), port, NULL, 0))
		return true;

	return false;
}

bool SqlConnector::insert(const std::string& name, 
			 				  const std::string& sex,
			   				  const std::string& hobby,
			   				  const std::string& school)
{
	std::string insert("INSERT student(name, sex, hobby, school) values('");

	insert += name;
	insert += "','";
	insert += sex;
	insert += "','";
	insert += hobby;
	insert += "','";
	insert += school;
	insert += "')";

	if( mysql_query(connector, insert.c_str()))
		return false;
	return true;
}


bool SqlConnector::select()
{
	std::string select("select * from student");

	if( mysql_query( connector, select.c_str()) == 0)
	{
		MYSQL_RES *res = mysql_store_result(connector);

		if(res)
		{
			// get the row of the query result
			int rows = mysql_num_rows(res);
			//get the field of the query result 
			int fields = mysql_num_fields(res);
			MYSQL_FIELD *fd = NULL;

			// get the name of the field
			for(; fd = mysql_fetch_field(res); )
			{
				cout << fd->name << "--";
			}

			cout << "<br>";
			// print row and field 
			int i = 0;
			for (; i < rows; ++i)
			{
				MYSQL_ROW row = mysql_fetch_row(res);
				int j = 0;
				for(; j < fields; j++)
					cout << row[j] << "--";

				cout << "<br>";
			}
			return true;
		}
	}
	return false;
}


SqlConnector::~SqlConnector()
{
	mysql_close(connector);
}
