#include "Server.h"

Server::Server(const char* nPort)
    : port(nPort), currentID(0)
{
    addrinfo* result;

    WSADATA wsaData;
    if (int eCode = WSAStartup(MAKEWORD(2, 2), &wsaData))
        throw eCode;

    addrinfo hints;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    if (int eCode = getaddrinfo(NULL, port, &hints, &result))
        throw eCode;

    listenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

    if (listenSocket == INVALID_SOCKET)
        throw INVALID_SOCKET;

    if (int eCode = bind(listenSocket, result->ai_addr, (int)result->ai_addrlen) == SOCKET_ERROR)
        throw SOCKET_ERROR;

    freeaddrinfo(result);
}

Server::~Server()
{
    WSACleanup();
}

// private

void Server::ClientSession(Server* server, SOCKET client, int id)
{
    server->PushClient(id, client);

    try {
        char* data = new char[512];
        while (server->GetFrom(client, data, 512) > 0)
        {
            printf("Client %d: %s\n", id, data);

            for (auto& nextClient : server->clients)
            {
                server->SendTo(nextClient.second, data, 512);
            }
        }
    }
    catch (...) {
        printf("l\n");
    }

    printf("Client %d disconnected...\n", id);
}

// public

int Server::GetFrom(SOCKET& client, char* msg, int size)
{
    ZeroMemory(msg, size);

    int iResult = recv(client, msg, size, 0);

    return iResult;
}

int Server::SendTo(SOCKET& client, char* msg, int size)
{
    int iResult = send(client, msg, size, 0);

    return iResult;
}

void Server::PushClient(int id, SOCKET sock)
{
    clients.emplace(id, sock);
}

void Server::Monitor()
{
    if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR)
        throw SOCKET_ERROR;

    printf("Server listening...\n");

    SOCKET client = SOCKET_ERROR;
    while (client = accept(listenSocket, NULL, NULL))
    {
        bool exists = false;

        for (auto& i : this->clients)
        {
            if (client == i.second)
            {
                exists = true;
                break;
            }
        }

        if (exists) break;

        std::thread t(Server::ClientSession, this, client, currentID);
        t.detach();
        printf("Client created, ID = %i\n", currentID);
        currentID++;
    }
}
