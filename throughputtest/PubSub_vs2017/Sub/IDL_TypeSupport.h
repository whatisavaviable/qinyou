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
		ListData.push_back("struct ThroughPut{");
		ListData.push_back("short num;");
		ListData.push_back("string 255 data;");
		ListData.push_back("};");
	}
}

class ThroughPutTypeSupport : public TypeSupport {
public:
	static ThroughPut* create_data()
	{
		return new ThroughPut;
	}

	static ReturnCode_t delete_data(ThroughPut* pThroughPut)
	{
		delete pThroughPut;
		pThroughPut = NULL;
		return ReturnCode_t();
	}

	static void print_data(ThroughPut* pThroughPut,int package,int layer = 0)
	{
		char *c = new char[layer];
		int i = 0;
		for (; i < layer; i++)
		{
			c[i] = '\t';
		}
		c[i] = '\0';
		float loss = (float)pThroughPut->num/package;
		std::cout<<c<<"ThroughPut:"<<"dont know"<<std::endl;
		std::cout<<"  losspackagepercent:"<<loss<<std::endl;
		
	}

	static const char* get_type_name()
	{
		return "ThroughPut";
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
