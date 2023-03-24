#ifndef _IDL_DATAWRITER_H_INCLUDED_
#define _IDL_DATAWRITER_H_INCLUDED_
#include "ReturnCode.h"
#include "BasicTypes.h"
#include "DDS/DomainParticipantFactory.h"
#include "DDS/Topic.h"
#include "DDS/Publisher.h"
#include "DDS/DataWriter.h"
#include "IDL_timedelaytest.h"
class DataWriterImpl;

class TimeDelayDataWriter : public DataWriter
{
public:
	TimeDelayDataWriter(DataWriterImpl* pDataWriterImpl);

	~TimeDelayDataWriter();

	static TimeDelayDataWriter* narrow(DataWriter* pDataWriter);

	ReturnCode_t write(TimeDelay& data,const InstanceHandle_t & handle);

	ReturnCode_t write_w_timestamp(TimeDelay& data,const InstanceHandle_t & handle, const Time_t& timestamp);

};

#endif
