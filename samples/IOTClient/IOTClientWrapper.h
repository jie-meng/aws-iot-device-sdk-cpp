#pragma once

#ifdef __cplusplus
extern "C" {
#endif

void iot_client_startLogging();

void iot_client_stopLogging();

int iot_client_init(const char* config_file_path);

int iot_client_connect();

int iot_client_disconnect();

int iot_client_publish(const char* topic_name, const char* payload);

#ifdef __cplusplus
}
#endif
