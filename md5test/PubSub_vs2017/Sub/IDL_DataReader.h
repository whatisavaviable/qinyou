#ifndef _IDL_DATAREADER_H_INCLUDED_
#define _IDL_DATAREADER_H_INCLUDED_

#include "ReturnCode.h"
#include "BasicTypes.h"
#include "IDL_Md5test.h"
#include "DDS/DomainParticipantFactory.h"
#include "DDS/Topic.h"
#include "DDS/Subscriber.h"
#include "DDS/DataReader.h"
#include "DDS/Listener/DataReaderListener.h"

class DataReaderImpl;

class Md5testDataReader : public DataReader 
{
public:
	Md5testDataReader(DataReaderImpl* pDataReaderImpl);

	~Md5testDataReader();

	static Md5testDataReader* narrow(DataReader* pDataReader);

	ReturnCode_t take(Md5testSeq& data_values, SampleInfoSeq & sample_infos, int max_samples, SampleStateKind sample_states, ViewStateKind view_states, InstanceStateKind instance_states);

	ReturnCode_t read(Md5testSeq& data_values, SampleInfoSeq & sample_infos, int max_samples, SampleStateKind sample_states, ViewStateKind view_states, InstanceStateKind instance_states);

	ReturnCode_t take_next_sample(Md5test& receivedData, SampleInfo & sample_info);

	ReturnCode_t read_next_sample(Md5test& receivedData, SampleInfo& sample_info);

	ReturnCode_t return_loan(Md5testSeq& data_values, SampleInfoSeq& sample_infos);


};

#endif
