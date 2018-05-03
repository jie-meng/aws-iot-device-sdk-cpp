#include "AWSIOTDevice.h"
#include "AWSIOTDeviceWrapper.h"

void aws_iot_wrapper_startLogging()
{
    aws_iot_startLogging();
}

void aws_iot_wrapper_stopLogging()
{
    aws_iot_stopLogging();
}

int aws_iot_wrapper_init(const char* config_file_path)
{
    return aws_iot_init(config_file_path);
}

int aws_iot_wrapper_connect()
{
    return aws_iot_connect();
}

int aws_iot_wrapper_disconnect()
{
    return aws_iot_disconnect();
}

int aws_iot_wrapper_publish(const char* topic_name, const char* payload)
{
    return aws_iot_publish(topic_name, payload);
}
