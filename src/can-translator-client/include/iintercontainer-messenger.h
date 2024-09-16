/*********************************************************************
* Copyright (c) 9-7-2024 Cummins Inc
*
* This program and the accompanying materials are made
* available under the terms of the Eclipse Public License 2.0
* which is available at https://www.eclipse.org/legal/epl-2.0/
*
* SPDX-License-Identifier: EPL-2.0
**********************************************************************/
#ifndef __I_InterContainer_Messenger
#define __I_InterContainer_Messenger

#pragma once
#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>
#include "iprotocolMessage.h"



class messageCallback
{
public:
    virtual ~messageCallback() = default;
    
    /** @brief - OnMessage method to handle incoming message
     * @return void
     */

    virtual std::string OnMessage(const IprotocolMessage &message)
    {
        spdlog::debug("Inside messageCallback onmessage : {}, data: {}", message.getDestination(), message.getPayload().dump());
        return message.getDestination();
    }

    /** @brief - OnConnect method to perform actions after connections
     * @return void
     */

    virtual void OnConnect()
    {
        spdlog::error("messageCallback::OnConnect() is not implemented.");
    }

    /** @brief - Disconnect method to disconnect mqtt connection
     * @return void
     */

    virtual void OnDisconnect()
    {
        spdlog::error("messageCallback::OnDisConnect() is not implemented.");
    }
};
class InterContainerMessenger
{
public:
    //Default InterContainerMessenger destructor
    virtual ~InterContainerMessenger() = default; 

    /** @brief - ListenTo method to subscribe to mqtt topic
     * @param msgType - message topic
     * @return void
     */
    virtual void ListenTo(const std::string &msgType)=0;

    /** @brief - SendMessage method to publish payload on mqtt topic
     * @param topic - string type topic for publishing message
     * @param payload - string type payload
     * @param retain - option to retain mqtt message
     * @return void
     */

    virtual void SendMessage(const std::string &destination, const std::string &payload, const bool &retain)=0;

    /** @brief - OnConnect method to perform actions after connections
     * @return void
     */

    virtual void OnConnect()=0;

    /** @brief - OnConnectionLost method to perform actions after loss of mqtt connection
     * @return void
     */

    virtual void OnConnectionLost()=0;

    /** @brief - Connect method to perform actions after loss of mqtt connection
     * @return void
     */

    virtual void Connect(messageCallback &messageCallback)=0;

    /** @brief - Disconnect method to disconnect mqtt connection
     * @return void
     */
    
    virtual void Disconnect()=0;

};

#endif