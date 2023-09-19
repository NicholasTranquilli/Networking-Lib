#include "Server.h"
#include "Client.h"

int RunClient(char* IP)
{
    try {
        Client c(IP, "27015");
        c.Run();
    }
    catch (...) {
        printf("last error: %i\n", WSAGetLastError());
    }

    printf("\nclient closed\n");
    printf("last error: %i\n", WSAGetLastError());

    return 0;
}

int RunServer()
{
    try {
        Server s("27015");
        s.Monitor();
    }
    catch (...) {
        printf("last error: %i\n", WSAGetLastError());
    }

    return 0;
}

int main()
{
    //std::string IPs;
    //printf("ENTER IP: ");
    //std::cin >> IPs;
    //char* IP = new char;
    //strcpy_s(IP, IPs.length() + 1, IPs.c_str());
    //printf("IP IS: %s\n", IP);
    //RunClient(IP);
    RunServer();
}