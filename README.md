# CAN Translator Client
The CANought CAN Translator Client implements the client-side interfaces defined in the CANought CAN Translator project. 
This client is essentially an MQTT wrapper for standard J1939 and UDS services. 
This project provides code which can be used to create a new client application which will interface with the
CAN Translator for sending and receiving J1939 and UDS messages. It is written in C++ and provides
1. A template main application that will keep the application running so it can receive MQTT responses from the CAN Translator
2. A set of Dockerfiles for setting up the development environment
3. A set of functions which implement the J1939 and UDS requests to the CAN Translator over MQTT/JSON
4. Callback functions for handling responses
5. Base framework for MQTT message handling and routing 
6. A set of docker-compose files for building images and setting up test environment
7. Environment setup for executing gmock tests
8. Test Examples

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

Getting Started

## Building docker images

To generate the first base images use docker-compose to generate dev and prod images
```
docker-compose -f opensource/docker-compose.yaml build
```
## Test and Deploy

To execute unit tests please run the shell script runUT.sh after generating the base image
```
./runUT.sh
```
## If using VSCode
For debugging you can execute cleanup task followed by build task which will deploy container services mentioned under docker-compose.dev.yml. Modify Launch and Task.json as per need for debugging application and test suite.
Tip : Use docker exec command to run application inside the created container
     set flags 
    -DCMAKE_BUILD_TYPE -DENABLE_TESTING -DAPP_NAME:STRING as needed.
change type from CRLF to LF during script execution.

