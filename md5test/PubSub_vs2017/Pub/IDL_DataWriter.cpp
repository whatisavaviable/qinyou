#include "IDL_DataWriter.h"

Md5testDataWriter::Md5testDataWriter(DataWriterImpl * pDataWriterImpl)
	: DataWriter(pDataWriterImpl)
{
}

Md5testDataWriter::~Md5testDataWriter()
{
}

Md5testDataWriter* Md5testDataWriter::narrow(DataWriter* pDataWriter) 
{
	if (!pDataWriter)
		return NULL;
	Md5testDataWriter *aMd5testDataWriter = (Md5testDataWriter*)pDataWriter;
    return aMd5testDataWriter;
}

ReturnCode_t Md5testDataWriter::write(Md5test& data, const InstanceHandle_t & handle){
	char *buf = new char[DEFAULT_CDRSIZE];
	CDR* CDRData = NULL;
	ReturnCode_t ret = RETCODE_OK;
	CDRData = new CDR((unsigned char *)buf, DEFAULT_CDRSIZE, MY_BYTE_SEX, 1);
	data.Marshal(CDRData);
	char* myData = CDRData->GetBufferPtr();
	int typeSize = CDRData->GetContentLen();
	char* pDataVale = new char[typeSize + 4]();
	pDataVale[1] = 0x01;
	memcpy(pDataVale + 4, myData, typeSize);
	//InstanceHandle_t handle = HANDLE_NIL;
	ret = DataWriter::write(pDataVale, typeSize + 4, handle);
	buf = (char*)CDRData->pReal_buffer;
	if (buf)
		delete buf;
	if (CDRData)
		delete CDRData;
	if (pDataVale)
		delete pDataVale;
	return ret;
}

ReturnCode_t Md5testDataWriter::write_w_timestamp(Md5test& data, const InstanceHandle_t & handle, const Time_t& timestamp){
	char *buf = new char[DEFAULT_CDRSIZE];
	CDR* CDRData = NULL;
	ReturnCode_t ret = RETCODE_OK;
	CDRData = new CDR((unsigned char *)buf, DEFAULT_CDRSIZE, MY_BYTE_SEX, 1);
	data.Marshal(CDRData);
	char* myData = CDRData->GetBufferPtr();
	int typeSize = CDRData->GetContentLen();
	char* pDataVale = new char[typeSize + 4]();
	pDataVale[1] = 0x01;
	memcpy(pDataVale + 4, myData, typeSize);
	//InstanceHandle_t handle = HANDLE_NIL;
	ret = DataWriter::write_w_timestamp(pDataVale, typeSize + 4, handle, timestamp);
	buf = (char*)CDRData->pReal_buffer;
	if (buf)
		delete buf;
	if (CDRData)
		delete CDRData;
	if (pDataVale)
		delete pDataVale;
	return ret;
}

