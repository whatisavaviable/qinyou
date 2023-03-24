#ifndef _IDL_TYPESUPPORT_H_INCLUDED_ 
#define _IDL_TYPESUPPORT_H_INCLUDED_
#define _CRT_SECURE_NO_DEPRECATE；

#include<md5.c>
#include <cstring>
#include "IDL_DataWriter.h"
#include "IDL_DataReader.h"
#include "DDS/TypeSupport.h"
#include "md5.h"
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
		std::cout<<c<<"  接收到的md5 = "<< pMd5test->md5 <<std::endl;
		MD5_CTX md5c;
		char temp[8] = { 0 };
		unsigned char digest[16];
		unsigned char decrypt[16] = { 0 };
		unsigned char decrypt32[64] = { 0 };

		MD5Init(&md5c);
		MD5Update(&md5c, (unsigned char *)pMd5test->data, strlen(pMd5test->data));
		MD5Final(&md5c, decrypt);

		strcpy_s((char *)decrypt32,sizeof(decrypt32), "");
		for (i = 0; i < 16; i++)
		{
			sprintf_s(temp, "%02x", decrypt[i]);
			strcat_s((char *)decrypt32, sizeof(decrypt32),temp);
		}//计算MD5=decrypt32

		std::cout<<c<<"  计算出的的md5 = "<< (char*)decrypt32<<std::endl;
		if (strcmp((char*)decrypt32, (char*)pMd5test->md5))
		{
			std::cout << "MD5不一致！！！！" << endl;
		}

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
