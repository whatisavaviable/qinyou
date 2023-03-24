#include "IDL_DataReader.h"

TimeDelayDataReader::TimeDelayDataReader(DataReaderImpl * pDataReaderImpl)
	:DataReader(pDataReaderImpl)
{
}

TimeDelayDataReader::~TimeDelayDataReader() 
{
}

TimeDelayDataReader* TimeDelayDataReader::narrow(DataReader* pDataReader) 
{
	if (!pDataReader)
		return NULL;

	TimeDelayDataReader *aTimeDelayDataReader = (TimeDelayDataReader*)pDataReader;
	return aTimeDelayDataReader;
}

ReturnCode_t TimeDelayDataReader::take(TimeDelaySeq & data_values, SampleInfoSeq & sample_infos, int max_samples, SampleStateKind sample_states, ViewStateKind view_states, InstanceStateKind instance_states)
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

ReturnCode_t TimeDelayDataReader::read(TimeDelaySeq & data_values, SampleInfoSeq & sample_infos, int max_samples, SampleStateKind sample_states, ViewStateKind view_states, InstanceStateKind instance_states)
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

ReturnCode_t TimeDelayDataReader::take_next_sample(TimeDelay& receivedData, SampleInfo& sample_info)
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

ReturnCode_t TimeDelayDataReader::read_next_sample(TimeDelay& receivedData, SampleInfo& sample_info)
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

ReturnCode_t TimeDelayDataReader::return_loan(TimeDelaySeq& data_values, SampleInfoSeq& sample_infos)
{
	return ReturnCode_t();
}

