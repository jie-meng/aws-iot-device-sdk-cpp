#include <iostream>

#include "../IOTClient/IOTClientWrapper.h"
#include "AWSIOTDevice.h"

void aws_iot_startLogging()
{
    iot_client_startLogging();
}

void aws_iot_stopLogging()
{
    iot_client_stopLogging();
}

int aws_iot_init(const char* config_file_path)
{
    return static_cast<int>(iot_client_init(config_file_path));
}

int aws_iot_connect()
{
    return static_cast<int>(iot_client_connect());
}

int aws_iot_disconnect()
{
    return static_cast<int>(iot_client_disconnect());
}

int aws_iot_publish(const char* topic_name, const char* payload)
{
    return static_cast<int>(iot_client_publish(topic_name, payload));
}
