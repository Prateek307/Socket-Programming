## Overview

This project consists of a server program (`chat_server.c`) and a client program (`chat_client.c`) for establishing a basic socket connection in the banking scenario.

## Getting Started

Follow these steps to compile and run the server and client programs.

### Prerequisites

Make sure you have a C++ compiler installed on your system.

### Compiling and Running the Server

1. Open a terminal.

2. Compile the server program using the following command:

   ```bash
   g++ chat_server.c -o chat_server.exe -lws2_32
   ./chat_server.exe
   
### Compiling and Running the Client

1. Open a terminal.

2. Compile the Client program using the following command:

   ```bash
   g++ chat_client.c -o chat_client.exe -lws2_32
   ./chat_client.exe
