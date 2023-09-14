#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <thread>
#include <string>
#include <stdio.h>

#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

class Client
{
    addrinfo* result;
    SOCKET connectSocket;

    const char* serverIP;
    const char* serverPort;

    static void GetSession(Client* client);

public:
	Client(const char* IP, const char* port);
    int Get(char* out, int size);
    void Send(char* message);
    int Run();
};