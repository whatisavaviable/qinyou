// Don't modify this file as it will be overwritten.
//
#include "IDL_ThroughPut.h"

ThroughPut::ThroughPut(const ThroughPut &IDL_s){
  num = IDL_s.num;
  data = IDL_s.data;
}

ThroughPut& ThroughPut::operator= (const ThroughPut &IDL_s){
  if (this == &IDL_s) return *this;
  num = IDL_s.num;
  data = IDL_s.data;
  return *this;
}

void ThroughPut::Marshal(CDR *cdr) const {
  cdr->PutShort(num);
  cdr->PutString(data);
}

void ThroughPut::UnMarshal(CDR *cdr){
  cdr->GetShort(num);
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

