#include "Client.h"


Client::Client(const char* IP, const char* port)
    : serverPort(port), serverIP(IP)
{
    // Make sure memory is cleared for WSAStartup
    WSACleanup();

    WSADATA wsaData;
    if (int eCode = WSAStartup(MAKEWORD(2, 2), &wsaData))
        throw eCode;

    addrinfo hints;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    if (int eCode = getaddrinfo(serverIP, serverPort, &hints, &result))
        throw eCode;

    // Create a SOCKET for connecting to server
    connectSocket = socket(result->ai_family, result->ai_socktype,
        result->ai_protocol);

    if (connectSocket == INVALID_SOCKET)
        throw WSAGetLastError();

    if (int eCode = connect(connectSocket, result->ai_addr, (int)result->ai_addrlen) == SOCKET_ERROR)
        throw WSAGetLastError();

    freeaddrinfo(result);
}

void Client::GetSession(Client* client)
{
    printf("Client Listening...\n");
    while (true)
    {
        char* msg = new char[512];
        client->Get(msg, 512);
        printf("Received: %s\n", msg);
    }
}

int Client::Get(char* out, int size)
{
    int iResult = recv(connectSocket, out, size, 0);

    return iResult;
}

void Client::Send(char* message)
{
    int iResult = send(connectSocket, message, strlen(message), 0);

    if (iResult == SOCKET_ERROR)
        throw WSAGetLastError();

    printf("Bytes Sent: %ld\n", iResult);
}

int Client::Run()
{
    printf("Client starting...\n");
    printf("Type something!\n");
    
    try {
        std::string s;

        std::thread t(Client::GetSession, this);
        t.detach();

        // Send an initial buffer
        while (true)
        {
            std::getline(std::cin, s);
            this->Send((char*)s.c_str());
        }
    }
    catch (...) {
        printf("last error: %i\n", WSAGetLastError());
    }

    return 0;
}
