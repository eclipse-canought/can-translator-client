/*********************************************************************
* Copyright (c) 9-7-2024 Cummins Inc
*
* This program and the accompanying materials are made
* available under the terms of the Eclipse Public License 2.0
* which is available at https://www.eclipse.org/legal/epl-2.0/
*
* SPDX-License-Identifier: EPL-2.0
**********************************************************************/

/** @file observer.h
 *  @brief 
*/

#pragma once


#include "threadpool.h"
#include "globalconfig.h"
#include "SynchronizedQueue.h"

enum class CONTAINER{
    TRANSLATOR,
    APPLICATION,
    NONE
};

class Observer: public messageCallback
{
    public:
        explicit Observer(std::shared_ptr<InterContainerMessenger> Client): protocolClient(Client)
                                                    #if USE_TRANSLATOR
                                                    ,communicationLib(std::make_unique<Translator>(Client))
                                                    #endif
                                                   

        {	 
            protocolClient->Connect(*this);
        };

        ~Observer() override {
            holderQueue.killAll();
            if (mainThread.joinable())
            {
                mainThread.join();
            }
        }
       

        /**
         * @brief - cleanUp method
         * @param none - No input parameters
         * @return void
         */
        void cleanUp()
        {
            protocolClient->Disconnect();
            finish = true;
        }

        /**
         * @brief - Initializes notifications map
         * @param None - No input parameters
         * @return void 
         */
        void Initialize();

        /**
         * @brief - Notifies on message
         * @param message - const IprotocolMessage reference type
         * @return std::string - returns string
         */
        std::string OnMessage(const IprotocolMessage& message) override;

        /**
         * @brief - Initialization method
         * @param none - No input parameters
         * @return void
         */
        virtual void Init();

        /**
         * @brief - Sends message to client on input
         * @param topic - topic in const string reference type
         * @param payload - payload in const string reference type
         * @return void
         */
        virtual void SendMessageonInput(const std::string &topic,
                                        const std::string &payload, 
								        const bool &retain = false);


        /**
         * @brief - OnIncomingMessage virtual method
         * @param topic - topic in const string reference type
         * @param payload - payload in const jsonType reference Type
         * @return std::string - Returns empty string
         */
        virtual std::string OnIncomingMessage(const std::string& topic,
                              const jsonType &payload);
        
        /**
         * @brief - forwardPayload method forwards the payload to specific container
         * @param topic - topic in const string reference type
         * @param payload - payload in const jsonType reference Type
         * @return std::string - Returns empty string
         */
        void forwardPayload(const std::string &containerName,
                        const std::string &topic,
                        const jsonType &payload);

        
        /** @brief - get Translator
         * @param None - No input parameters
         * @return Translator pointer
         */
        virtual std::shared_ptr<Translator> &getcommunicationLibPtr()
        {
            return communicationLib;
        }

    private:
    
    #if USE_TRANSLATOR
        std::shared_ptr<Translator> communicationLib;
    #endif
    
        /**
         * @brief - Helper function to parse the message and payload for incoming mqtt message
         * @param none - No input parameters
         * @return void
         */
        void MainThreadFunc();

        /**
         * @brief - Notifies the respective container type on message
         * @param topic - topic in const string reference type
         * @param payload - payload in const jsonType reference Type
         * @return void
         */
        void MessageHelper(const std::string& topic, const jsonType& payload);

        /**
         * @brief - Passes data to client to listen
         * @param topic - data in const string reference type
         * @return void
         */
        void ListenToData(const std::string &topic) const{      
            protocolClient->ListenTo(topic);
        };

        std::shared_ptr<InterContainerMessenger> protocolClient;
        std::unordered_map<std::string, CONTAINER> notificationMap;
        ThreadPool threadPool;

        SynchronizedQueue<std::pair<std::string, jsonType>> holderQueue;
        std::atomic<bool> finish{false};
        std::thread mainThread;
        std::queue<IprotocolMessage> messageQueue;
        std::condition_variable messageConditionVariable;
        std::mutex messageMutex;
        
};

