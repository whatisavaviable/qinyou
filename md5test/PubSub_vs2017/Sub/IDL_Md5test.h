// Don't modify this file as it will be overwritten.
//
#include "CDR/CDR.h"
#include "ReturnCode.h"
#include "BasicTypes.h"

#ifndef IDL_Md5test_hh
#define IDL_Md5test_hh

#ifndef Md5test_defined
#define Md5test_defined

struct Md5test {
  Md5test()
	{
		data = new char[255];
		data[0]= '\0';
		md5 = new char[255];
		md5[0]= '\0';
	}

  Md5test(const Md5test  &IDL_s);

  ~Md5test(){
		delete data;
		data = NULL;
		delete md5;
		md5 = NULL;
	}

  	int StructSize()
	{
		int strSize = 0;
		strSize += sizeof(Md5test);
		strSize += strlen(data);
		strSize += strlen(md5);
		return strSize;
	}
  Md5test& operator= (const Md5test &IDL_s);

  void Marshal(CDR *cdr) const;
  void UnMarshal(CDR *cdr);

  char* data;
char* md5;
  
};

typedef sequence<Md5test> Md5testSeq;

#endif




#endif /*IDL_Md5test_hh */
