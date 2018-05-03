#include <chrono>
#include <cstring>
#include <iostream>

#ifdef USE_WEBSOCKETS
#include "WebSocketConnection.hpp"
#elif defined USE_MBEDTLS
#include "MbedTLSConnection.hpp"
#else
#include "OpenSSLConnection.hpp"
#endif

#include "util/logging/Logging.hpp"
#include "util/logging/LogMacros.hpp"
#include "util/logging/ConsoleLogSystem.hpp"

#include "ConfigCommon.hpp"
#include "IOTClient.hpp"

#define LOG_TAG_AWS_IOT_DEVICE "[AWS_IOT_DEVICE]"
#define MESSAGE_COUNT 5
#define SDK_SAMPLE_TOPIC "sdk/test/cpp"

using namespace std;

namespace awsiotsdk {

ResponseCode IOTClient::RunPublish(int msg_count) {
    std::cout << std::endl
              << "******************************Entering Publish with no queuing delay unless queue is full!!**************************"
              << std::endl;
    ResponseCode rc;
    uint16_t packet_id = 0;
    int itr = 1;

    util::String p_topic_name_str = SDK_SAMPLE_TOPIC;

    do {
        util::String payload = "Hello from SDK : ";
        payload.append(std::to_string(itr));
        std::cout << "Publish Payload : " << payload << std::endl;

        std::unique_ptr<Utf8String> p_topic_name = Utf8String::Create(p_topic_name_str);
        rc = p_iot_client_->PublishAsync(std::move(p_topic_name), false, false, mqtt::QoS::QOS1,
                                         payload, nullptr, packet_id);
        if (ResponseCode::SUCCESS == rc) {
            cur_pending_messages_++;
            total_published_messages_++;
            std::cout << "Publish Packet Id : " << packet_id << std::endl;
        } else if (ResponseCode::ACTION_QUEUE_FULL == rc) {
            itr--;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    } while (++itr <= msg_count && (ResponseCode::SUCCESS == rc || ResponseCode::ACTION_QUEUE_FULL == rc));

    return rc;
}

ResponseCode IOTClient::SubscribeCallback(util::String topic_name,
                                       util::String payload,
                                       std::shared_ptr<mqtt::SubscriptionHandlerContextData> p_app_handler_data) {
    std::cout << std::endl << "************" << std::endl;
    std::cout << "Received message on topic : " << topic_name << std::endl;
    std::cout << "Payload Length : " << payload.length() << std::endl;
    if (payload.length() < 50) {
        std::cout << "Payload : " << payload << std::endl;
    }
    std::cout << std::endl << "************" << std::endl;
    cur_pending_messages_--;
    return ResponseCode::SUCCESS;
}

ResponseCode IOTClient::DisconnectCallback(util::String client_id,
                                        std::shared_ptr<DisconnectCallbackContextData> p_app_handler_data) {
    std::cout << "*******************************************" << std::endl
              << client_id << " Disconnected!" << std::endl
              << "*******************************************" << std::endl;
    return ResponseCode::SUCCESS;
}

ResponseCode IOTClient::ReconnectCallback(util::String client_id,
                                       std::shared_ptr<ReconnectCallbackContextData> p_app_handler_data,
                                       ResponseCode reconnect_result) {
    std::cout << "*******************************************" << std::endl
              << client_id << " Reconnect Attempted. Result " << ResponseHelper::ToString(reconnect_result)
              << std::endl
              << "*******************************************" << std::endl;
    return ResponseCode::SUCCESS;
}

ResponseCode IOTClient::ResubscribeCallback(util::String client_id,
                                         std::shared_ptr<ResubscribeCallbackContextData> p_app_handler_data,
                                         ResponseCode resubscribe_result) {
    std::cout << "*******************************************" << std::endl
              << client_id << " Resubscribe Attempted. Result" << ResponseHelper::ToString(resubscribe_result)
              << std::endl
              << "*******************************************" << std::endl;
    return ResponseCode::SUCCESS;
}

ResponseCode IOTClient::Subscribe() {
    util::String p_topic_name_str = SDK_SAMPLE_TOPIC;
    std::unique_ptr<Utf8String> p_topic_name = Utf8String::Create(p_topic_name_str);
    mqtt::Subscription::ApplicationCallbackHandlerPtr p_sub_handler = std::bind(&IOTClient::SubscribeCallback,
                                                                                this,
                                                                                std::placeholders::_1,
                                                                                std::placeholders::_2,
                                                                                std::placeholders::_3);
    std::shared_ptr<mqtt::Subscription> p_subscription =
        mqtt::Subscription::Create(std::move(p_topic_name), mqtt::QoS::QOS0, p_sub_handler, nullptr);
    util::Vector<std::shared_ptr<mqtt::Subscription>> topic_vector;
    topic_vector.push_back(p_subscription);

    ResponseCode rc = p_iot_client_->Subscribe(topic_vector, ConfigCommon::mqtt_command_timeout_);
    std::this_thread::sleep_for(std::chrono::seconds(3));
    return rc;
}

ResponseCode IOTClient::Unsubscribe() {
    util::String p_topic_name_str = SDK_SAMPLE_TOPIC;
    std::unique_ptr<Utf8String> p_topic_name = Utf8String::Create(p_topic_name_str);
    util::Vector<std::unique_ptr<Utf8String>> topic_vector;
    topic_vector.push_back(std::move(p_topic_name));

    ResponseCode rc = p_iot_client_->Unsubscribe(std::move(topic_vector), ConfigCommon::mqtt_command_timeout_);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return rc;
}

ResponseCode IOTClient::InitializeTLS() {
    ResponseCode rc = ResponseCode::SUCCESS;

#ifdef USE_WEBSOCKETS
    p_network_connection_ = std::shared_ptr<NetworkConnection>(
        new network::WebSocketConnection(ConfigCommon::endpoint_, ConfigCommon::endpoint_https_port_,
                                         ConfigCommon::root_ca_path_, ConfigCommon::aws_region_,
                                         ConfigCommon::aws_access_key_id_,
                                         ConfigCommon::aws_secret_access_key_,
                                         ConfigCommon::aws_session_token_,
                                         ConfigCommon::tls_handshake_timeout_,
                                         ConfigCommon::tls_read_timeout_,
                                         ConfigCommon::tls_write_timeout_, true));
    if (nullptr == p_network_connection_) {
        AWS_LOG_ERROR(LOG_TAG_AWS_IOT_DEVICE, "Failed to initialize Network Connection. %s",
                      ResponseHelper::ToString(rc).c_str());
        rc = ResponseCode::FAILURE;
    }
#elif defined USE_MBEDTLS
    p_network_connection_ = std::make_shared<network::MbedTLSConnection>(ConfigCommon::endpoint_,
                                                                         ConfigCommon::endpoint_mqtt_port_,
                                                                         ConfigCommon::root_ca_path_,
                                                                         ConfigCommon::client_cert_path_,
                                                                         ConfigCommon::client_key_path_,
                                                                         ConfigCommon::tls_handshake_timeout_,
                                                                         ConfigCommon::tls_read_timeout_,
                                                                         ConfigCommon::tls_write_timeout_,
                                                                         true);
    if (nullptr == p_network_connection_) {
        AWS_LOG_ERROR(LOG_TAG_AWS_IOT_DEVICE, "Failed to initialize Network Connection. %s",
                      ResponseHelper::ToString(rc).c_str());
        rc = ResponseCode::FAILURE;
    }
#else
    std::shared_ptr<network::OpenSSLConnection> p_network_connection =
        std::make_shared<network::OpenSSLConnection>(ConfigCommon::endpoint_,
                                                     ConfigCommon::endpoint_mqtt_port_,
                                                     ConfigCommon::root_ca_path_,
                                                     ConfigCommon::client_cert_path_,
                                                     ConfigCommon::client_key_path_,
                                                     ConfigCommon::tls_handshake_timeout_,
                                                     ConfigCommon::tls_read_timeout_,
                                                     ConfigCommon::tls_write_timeout_, true);
    rc = p_network_connection->Initialize();

    if (ResponseCode::SUCCESS != rc) {
        AWS_LOG_ERROR(LOG_TAG_AWS_IOT_DEVICE,
                      "Failed to initialize Network Connection. %s",
                      ResponseHelper::ToString(rc).c_str());
        rc = ResponseCode::FAILURE;
    } else {
        p_network_connection_ = std::dynamic_pointer_cast<NetworkConnection>(p_network_connection);
    }
#endif
    return rc;
}

void IOTClient::startLogging()
{
    std::shared_ptr<awsiotsdk::util::Logging::ConsoleLogSystem> p_log_system = std::make_shared<awsiotsdk::util::Logging::ConsoleLogSystem>(awsiotsdk::util::Logging::LogLevel::Info);
    awsiotsdk::util::Logging::InitializeAWSLogging(p_log_system);
}

void IOTClient::stopLogging()
{
    awsiotsdk::util::Logging::ShutdownAWSLogging();
}

ResponseCode IOTClient::init(const util::String &config_file_path)
{
    return awsiotsdk::ConfigCommon::InitializeCommon(config_file_path);
}

ResponseCode IOTClient::Connect() {
    ResponseCode rc = InitializeTLS();
    if (ResponseCode::SUCCESS != rc) {
        return rc;
    }

    ClientCoreState::ApplicationDisconnectCallbackPtr p_disconnect_handler =
        std::bind(&IOTClient::DisconnectCallback, this, std::placeholders::_1, std::placeholders::_2);

    ClientCoreState::ApplicationReconnectCallbackPtr p_reconnect_handler =
        std::bind(&IOTClient::ReconnectCallback,
                  this,
                  std::placeholders::_1,
                  std::placeholders::_2,
                  std::placeholders::_3);

    ClientCoreState::ApplicationResubscribeCallbackPtr p_resubscribe_handler =
        std::bind(&IOTClient::ResubscribeCallback,
                  this,
                  std::placeholders::_1,
                  std::placeholders::_2,
                  std::placeholders::_3);

    p_iot_client_ = std::shared_ptr<MqttClient>(MqttClient::Create(p_network_connection_,
                                                                   ConfigCommon::mqtt_command_timeout_,
                                                                   p_disconnect_handler, nullptr,
                                                                   p_reconnect_handler, nullptr,
                                                                   p_resubscribe_handler, nullptr));
    if (nullptr == p_iot_client_) {
        return ResponseCode::FAILURE;
    }

    util::String client_id_tagged = ConfigCommon::base_client_id_;
    client_id_tagged.append("_pub_sub_tester_");
    client_id_tagged.append(std::to_string(rand()));
    std::unique_ptr<Utf8String> client_id = Utf8String::Create(client_id_tagged);

    std::cout << "connecting ...." << std::endl;
    rc = p_iot_client_->Connect(ConfigCommon::mqtt_command_timeout_, ConfigCommon::is_clean_session_,
                                mqtt::Version::MQTT_3_1_1, ConfigCommon::keep_alive_timeout_secs_,
                                std::move(client_id), nullptr, nullptr, nullptr);
    if (ResponseCode::MQTT_CONNACK_CONNECTION_ACCEPTED != rc) {
        std::cout << "connecting failed!" << std::endl;
        return rc;
    }

    std::cout << "connecting done!" << std::endl;

    //return ResponseCode::MQTT_CONNACK_CONNECTION_ACCEPTED if connect success
    return rc;
}

ResponseCode IOTClient::Disconnect()
{
    ResponseCode rc = p_iot_client_->Disconnect(ConfigCommon::mqtt_command_timeout_);
    return rc;
}

ResponseCode IOTClient::PublishAsync(const util::String &topic_name, const util::String &payload)
{
    ResponseCode rc;
    uint16_t packet_id = 0;

    std::cout << "Publish Payload : " << payload << std::endl;

    std::unique_ptr<Utf8String> p_topic_name = Utf8String::Create(topic_name);
    rc = p_iot_client_->PublishAsync(std::move(p_topic_name), false, false, mqtt::QoS::QOS1,
                                     payload, nullptr, packet_id);

    if (ResponseCode::SUCCESS == rc) {
        cur_pending_messages_++;
        total_published_messages_++;
        std::cout << "Publish Packet Id : " << packet_id << std::endl;
    } else if (ResponseCode::ACTION_QUEUE_FULL == rc) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    return rc;
}

}
