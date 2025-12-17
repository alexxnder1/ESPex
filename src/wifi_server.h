#pragma once
#include <IPAddress.h>

class WifiServer
{
public:
        IPAddress ip;
        IPAddress subnet;
        IPAddress gateway;
    WifiServer(IPAddress ip, IPAddress gateway, IPAddress subnet);

    void softAPInit();
};