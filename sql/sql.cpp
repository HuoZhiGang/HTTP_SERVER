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

void SqlConnector::connect()
{

	cout << "----------------" << endl;
	cerr << "user:" << user << endl;
	cerr << "ip:" << ip << endl;
	cerr << "passwd:" << passwd << endl;
	cerr << "port:" << port << endl;
	cerr << "db:" << db << endl;
	cout << "----------------" << endl;
	if(mysql_real_connect(connector, ip.c_str(),\
				         user.c_str(), passwd.c_str(),\
						 db.c_str(), port, NULL, 0))
	{
		cerr << "connect successful" <<endl;
	}
	else
	{
		cerr << "connect faild" << endl;
	}
}

void SqlConnector::insert(const std::string& name, 
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
		std::cerr << "insert faild" << std::endl;
	else
	{
		std::cerr << "insert success" << std::endl;
	}
}


void SqlConnector::select()
{
	std::string select("select * from student");

	if( mysql_query( connector, select.c_str()) == 0)
	{
		cerr << "------select success------" << endl;
	}
	else
	{
		cerr << "------select fail  -------" << endl;
	}
}


SqlConnector::~SqlConnector()
{
	mysql_close(connector);
}
