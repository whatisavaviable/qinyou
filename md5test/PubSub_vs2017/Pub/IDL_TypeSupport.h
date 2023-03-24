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
		ListData.push_back("struct Md5test{");
		ListData.push_back("string 255 data;");
		ListData.push_back("string 255 md5;");
		ListData.push_back("};");
	}
}

class Md5testTypeSupport : public TypeSupport {
public:
	static Md5test* create_data()
	{
		return new Md5test;
	}

	static ReturnCode_t delete_data(Md5test* pMd5test)
	{
		delete pMd5test;
		pMd5test = NULL;
		return ReturnCode_t();
	}

	static void print_data(Md5test* pMd5test,int layer = 0)
	{
		char *c = new char[layer];
		int i = 0;
		for (; i < layer; i++)
		{
			c[i] = '\t';
		}
		c[i] = '\0';
		std::cout<<c<<"Md5test:"<<std::endl;
		std::cout<<c<<"  data = "<< pMd5test->data <<std::endl;
		std::cout<<c<<"  md5 = "<< pMd5test->md5 <<std::endl;
	}

	static const char* get_type_name()
	{
		return "Md5test";
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
