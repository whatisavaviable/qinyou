#include "IDL_DataReader.h"

Md5testDataReader::Md5testDataReader(DataReaderImpl * pDataReaderImpl)
	:DataReader(pDataReaderImpl)
{
}

Md5testDataReader::~Md5testDataReader() 
{
}

Md5testDataReader* Md5testDataReader::narrow(DataReader* pDataReader) 
{
	if (!pDataReader)
		return NULL;

	Md5testDataReader *aMd5testDataReader = (Md5testDataReader*)pDataReader;
	return aMd5testDataReader;
}

ReturnCode_t Md5testDataReader::take(Md5testSeq & data_values, SampleInfoSeq & sample_infos, int max_samples, SampleStateKind sample_states, ViewStateKind view_states, InstanceStateKind instance_states)
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

ReturnCode_t Md5testDataReader::read(Md5testSeq & data_values, SampleInfoSeq & sample_infos, int max_samples, SampleStateKind sample_states, ViewStateKind view_states, InstanceStateKind instance_states)
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

ReturnCode_t Md5testDataReader::take_next_sample(Md5test& receivedData, SampleInfo& sample_info)
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

ReturnCode_t Md5testDataReader::read_next_sample(Md5test& receivedData, SampleInfo& sample_info)
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

ReturnCode_t Md5testDataReader::return_loan(Md5testSeq& data_values, SampleInfoSeq& sample_infos)
{
	return ReturnCode_t();
}

