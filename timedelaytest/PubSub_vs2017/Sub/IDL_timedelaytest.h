// Don't modify this file as it will be overwritten.
//
#include "CDR/CDR.h"
#include "ReturnCode.h"
#include "BasicTypes.h"

#ifndef IDL_timedelaytest_hh
#define IDL_timedelaytest_hh

#ifndef TimeDelay_defined
#define TimeDelay_defined

struct TimeDelay {
  TimeDelay()
	{
		data = new char[255];
		data[0]= '\0';
	}

  TimeDelay(const TimeDelay  &IDL_s);

  ~TimeDelay(){
		delete data;
		data = NULL;
	}

  	int StructSize()
	{
		int strSize = 0;
		strSize += sizeof(TimeDelay);
		strSize += strlen(data);
		return strSize;
	}
  TimeDelay& operator= (const TimeDelay &IDL_s);

  void Marshal(CDR *cdr) const;
  void UnMarshal(CDR *cdr);

  char* data;
  
};

typedef sequence<TimeDelay> TimeDelaySeq;

#endif




#endif /*IDL_timedelaytest_hh */
