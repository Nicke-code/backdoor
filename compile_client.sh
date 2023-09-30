#!/bin/bash
i686-w64-mingw32-g++ client_backdoor/src/client_tcp.cpp client_backdoor/src/main.cpp -o backdoor.exe -lws2_32 -lwininet -static-libgcc