// Don't modify this file as it will be overwritten.
//
#include "IDL_Md5test.h"

Md5test::Md5test(const Md5test &IDL_s){
  data = IDL_s.data;
  md5 = IDL_s.md5;
}

Md5test& Md5test::operator= (const Md5test &IDL_s){
  if (this == &IDL_s) return *this;
  data = IDL_s.data;
  md5 = IDL_s.md5;
  return *this;
}

void Md5test::Marshal(CDR *cdr) const {
  cdr->PutString(data);
  cdr->PutString(md5);
}

void Md5test::UnMarshal(CDR *cdr){
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
  {
    char *IDL_str;
    cdr->GetString(IDL_str);
    if(md5 != NULL )
    {
        delete md5;
        md5 = NULL;
    }
    md5 = IDL_str;
  }
}

