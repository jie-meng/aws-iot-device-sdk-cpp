#include <iostream>

#include "../IOTClient/IOTClientWrapper.h"
#include "AWSIOTDevice.h"

void CALLING_CONVENTION aws_iot_startLogging()
{
    iot_client_startLogging();
}

void CALLING_CONVENTION aws_iot_stopLogging()
{
    iot_client_stopLogging();
}

int CALLING_CONVENTION aws_iot_init(const char* config_file_path)
{
    return static_cast<int>(iot_client_init(config_file_path));
}

int CALLING_CONVENTION aws_iot_connect()
{
    return static_cast<int>(iot_client_connect());
}

int CALLING_CONVENTION aws_iot_disconnect()
{
    return static_cast<int>(iot_client_disconnect());
}

int CALLING_CONVENTION aws_iot_publish(const char* topic_name, const char* payload)
{
    return static_cast<int>(iot_client_publish(topic_name, payload));
}
