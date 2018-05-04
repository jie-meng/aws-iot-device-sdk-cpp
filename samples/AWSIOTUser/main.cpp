#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <sstream>
#include <utility>
#include <exception>
#include <iostream>
#include "../AWSIOTDevice/AWSIOTDevice.h"

inline std::string getLine() { std::string str; std::getline(std::cin, str); return str; }

using namespace std;

int main(int argc, char* argv[])
{
    int res = 0;

    aws_iot_startLogging();

    res = aws_iot_init("config/SampleConfig.json");

    cout<<"init: "<<res<<endl;

    if (res != 0)
    {
        return -1;
    }

    res = aws_iot_connect();

    cout<<"connect: "<<res<<endl;

    if (res != 100)
    {
        return -1;
    }

    res = aws_iot_publish("sdk/test/cpp", "This is just a test!");

    cout<<"publish: "<<res<<endl;

    cout<<"press any key to continue ..."<<endl;

    getLine();

    res = aws_iot_disconnect();

    cout<<"disconnect: "<<res<<endl;

    aws_iot_stopLogging();

    return 0;
}
