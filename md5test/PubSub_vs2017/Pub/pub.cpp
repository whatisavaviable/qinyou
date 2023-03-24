/**********************************************************
*****************发布端程序publisher.cpp********************
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include "md5.h"
#include<md5.c>

/* IDL_TypeSupport.h中包含所有依赖的头文件 */
#include "IDL_TypeSupport.h"

/* 删除所有实体 */
static int publisher_shutdown(DomainParticipant *participant)
{
	ReturnCode_t retcode;
	int status = 0;

	if (participant != NULL) {
		retcode = participant->delete_contained_entities();
		if (retcode != RETCODE_OK) {
			fprintf(stderr, "delete_contained_entities error %d\n", retcode);
			status = -1;
		}

		retcode = DomainParticipantFactory::get_instance()->delete_participant(participant);
		if (retcode != RETCODE_OK) {
			fprintf(stderr, "delete_participant error %d\n", retcode);
			status = -1;
		}
	}

	return status;
}

/* 发布者函数 */
extern "C" int publisher_main(int domainId, int sample_count)
{
	DomainParticipant *participant = NULL;
	Publisher *publisher = NULL;
	Topic *topic = NULL;
	DataWriter *writer = NULL;
	Md5testDataWriter* Md5test_writer = NULL;
	Md5test *instance = NULL;
	ReturnCode_t retcode;
	InstanceHandle_t instance_handle = HANDLE_NIL;
	const char *type_name = NULL;
	int count = 0;

	/* 1. 创建一个participant，可以在此处定制participant的QoS */
	/* 建议1：在程序启动后优先创建participant，进行资源初始化*/
	/* 建议2：相同的domainId只创建一次participant，重复创建会占用大量资源 */
	participant = DomainParticipantFactory::get_instance()->create_participant(
		domainId, PARTICIPANT_QOS_DEFAULT/* participant默认QoS */,
		NULL /* listener */, STATUS_MASK_NONE);
	if (participant == NULL) {
		fprintf(stderr, "create_participant error\n");
		publisher_shutdown(participant);
		return -1;
	}

	/* 2. 创建一个publisher，可以在创建publisher的同时定制其QoS  */
	/* 建议1：在程序启动后优先创建publisher */
	/* 建议2：一个participant下创建一个publisher即可，无需重复创建 */
	publisher = participant->create_publisher(
		PUBLISHER_QOS_DEFAULT /* 默认QoS */,
		NULL /* listener */, STATUS_MASK_NONE);
	if (publisher == NULL) {
		fprintf(stderr, "create_publisher error\n");
		publisher_shutdown(participant);
		return -1;
	}

	/* 3. 在创建主题之前注册数据类型 */
	/* 建议1：在程序启动后优先进行注册 */
	/* 建议2：一个数据类型注册一次即可 */
	type_name = Md5testTypeSupport::get_type_name();
	retcode = Md5testTypeSupport::register_type(
		participant, type_name);
	if (retcode != RETCODE_OK) {
		fprintf(stderr, "register_type error %d\n", retcode);
		publisher_shutdown(participant);
		return -1;
	}

	/* 4. 创建主题，并定制主题的QoS  */
	/* 建议1：在程序启动后优先创建Topic */
	/* 建议2：一种主题名创建一次即可，无需重复创建 */
	topic = participant->create_topic(
		"Example UserDataType"/* 主题名 */,
		type_name /* 类型名 */, TOPIC_QOS_DEFAULT/* 默认QoS */,
		NULL /* listener */, STATUS_MASK_NONE);
	if (topic == NULL) {
		fprintf(stderr, "create_topic error\n");
		publisher_shutdown(participant);
		return -1;
	}

	/* 5. 创建datawriter，并定制datawriter的QoS  */
	/* 建议1：在程序启动后优先创建datawriter */
	/* 建议2：创建一次即可，无需重复创建 */
	/* 建议3：在程序退出时再进行释放 */
	/* 建议4：避免打算发送数据时创建datawriter，发送数据后删除，该做法消耗资源，影响性能 */
	writer = publisher->create_datawriter(
		topic, DATAWRITER_QOS_DEFAULT/* 默认QoS */,
		NULL /* listener */, STATUS_MASK_NONE);
	if (writer == NULL) {
		fprintf(stderr, "create_datawriter error\n");
		publisher_shutdown(participant);
		return -1;
	}
	Md5test_writer = Md5testDataWriter::narrow(writer);
	if (Md5test_writer == NULL) {
		fprintf(stderr, "DataWriter narrow error\n");
		publisher_shutdown(participant);
		return -1;
	}

	/* 6. 创建一个数据样本 */
	/* 建议：该数据为new出来的，使用后用户需要调用delete_data进行释放内存*/
	instance = Md5testTypeSupport::create_data();
	if (instance == NULL) {
		fprintf(stderr, "UserDataTypeTypeSupport::create_data error\n");
		publisher_shutdown(participant);
		return -1;
	}

	//此处可以修改数据的值
	instance->data = const_cast<char *>("this is my data");
	MD5_CTX md5c;
	char temp[8] = { 0 };
	int i;
	unsigned char digest[16];
	unsigned char decrypt[16] = { 0 };
	unsigned char decrypt32[64] = { 0 };
	
	MD5Init(&md5c);
	MD5Update(&md5c, (unsigned char *)instance->data, strlen(instance->data));
	MD5Final(&md5c, decrypt);

	strcpy((char *)decrypt32, "");
	 for (i = 0; i < 16; i++)
	{
		sprintf(temp, "%02x", decrypt[i]);
		strcat((char *)decrypt32, temp);
	}

	instance->md5 = (char*)decrypt32;//md5值
	



	/* 7. 主循环 ，发送数据 */
	for (count = 0; (sample_count == 0) || (count < sample_count); ++count) {

		retcode = Md5test_writer->write(*instance, instance_handle);
		if (retcode != RETCODE_OK) {
			fprintf(stderr, "write error %d\n", retcode);
		}
		else
			fprintf(stderr, "%d : write  successfully . . \n", count);
#ifdef ULINX_LINUX
		sleep(1);
#elif (defined( ULINX_WIN) ||  defined(_WIN32))
		Sleep(1000);
#endif //沉睡一秒

	}

	/* 8. 删除数据样本 */
	retcode = Md5testTypeSupport::delete_data(instance);
	if (retcode != RETCODE_OK) {
		fprintf(stderr, "UserDataTypeTypeSupport::delete_data error %d\n", retcode);
	}

	/* 9. 删除所有实例 */
	return publisher_shutdown(participant);
}

int main(int argc, char *argv[])
{
	int domain_id = 0;
	int sample_count = 0; /* 无限循环 */

	if (argc >= 2) {
		domain_id = atoi(argv[1]);  /* 发送至域domain_id */
	}
	if (argc >= 3) {
		sample_count = atoi(argv[2]); /* 发送sample_count次 */
	}

	return publisher_main(domain_id, sample_count);
}
