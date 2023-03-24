#ifndef _IDL_DATAWRITER_H_INCLUDED_
#define _IDL_DATAWRITER_H_INCLUDED_
#include "ReturnCode.h"
#include "BasicTypes.h"
#include "DDS/DomainParticipantFactory.h"
#include "DDS/Topic.h"
#include "DDS/Publisher.h"
#include "DDS/DataWriter.h"
#include "IDL_ThroughPut.h"
class DataWriterImpl;

class ThroughPutDataWriter : public DataWriter
{
public:
	ThroughPutDataWriter(DataWriterImpl* pDataWriterImpl);

	~ThroughPutDataWriter();

	static ThroughPutDataWriter* narrow(DataWriter* pDataWriter);

	ReturnCode_t write(ThroughPut& data,const InstanceHandle_t & handle);

	ReturnCode_t write_w_timestamp(ThroughPut& data,const InstanceHandle_t & handle, const Time_t& timestamp);

};

#endif
