#pragma once

#ifdef __cplusplus
extern "C" {
#endif

const int RESPONSE_CODE_DISCOVER_ACTION_NO_INFORMATION_PRESENT = 401;           ///< Discover Action response showed no discovery information is present for this thing name
const int RESPONSE_CODE_DISCOVER_ACTION_SUCCESS = 400;                          ///< Discover Action found connectivity information for this thing name

// Shadow Success Codes

const int RESPONSE_CODE_SHADOW_RECEIVED_DELTA = 301;                             ///< Returned when a delta update is received
const int RESPONSE_CODE_SHADOW_REQUEST_ACCEPTED = 300;                           ///< Returned when the request has been accepted

// Network Success Codes

const int RESPONSE_CODE_NETWORK_PHYSICAL_LAYER_CONNECTED = 203;                   ///< Returned when the Network physical layer is connected.
const int RESPONSE_CODE_NETWORK_MANUALLY_DISCONNECTED = 202;                      ///< Returned when the Network is manually disconnected.
const int RESPONSE_CODE_NETWORK_ATTEMPTING_RECONNECT = 201;                       ///< Returned when the Network is disconnected and the reconnect attempt is in progress.
const int RESPONSE_CODE_NETWORK_RECONNECTED = 200;                                ///< Return value of yield function to indicate auto-reconnect was successful.

// MQTT Success Codes

const int RESPONSE_CODE_MQTT_NOTHING_TO_READ = 101;                               ///< Returned when a read attempt is made on the TLS buffer and it is empty.
const int RESPONSE_CODE_MQTT_CONNACK_CONNECTION_ACCEPTED = 100;                   ///< Returned when a connection request is successful and packet response is connection accepted.

// Generic Response Codes

const int RESPONSE_CODE_SUCCESS = 0;                                              ///< Success return value - no error occurred.
const int RESPONSE_CODE_FAILURE = -1;                                             ///< A generic error. Not enough information for a specific error code.
const int RESPONSE_CODE_NULL_VALUE_ERROR = -2;                                    ///< A required parameter was passed as null.

// I/O Error Codes

const int RESPONSE_CODE_FILE_OPEN_ERROR = -100;                                    ///< Unable to open the requested file
const int RESPONSE_CODE_FILE_NAME_INVALID = -101;                                  ///< File name is invalid or of zero length

// Threading Error Codes

const int RESPONSE_CODE_MUTEX_INIT_ERROR = -200;                                   ///< Mutex initialization failed
const int RESPONSE_CODE_MUTEX_LOCK_ERROR = -201;                                   ///< Mutex lock request failed
const int RESPONSE_CODE_MUTEX_UNLOCK_ERROR = -202;                                 ///< Mutex unlock request failed
const int RESPONSE_CODE_MUTEX_DESTROY_ERROR = -203;                                ///< Mutex destroy failed
const int RESPONSE_CODE_THREAD_EXITING = -204;                                     ///< Thread is exiting, returned when thread exits in the middle of an operation

// Network TCP Error Codes

const int RESPONSE_CODE_NETWORK_TCP_CONNECT_ERROR = -300;                          ///< The TCP socket could not be established.
const int RESPONSE_CODE_NETWORK_TCP_SETUP_ERROR = -301;                            ///< Error associated with setting up the parameters of a Socket.
const int RESPONSE_CODE_NETWORK_TCP_UNKNOWN_HOST = -302;                           ///< Returned when the server is unknown.
const int RESPONSE_CODE_NETWORK_TCP_NO_ENDPOINT_SPECIFIED = -303;                  ///< Returned when the Network connection was not provided an endpoint

// Network SSL Error Codes

const int RESPONSE_CODE_NETWORK_SSL_INIT_ERROR = -400;                             ///< SSL initialization error at the TLS layer.
const int RESPONSE_CODE_NETWORK_SSL_ROOT_CRT_PARSE_ERROR = -401;                   ///< Returned when the root certificate is invalid.
const int RESPONSE_CODE_NETWORK_SSL_DEVICE_CRT_PARSE_ERROR = -402;                 ///< Returned when the device certificate is invalid.
const int RESPONSE_CODE_NETWORK_SSL_KEY_PARSE_ERROR = -403;                        ///< An error occurred when loading the certificates. The certificates could not be located or are incorrectly formatted.
const int RESPONSE_CODE_NETWORK_SSL_TLS_HANDSHAKE_ERROR = -404;                    ///< The TLS handshake failed due to unknown error.
const int RESPONSE_CODE_NETWORK_SSL_CONNECT_ERROR = -405;                          ///< An unknown occurred while waiting for the TLS handshake to complete.
const int RESPONSE_CODE_NETWORK_SSL_CONNECT_TIMEOUT_ERROR = -406;                  ///< A timeout occurred while waiting for the TLS handshake to complete.
const int RESPONSE_CODE_NETWORK_SSL_CONNECTION_CLOSED_ERROR = -407;                ///< The SSL Connection was closed
const int RESPONSE_CODE_NETWORK_SSL_WRITE_ERROR = -408;                            ///< A Generic write error based on the platform used.
const int RESPONSE_CODE_NETWORK_SSL_WRITE_TIMEOUT_ERROR = -409;                    ///< SSL Write times out.
const int RESPONSE_CODE_NETWORK_SSL_READ_ERROR = -410;                             ///< A Generic error based on the platform used.nerator seeding failed.
const int RESPONSE_CODE_NETWORK_SSL_READ_TIMEOUT_ERROR = -411;                     ///< SSL Read times out.
const int RESPONSE_CODE_NETWORK_SSL_NOTHING_TO_READ = -412;                        ///< Returned when there is nothing to read in the TLS read buffer.
const int RESPONSE_CODE_NETWORK_SSL_UNKNOWN_ERROR = -413;                          ///< A generic error code for Network SSL layer errors.
const int RESPONSE_CODE_NETWORK_SSL_SERVER_VERIFICATION_ERROR = -414;              ///< Server name verification failure.

// Network Generic Error Codes

const int RESPONSE_CODE_NETWORK_DISCONNECTED_ERROR = -500;                         ///< Returned when the Network is disconnected and reconnect is either disabled or physical layer is disconnected.
const int RESPONSE_CODE_NETWORK_RECONNECT_TIMED_OUT_ERROR = -501;                  ///< Returned when the Network is disconnected and the reconnect attempt has timed out.
const int RESPONSE_CODE_NETWORK_ALREADY_CONNECTED_ERROR = -502;                    ///< Returned when the Network is already connected and a connection attempt is made.
const int RESPONSE_CODE_NETWORK_PHYSICAL_LAYER_DISCONNECTED = -503;                ///< Returned when the physical layer is disconnected.
const int RESPONSE_CODE_NETWORK_NOTHING_TO_WRITE_ERROR = -504;                     ///< Returned when the Network write function is passed an empty buffer as argument

// ClientCore Error Codes

const int RESPONSE_CODE_ACTION_NOT_REGISTERED_ERROR = -601;                        ///< Requested action is not registered with the core client
const int RESPONSE_CODE_ACTION_QUEUE_FULL = -602;                                  ///< Core Client Action queue is full
const int RESPONSE_CODE_ACTION_CREATE_FAILED = -603;                               ///< Core Client was not able to create the requested action

// MQTT Error Codes

const int RESPONSE_CODE_MQTT_CONNECTION_ERROR = -701;                              ///< A connection could not be established.
const int RESPONSE_CODE_MQTT_CONNECT_TIMEOUT_ERROR = -702;                         ///< A timeout occurred while waiting for the MQTT connect to complete.
const int RESPONSE_CODE_MQTT_REQUEST_TIMEOUT_ERROR = -703;                         ///< A timeout occurred while waiting for the TLS request to complete.
const int RESPONSE_CODE_MQTT_UNEXPECTED_CLIENT_STATE_ERROR = -704;                 ///< The current client state does not match the expected value.
const int RESPONSE_CODE_MQTT_CLIENT_NOT_IDLE_ERROR = -705;                         ///< The client state is not idle when request is being made.
const int RESPONSE_CODE_MQTT_RX_MESSAGE_PACKET_TYPE_INVALID_ERROR = -706;          ///< The MQTT RX buffer received corrupt or unexpected message.
const int RESPONSE_CODE_MQTT_MAX_SUBSCRIPTIONS_REACHED_ERROR = -707;               ///< The client is subscribed to the maximum possible number of subscriptions.
const int RESPONSE_CODE_MQTT_DECODE_REMAINING_LENGTH_ERROR = -708;                 ///< Failed to decode the remaining packet length on incoming packet.
const int RESPONSE_CODE_MQTT_CONNACK_UNKNOWN_ERROR = -709;                         ///< Connect request failed with the server returning an unknown error.
const int RESPONSE_CODE_MQTT_CONNACK_UNACCEPTABLE_PROTOCOL_VERSION_ERROR = -710;   ///< Connect request failed with the server returning an unacceptable protocol version error.
const int RESPONSE_CODE_MQTT_CONNACK_IDENTIFIER_REJECTED_ERROR = -711;             ///< Connect request failed with the server returning an identifier rejected error.
const int RESPONSE_CODE_MQTT_CONNACK_SERVER_UNAVAILABLE_ERROR = -712;              ///< Connect request failed with the server returning an unavailable error.
const int RESPONSE_CODE_MQTT_CONNACK_BAD_USERDATA_ERROR = -713;                    ///< Connect request failed with the server returning a bad userdata error.
const int RESPONSE_CODE_MQTT_CONNACK_NOT_AUTHORIZED_ERROR = -714;                  ///< Connect request failed with the server failing to authenticate the request.
const int RESPONSE_CODE_MQTT_NO_SUBSCRIPTION_FOUND = -715;                         ///< No subscription exists for requested topic
const int RESPONSE_CODE_MQTT_SUBSCRIPTION_NOT_ACTIVE = -716;                       ///< Subscription exists but is not active; waiting for Suback or Ack not received
const int RESPONSE_CODE_MQTT_UNEXPECTED_PACKET_FORMAT_ERROR = -717;                ///< Deserialization failed because packet data was in an unexpected format
const int RESPONSE_CODE_MQTT_TOO_MANY_SUBSCRIPTIONS_IN_REQUEST = -718;             ///< Too many subscriptions were provided in the Subscribe/Unsubscribe request
const int RESPONSE_CODE_MQTT_INVALID_DATA_ERROR = -719;                            ///< Provided data is invalid/not sufficient for the request
const int RESPONSE_CODE_MQTT_SUBSCRIBE_PARTIALLY_FAILED = -720;                    ///< Failed to subscribe to atleast one of the topics in the subscribe request
const int RESPONSE_CODE_MQTT_SUBSCRIBE_FAILED = -721;                              ///< Unable to subscribe to any of the topics in the subscribe request

// JSON Parsing Error Codes

const int RESPONSE_CODE_JSON_PARSE_KEY_NOT_FOUND_ERROR = -800;                     ///< JSON Parser was not able to find the requested key in the specified JSON
const int RESPONSE_CODE_JSON_PARSE_KEY_UNEXPECTED_TYPE_ERROR = -801;               ///< The value type was different from the expected type
const int RESPONSE_CODE_JSON_PARSING_ERROR = -802;                                 ///< An error occurred while parsing the JSON string.  Usually malformed JSON.
const int RESPONSE_CODE_JSON_MERGE_FAILED = -803;                                  ///< Returned when the JSON merge request fails unexpectedly
const int RESPONSE_CODE_JSON_DIFF_FAILED = -804;                                   ///< Returned when the JSON diff request fails unexpectedly

// Shadow Error Codes

const int RESPONSE_CODE_SHADOW_WAIT_FOR_PUBLISH = -900;                            ///< Shadow: The response Ack table is currently full waiting for previously published updates
const int RESPONSE_CODE_SHADOW_JSON_BUFFER_TRUNCATED = -901;                       ///< Any time an snprintf writes more than size value; this error will be returned
const int RESPONSE_CODE_SHADOW_JSON_ERROR = -902;                                  ///< Any time an snprintf encounters an encoding error or not enough space in the given buffer
const int RESPONSE_CODE_SHADOW_JSON_EMPTY_ERROR = -903;                            ///< Returned when the provided json document is empty
const int RESPONSE_CODE_SHADOW_REQUEST_MAP_EMPTY = -904;                           ///< Returned when the provided request map is empty
const int RESPONSE_CODE_SHADOW_MQTT_DISCONNECTED_ERROR = -905;                     ///< Returned when the MQTT connection is not active
const int RESPONSE_CODE_SHADOW_UNEXPECTED_RESPONSE_TYPE = -906;                    ///< Returned when the Response type in the recevied payload is unexpected
const int RESPONSE_CODE_SHADOW_UNEXPECTED_RESPONSE_TOPIC = -907;                   ///< Returned when Response is received on an unexpected topic
const int RESPONSE_CODE_SHADOW_REQUEST_REJECTED = -908;                            ///< Returned when the request has been rejected by the server
const int RESPONSE_CODE_SHADOW_MQTT_CLIENT_NOT_SET_ERROR = -909;                   ///< Returned when there is no client set for this shadow
const int RESPONSE_CODE_SHADOW_NOTHING_TO_UPDATE = -910;                           ///< Returned when there is nothing to update for a Shadow Update request
const int RESPONSE_CODE_SHADOW_UNEXPECTED_RESPONSE_PAYLOAD = -911;                 ///< Returned when the response payload is in an unexpected format
const int RESPONSE_CODE_SHADOW_RECEIVED_OLD_VERSION_UPDATE = -912;                 ///< Returned when a version update is received with an older version than the current one on the device

// WebSocket Error Codes

const int RESPONSE_CODE_WEBSOCKET_SIGN_URL_NO_MEM = -1000;                         ///< Internal buffer overflow when signing secured WebSocket url
const int RESPONSE_CODE_WEBSOCKET_GEN_CLIENT_KEY_ERROR = -1001;                    ///< Error in generating WebSocket handhshake client key
const int RESPONSE_CODE_WEBSOCKET_HANDSHAKE_ERROR = -1002;                         ///< WebSocket handshake generic error
const int RESPONSE_CODE_WEBSOCKET_HANDSHAKE_WRITE = -1003;                         ///< WebSocket handshake error in sending request
const int RESPONSE_CODE_WEBSOCKET_HANDSHAKE_READ = -1004;                          ///< WebSocket handhshake error in receiving request
const int RESPONSE_CODE_WEBSOCKET_HANDSHAKE_VERIFY_ERROR = -1005;                  ///< WebSocket handshake error in verifying server response
const int RESPONSE_CODE_WEBSOCKET_WSLAY_CONTEXT_INIT_ERROR = -1006;                ///< WebSocket wslay context init error
const int RESPONSE_CODE_WEBSOCKET_FRAME_RECEIVE_ERROR = -1007;                     ///< WebSocket error in receiving frames
const int RESPONSE_CODE_WEBSOCKET_FRAME_TRANSMIT_ERROR = -1008;                    ///< WebSocket error in sending frames
const int RESPONSE_CODE_WEBSOCKET_PROTOCOL_VIOLATION = -1009;                      ///< WebSocket protocol violation detected in receiving frames
const int RESPONSE_CODE_WEBSOCKET_MAX_LIFETIME_REACHED = -1010;                    ///< WebSocket connection max life time window reached
const int RESPONSE_CODE_WEBSOCKET_DISCONNECT_ERROR = -1011;                        ///< WebSocket disconnect error
const int RESPONSE_CODE_WEBSOCKET_GET_UTC_TIME_FAILED = -1012;                     ///< Returned when the WebSocket wrapper cannot get UTC time

// Discovery Error Codes

const int RESPONSE_CODE_DISCOVER_ACTION_REQUEST_FAILED_ERROR = -1100;              ///< Discover Action request failed
const int RESPONSE_CODE_DISCOVER_ACTION_REQUEST_TIMED_OUT_ERROR = -1101;           ///< Discover Action request timed out
const int RESPONSE_CODE_DISCOVER_ACTION_UNAUTHORIZED = -1102;                      ///< Discover Action repsonse showed that this device does not have authorization to query the server
const int RESPONSE_CODE_DISCOVER_ACTION_SERVER_ERROR = -1103;                      ///< Discover Action failed due to some server side error
const int RESPONSE_CODE_DISCOVER_ACTION_REQUEST_OVERLOAD = -1104;                  ///< Discover Action failed due to too many requests, try again after some time

// Discovery Response Parsing Error Codes

const int RESPONSE_CODE_DISCOVER_RESPONSE_UNEXPECTED_JSON_STRUCTURE_ERROR = -1200;  ///< Discover Response Json is missing expected keys

#ifdef _WIN32

#ifdef DLL_EXPORT
#define DLL_IMPORT_EXPORT  __declspec(dllexport)
#else
#define DLL_IMPORT_EXPORT  __declspec(dllimport)
#endif

#else

#define DLL_IMPORT_EXPORT

#endif

DLL_IMPORT_EXPORT void aws_iot_startLogging();

DLL_IMPORT_EXPORT void aws_iot_stopLogging();

DLL_IMPORT_EXPORT int aws_iot_init(const char* config_file_path);

DLL_IMPORT_EXPORT int aws_iot_connect();

DLL_IMPORT_EXPORT int aws_iot_disconnect();

DLL_IMPORT_EXPORT int aws_iot_publish(const char* topic_name, const char* payload);

#ifdef __cplusplus
}
#endif
