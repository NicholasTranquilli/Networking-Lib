# Networking-Lib
C++ Networking library made with winsock.

I use Radmin VPN to test the server and client.

Supports multiple clients.

to run the client:
```c++
    try {
        // replace SERVER_IP_ADDRESS and PORT
        // EX: c("26.242.27.251", "27015");
        Client c("SERVER_IP_ADDRESS", "PORT");
        c.Run();
    }
    catch (...) {
        printf("last error: %i\n", WSAGetLastError());
    }
```

to run the server:
```c++
    try {
        // replace PORT
        // EX: s("27015");
        Server s("PORT");
        s.Monitor();
    }
    catch (...) {
        printf("last error: %i\n", WSAGetLastError());
    }
```
