// Don't modify this file as it will be overwritten.
//
#include "IDL_timedelaytest.h"

TimeDelay::TimeDelay(const TimeDelay &IDL_s){
  data = IDL_s.data;
}

TimeDelay& TimeDelay::operator= (const TimeDelay &IDL_s){
  if (this == &IDL_s) return *this;
  data = IDL_s.data;
  return *this;
}

void TimeDelay::Marshal(CDR *cdr) const {
  cdr->PutString(data);
}

void TimeDelay::UnMarshal(CDR *cdr){
  {
    char *IDL_str;
    cdr->GetString(IDL_str);
    if(data != NULL )
    {
        delete data;
        data = NULL;
    }
    data = IDL_str;
  }
}

