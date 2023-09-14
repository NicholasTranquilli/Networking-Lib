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

class Server
{
	SOCKET listenSocket;
	std::map<int, SOCKET> clients;
	const char* port;
	int currentID;

	static void ClientSession(Server* server, SOCKET client, int id);

public:
	Server(const char* nPort);
	int GetFrom(SOCKET& client, char* msg, int size);
	int SendTo(SOCKET& client, char* msg, int size);

	void PushClient(int id, SOCKET sock);
	void Monitor();
};