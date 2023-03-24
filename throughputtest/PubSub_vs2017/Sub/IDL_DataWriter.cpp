#include "IDL_DataWriter.h"

ThroughPutDataWriter::ThroughPutDataWriter(DataWriterImpl * pDataWriterImpl)
	: DataWriter(pDataWriterImpl)
{
}

ThroughPutDataWriter::~ThroughPutDataWriter()
{
}

ThroughPutDataWriter* ThroughPutDataWriter::narrow(DataWriter* pDataWriter) 
{
	if (!pDataWriter)
		return NULL;
	ThroughPutDataWriter *aThroughPutDataWriter = (ThroughPutDataWriter*)pDataWriter;
    return aThroughPutDataWriter;
}

ReturnCode_t ThroughPutDataWriter::write(ThroughPut& data, const InstanceHandle_t & handle){
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

ReturnCode_t ThroughPutDataWriter::write_w_timestamp(ThroughPut& data, const InstanceHandle_t & handle, const Time_t& timestamp){
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

