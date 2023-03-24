#ifndef _IDL_DATAREADER_H_INCLUDED_
#define _IDL_DATAREADER_H_INCLUDED_

#include "ReturnCode.h"
#include "BasicTypes.h"
#include "IDL_ThroughPut.h"
#include "DDS/DomainParticipantFactory.h"
#include "DDS/Topic.h"
#include "DDS/Subscriber.h"
#include "DDS/DataReader.h"
#include "DDS/Listener/DataReaderListener.h"

class DataReaderImpl;

class ThroughPutDataReader : public DataReader 
{
public:
	ThroughPutDataReader(DataReaderImpl* pDataReaderImpl);

	~ThroughPutDataReader();

	static ThroughPutDataReader* narrow(DataReader* pDataReader);

	ReturnCode_t take(ThroughPutSeq& data_values, SampleInfoSeq & sample_infos, int max_samples, SampleStateKind sample_states, ViewStateKind view_states, InstanceStateKind instance_states);

	ReturnCode_t read(ThroughPutSeq& data_values, SampleInfoSeq & sample_infos, int max_samples, SampleStateKind sample_states, ViewStateKind view_states, InstanceStateKind instance_states);

	ReturnCode_t take_next_sample(ThroughPut& receivedData, SampleInfo & sample_info);

	ReturnCode_t read_next_sample(ThroughPut& receivedData, SampleInfo& sample_info);

	ReturnCode_t return_loan(ThroughPutSeq& data_values, SampleInfoSeq& sample_infos);


};

#endif
