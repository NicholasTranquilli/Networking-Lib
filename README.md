# Networking-Lib
C++ Networking library made with winsock.

I use Radmin VPN to test the server and client.

Supports multiple clients.

to run the client:
```c++
    try {
        Client c("26.242.27.251", "27015");
        c.Run();
    }
    catch (...) {
        printf("last error: %i\n", WSAGetLastError());
    }
```

to run the server:
```c++
    try {
        Server s("27015");
        s.Monitor();
    }
    catch (...) {
        printf("last error: %i\n", WSAGetLastError());
    }
```
