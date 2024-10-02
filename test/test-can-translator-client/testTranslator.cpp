/*********************************************************************
* Copyright (c) 9-7-2024 Cummins Inc
*
* This program and the accompanying materials are made
* available under the terms of the Eclipse Public License 2.0
* which is available at https://www.eclipse.org/legal/epl-2.0/
*
* SPDX-License-Identifier: EPL-2.0
**********************************************************************/
#include <gmock/gmock.h>
#include <nlohmann/json.hpp>
#include "testIMqttWrapper.h"
#include "apiconstants.h"
#include "Application.h"
#include "udsTestPayloads.h"


class ApplicationDerived : public Application
{
public:
    ApplicationDerived(std::shared_ptr<InterContainerMessenger> protocolClient) : Application(protocolClient)
    {
        
    }
    virtual ~ApplicationDerived(){};
  

};

TEST_F(TestFixture1, ReadDataByIdentifierTest)
{
    EXPECT_CALL(*protocolClient, Connect(::testing::_)).Times(testing::Exactly(1)).WillRepeatedly(::testing::Return());
    ApplicationDerived app(protocolClient);
    auto translator = app.getcommunicationLibPtr();
    std::vector<std::string> DATA_IDENTIFIERS = {"A0E1"};
    EXPECT_CALL(*protocolClient, SendMessage(global::publish::OPEN_COMM_CHANNEL, uds::openCommRequest.dump(),false)).Times(1).WillRepeatedly([&translator] {
    translator->notify(global::subscribe::OPEN_COMM_CHANNEL, uds::openCommResponse);});
    EXPECT_CALL(*protocolClient, SendMessage(global::publish::TRANSLATOR_UDS_READ_BY_ID, uds::udsReadRequest.dump(),false)).Times(1).WillRepeatedly([&translator] { translator->notify(global::subscribe::TRANSLATOR_UDS_READ_BY_ID, uds::udsReadDataRes); });
    app.ReadUDSParameter(DATA_IDENTIFIERS);
 
}