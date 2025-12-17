#pragma once
#include <IPAddress.h>

class LocalServer
{
    // tn
    // asdasd
public:
        IPAddress ip;
        IPAddress subnet;
        IPAddress gateway;
    LocalServer(IPAddress ip, IPAddress gateway, IPAddress subnet);

    void softAPInit();
};