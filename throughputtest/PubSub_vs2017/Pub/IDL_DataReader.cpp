#include "IDL_DataReader.h"

ThroughPutDataReader::ThroughPutDataReader(DataReaderImpl * pDataReaderImpl)
	:DataReader(pDataReaderImpl)
{
}

ThroughPutDataReader::~ThroughPutDataReader() 
{
}

ThroughPutDataReader* ThroughPutDataReader::narrow(DataReader* pDataReader) 
{
	if (!pDataReader)
		return NULL;

	ThroughPutDataReader *aThroughPutDataReader = (ThroughPutDataReader*)pDataReader;
	return aThroughPutDataReader;
}

ReturnCode_t ThroughPutDataReader::take(ThroughPutSeq & data_values, SampleInfoSeq & sample_infos, int max_samples, SampleStateKind sample_states, ViewStateKind view_states, InstanceStateKind instance_states)
{
	UserDataVector userDataVector;
	DataReader::take(userDataVector, sample_infos, max_samples, sample_states, view_states, instance_states);

	data_values.ensure_length(userDataVector.size(), userDataVector.size());
	for (int i = 0; i < userDataVector.size(); i++)
	{
		CDR* CDRData = new CDR((unsigned char *)userDataVector[i].pData + 4, userDataVector[i].ilength - 4, MY_BYTE_SEX, 1);
		data_values[i].UnMarshal(CDRData);
		if (CDRData)
			delete CDRData;
		delete userDataVector[i].pData;
	}
	return ReturnCode_t();
}

ReturnCode_t ThroughPutDataReader::read(ThroughPutSeq & data_values, SampleInfoSeq & sample_infos, int max_samples, SampleStateKind sample_states, ViewStateKind view_states, InstanceStateKind instance_states)
{
	UserDataVector userDataVector;
	DataReader::read(userDataVector, sample_infos, max_samples, sample_states, view_states, instance_states);

	data_values.ensure_length(userDataVector.size(), userDataVector.size());
	for (int i = 0; i < userDataVector.size(); i++)
	{
		CDR* CDRData = new CDR((unsigned char *)userDataVector[i].pData + 4, userDataVector[i].ilength - 4, MY_BYTE_SEX, 1);
		data_values[i].UnMarshal(CDRData);
		if (CDRData)
			delete CDRData;
		delete userDataVector[i].pData;
	}
	return ReturnCode_t();
}

ReturnCode_t ThroughPutDataReader::take_next_sample(ThroughPut& receivedData, SampleInfo& sample_info)
{
	UserData userData;
	DataReader::take_next_sample(userData, sample_info);
	CDR* CDRData = new CDR((unsigned char *)userData.pData + 4, userData.ilength - 4, MY_BYTE_SEX, 1);
	receivedData.UnMarshal(CDRData);
	if (CDRData)
	{
		delete CDRData;
	}
	return ReturnCode_t();
}

ReturnCode_t ThroughPutDataReader::read_next_sample(ThroughPut& receivedData, SampleInfo& sample_info)
{
	UserData userData;
	DataReader::read_next_sample(userData, sample_info);
	CDR* CDRData = new CDR((unsigned char *)userData.pData + 4, userData.ilength - 4, MY_BYTE_SEX, 1);
	receivedData.UnMarshal(CDRData);
	if (CDRData)
	{
		delete CDRData;
	}
	return ReturnCode_t();
}

ReturnCode_t ThroughPutDataReader::return_loan(ThroughPutSeq& data_values, SampleInfoSeq& sample_infos)
{
	return ReturnCode_t();
}

