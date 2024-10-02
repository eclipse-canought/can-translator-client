/*********************************************************************
* Copyright (c) 9-7-2024 Cummins Inc
*
* This program and the accompanying materials are made
* available under the terms of the Eclipse Public License 2.0
* which is available at https://www.eclipse.org/legal/epl-2.0/
*
* SPDX-License-Identifier: EPL-2.0
**********************************************************************/

#pragma once

#include <gmock/gmock.h>
#include <nlohmann/json.hpp>
#include "imqtt-wrapper.h"
#include "apiconstants.h"
#include "Application.h"


using json = nlohmann::json;

class MockIMqttWrapper: public IMqttWrapper
{
    public:
        MockIMqttWrapper(const std::string& serverURI,const std::string& clientId):IMqttWrapper(serverURI, clientId){};
        virtual ~MockIMqttWrapper(){};
        MOCK_METHOD(void, Connect,(messageCallback &onMessageCallback));
        MOCK_METHOD(void, OnConnect, ());
        MOCK_METHOD(void, Disconnect, ());
        MOCK_METHOD(void, Reconnect, ());
        MOCK_METHOD(void, ListenTo, (const std::string &topic));
        MOCK_METHOD(void, SendMessage, (const std::string &topic, const std::string &payload, const bool &retain));
        MOCK_METHOD(void, notify,(const std::string topic, const json message));
};

class TestFixture1 : public ::testing::Test
{
public:
   
    TestFixture1()
    {
        protocolClient = std::make_shared<MockIMqttWrapper>(global::SERVER_ADDRESS, global::CLIENT_ID);
    }

    virtual void SetUp()
    {
       
        
    }

    virtual void TearDown()
    {
    }
   

protected:
    std::shared_ptr<MockIMqttWrapper> protocolClient;   
};