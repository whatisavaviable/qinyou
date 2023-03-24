// Don't modify this file as it will be overwritten.
//
#include "CDR/CDR.h"
#include "ReturnCode.h"
#include "BasicTypes.h"

#ifndef IDL_ThroughPut_hh
#define IDL_ThroughPut_hh

#ifndef ThroughPut_defined
#define ThroughPut_defined

struct ThroughPut {
  ThroughPut()
	{
		num = 0;
		data = new char[255];
		data[0]= '\0';
	}

  ThroughPut(const ThroughPut  &IDL_s);

  ~ThroughPut(){
		delete data;
		data = NULL;
	}

  	int StructSize()
	{
		int strSize = 0;
		strSize += sizeof(ThroughPut);
		strSize += strlen(data);
		return strSize;
	}
  ThroughPut& operator= (const ThroughPut &IDL_s);

  void Marshal(CDR *cdr) const;
  void UnMarshal(CDR *cdr);

  short num;
char* data;
  
};

typedef sequence<ThroughPut> ThroughPutSeq;

#endif




#endif /*IDL_ThroughPut_hh */
