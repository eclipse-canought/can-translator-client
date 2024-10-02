/*********************************************************************
* Copyright (c) 9-7-2024 Cummins Inc
*
* This program and the accompanying materials are made
* available under the terms of the Eclipse Public License 2.0
* which is available at https://www.eclipse.org/legal/epl-2.0/
*
* SPDX-License-Identifier: EPL-2.0
**********************************************************************/
#include <gtest/gtest.h>
#include "testIMqttWrapper.h"
#include "udsTestPayloads.h"

#ifndef DISABLE_IMQTT_TEST

class ApplicationDerived : public Application
{
public:
    ApplicationDerived(std::shared_ptr<InterContainerMessenger> protocolClient) : Application(protocolClient)
    {
    }
    virtual ~ApplicationDerived(){};
};

TEST_F(TestFixture1, ConnectTest)
{
   EXPECT_CALL(*protocolClient, Connect(::testing::_)).Times(testing::Exactly(1)).WillRepeatedly(::testing::Return());
   ApplicationDerived app(protocolClient);
   
}

 TEST_F(TestFixture1, ListenToTest)
{
   EXPECT_CALL(*protocolClient, Connect(::testing::_)).Times(testing::Exactly(1)).WillRepeatedly(::testing::Return());
   ApplicationDerived app(protocolClient);
   EXPECT_CALL(*protocolClient,SendMessage(global::publish::TRANSLATOR_UDS_READ_BY_ID,::testing::_,false)).Times(1);
   app.SendMessageonInput(global::publish::TRANSLATOR_UDS_READ_BY_ID,uds::udsReadRequest.dump(),false);
    
}
#endif
