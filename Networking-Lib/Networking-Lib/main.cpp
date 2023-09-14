#include "Server.h"
#include "Client.h"

int RunClient()
{
    try {
        Client c("26.242.27.251", "27015");
        c.Run();
    }
    catch (...) {
        printf("last error: %i\n", WSAGetLastError());
    }

    return 0;
}

int RunServer()
{
    try {
        Server s("27015");
        s.Monitor();
    }
    catch (...) {
        printf("L\n");
    }

    return 0;
}

int main()
{
    RunClient();
    //RunServer();
}