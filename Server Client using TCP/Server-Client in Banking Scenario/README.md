## Overview

This project consists of a server program (`server.c`) and a client program (`Client.c`) for establishing a basic socket connection in the banking scenario.

## Getting Started

Follow these steps to compile and run the server and client programs.

### Prerequisites

Make sure you have a C++ compiler installed on your system.

### Compiling and Running the Server

1. Open a terminal.

2. Compile the server program using the following command:

   ```bash
   g++ server.c -o server.exe -lws2_32
   ./server.exe
##Enter the IP address as : 127.0.0.1 and Port number as 8888

### Compiling and Running the Client

1. Open a terminal.

2. Compile the Client program using the following command:

   ```bash
   g++ Client.c -o Client.exe -lws2_32
   ./Client.exe
