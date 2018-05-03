#pragma once

#ifdef __cplusplus
extern "C" {
#endif

void aws_iot_wrapper_startLogging();

void aws_iot_wrapper_stopLogging();

int aws_iot_wrapper_init(const char* config_file_path);

int aws_iot_wrapper_connect();

int aws_iot_wrapper_disconnect();

int aws_iot_wrapper_publish(const char* topic_name, const char* payload);

#ifdef __cplusplus
}
#endif
