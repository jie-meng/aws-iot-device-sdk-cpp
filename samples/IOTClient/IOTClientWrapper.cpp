#include <iostream>

#include "IOTClient.hpp"
#include "IOTClientWrapper.h"

awsiotsdk::IOTClient g_iot_client;

void iot_client_startLogging()
{
    awsiotsdk::IOTClient::startLogging();
}

void iot_client_stopLogging()
{
    awsiotsdk::IOTClient::stopLogging();
}

int iot_client_init(const char* config_file_path)
{
    return static_cast<int>(awsiotsdk::IOTClient::init(config_file_path));
}

int iot_client_connect()
{
    return static_cast<int>(g_iot_client.Connect());
}

int iot_client_disconnect()
{
    return static_cast<int>(g_iot_client.Disconnect());
}

int iot_client_publish(const char* topic_name, const char* payload)
{
    return static_cast<int>(g_iot_client.PublishAsync(topic_name, payload));
}
