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

    return 0;
}