#ifndef _IDL_TYPESUPPORT_H_INCLUDED_ 
#define _IDL_TYPESUPPORT_H_INCLUDED_

#include <string>
using std::string;
#include "IDL_DataWriter.h"
#include "IDL_DataReader.h"
#include "DDS/TypeSupport.h"

#include "DDS/DomainParticipant.h"
class DomainParticipant;

list<string> ListData;
static void initList()
{	if (ListData.size() <= 0)
	{
		ListData.push_back("struct TimeDelay{");
		ListData.push_back("string 255 data;");
		ListData.push_back("};");
	}
}

class TimeDelayTypeSupport : public TypeSupport {
public:
	static TimeDelay* create_data()
	{
		int data = NULL;
		cout << "输入数据大小：" << endl;
		cin >> data;
		getchar();
		return new TimeDelay(data);//输入要传输的数据
	}

	static ReturnCode_t delete_data(TimeDelay* pTimeDelay)
	{
		delete pTimeDelay;
		pTimeDelay = NULL;
		return ReturnCode_t();
	}

	static void print_data(TimeDelay* pTimeDelay,int layer = 0)
	{
		char *c = new char[layer];
		int i = 0;
		for (; i < layer; i++)
		{
			c[i] = '\t';
		}
		c[i] = '\0';
		std::cout<<c<<"TimeDelay:"<<std::endl;
		std::cout<<c<<"  data = "<< pTimeDelay->data <<std::endl;
	}

	static const char* get_type_name()
	{
		return "TimeDelay";
	}

	static int register_type(DomainParticipant* participant, string type_name)
	{
		if (type_name.empty())
			type_name = get_type_name();

		initList();
		return participant->register_type(type_name,ListData);
	}
};

#endif
