/*********************************************************************
* Copyright (c) 9-7-2024 Cummins Inc
*
* This program and the accompanying materials are made
* available under the terms of the Eclipse Public License 2.0
* which is available at https://www.eclipse.org/legal/epl-2.0/
*
* SPDX-License-Identifier: EPL-2.0
**********************************************************************/

/******************************************************************************
 * OS Includes
 * ***************************************************************************/
 #include <csignal>

/******************************************************************************
 * Local Includes
 * ***************************************************************************/
#include "can-translator-client/include/apiconstants.h"
#include "can-translator-client/include/observer.h"
#include "can-translator-client/include/Application.h"

/******************************************************************************
 * Global Variables
 * ***************************************************************************/

std::promise<bool> closedPromise;

void signal_handler(int signal)
{
    spdlog::info("signal_handler Received signal " + std::to_string(signal));
    closedPromise.set_value(true);
    spdlog::info("signal_handler exiting");
}

int main()
{
    spdlog::set_level(spdlog::level::debug); 
    spdlog::info("Hello from main!");
    std::shared_ptr<InterContainerMessenger> protocolClient = std::make_shared<IMqttWrapper>(global::SERVER_ADDRESS, global::CLIENT_ID);
    if(!protocolClient){
        spdlog::error("Error Initializing protocol Client");
        return -1;
    }
    signal(SIGTERM, signal_handler);
    signal(SIGKILL, signal_handler);
    std::unique_ptr<Observer> observer = std::make_unique<Application>(protocolClient);
    if(!observer){
        spdlog::error("Failed to create Observer class");
        return -1;
    }
    observer->Initialize();
    
    spdlog::info("main: mutex locked");
    closedPromise.get_future().wait();
   
    observer->cleanUp();
    spdlog::info("Goodbye from main!");  
}