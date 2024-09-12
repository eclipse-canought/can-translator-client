# CAN Translator Client
The CANought CAN Translator Client implements the client-side interfaces defined in the CANought CAN Translator project. 
This client is essentially an MQTT wrapper for standard J1939 and UDS services. 
This project provides code which can be used to create a new client application which will interface with the
CAN Translator for sending and receiving J1939 and UDS messages. It is written in C++ and provides
1. A template main application that will keep the application running so it can receive MQTT responses from the CAN Translator
2. A set of Dockerfiles for setting up the development environment
3. A set of functions which implement the J1939 and UDS requests to the CAN Translator over MQTT/JSON
4. Callback functions for handling responses

```plaintext
+--------------------------+
|   CAN Translator Client  |     <--- You are here
+--------------------------+
            |  
            | MQTT
            |
+--------------------------+
|      CAN Translator      |
+--------------------------+
            |
            | J1939 and UDS
            |
+--------------------------+
|      CAN Interface       |
|      e.g. SocketCAN      |
+--------------------------+
