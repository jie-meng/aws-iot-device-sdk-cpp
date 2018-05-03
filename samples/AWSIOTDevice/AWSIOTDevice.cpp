#include <iostream>

#include "util/logging/Logging.hpp"
#include "util/logging/LogMacros.hpp"
#include "util/logging/ConsoleLogSystem.hpp"

#include "ConfigCommon.hpp"

#include "IOTClient.hpp"
#include "AWSIOTDevice.h"

using namespace std;

awsiotsdk::IOTClient g_iot_client;

void aws_iot_startLogging()
{
    std::shared_ptr<awsiotsdk::util::Logging::ConsoleLogSystem> p_log_system = std::make_shared<awsiotsdk::util::Logging::ConsoleLogSystem>(awsiotsdk::util::Logging::LogLevel::Info);
    awsiotsdk::util::Logging::InitializeAWSLogging(p_log_system);
}

void aws_iot_stopLogging()
{
    awsiotsdk::util::Logging::ShutdownAWSLogging();
}

int aws_iot_init(const char* config_file_path)
{
    return static_cast<int>(awsiotsdk::ConfigCommon::InitializeCommon(config_file_path));
}

int aws_iot_connect()
{
    return static_cast<int>(g_iot_client.Connect());
}

int aws_iot_disconnect()
{
    return static_cast<int>(g_iot_client.Disconnect());
}

int aws_iot_publish(const char* topic_name, const char* payload)
{
    return static_cast<int>(g_iot_client.PublishAsync(topic_name, payload));
}
