#ifndef _IDL_DATAWRITER_H_INCLUDED_
#define _IDL_DATAWRITER_H_INCLUDED_
#include "ReturnCode.h"
#include "BasicTypes.h"
#include "DDS/DomainParticipantFactory.h"
#include "DDS/Topic.h"
#include "DDS/Publisher.h"
#include "DDS/DataWriter.h"
#include "IDL_Md5test.h"
class DataWriterImpl;

class Md5testDataWriter : public DataWriter
{
public:
	Md5testDataWriter(DataWriterImpl* pDataWriterImpl);

	~Md5testDataWriter();

	static Md5testDataWriter* narrow(DataWriter* pDataWriter);

	ReturnCode_t write(Md5test& data,const InstanceHandle_t & handle);

	ReturnCode_t write_w_timestamp(Md5test& data,const InstanceHandle_t & handle, const Time_t& timestamp);

};

#endif
