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
#include <nlohmann/json.hpp>

namespace uds
{
	const auto openCommRequest = R"(
      {
        "appID": "can_translator_client",
        "canFormat": {
          "canPhysReqFormat": "",
          "canRespUSDTFormat": ""
        },
        "ecuAddress": "",
        "resourceName": "resource_name",
        "sequenceNo": "1",
        "toolAddress": ""
      })"_json;

	const auto openCommResponse = R"(
        {
            "appID": "can_translator_client",
            "connectionID": "0x12345678",
            "sequenceNo": "1",
            "responseCode": "0"
        })"_json;

	const auto closeCommRequest = R"(
      {
        "appID": "can_translator_client",
		    "connectionID": "0x12345678",
        "sequenceNo": "3"
      })"_json;

	const auto closeCommResponse = R"(
        {
            "appID": "can_translator_client",
            "connectionID": "0x12345678",
            "sequenceNo": "3",
            "responseCode": "0"
        })"_json;
	const auto udsReadRequest = R"(
        {
          "appID": "can_translator_client",
          "connectionID": "0x12345678",
          "did": ["A0E1"],
          "sequenceNo": "2"
        })"_json;
	
	const auto udsReadDataRes = R"(
   		{
			"appID": "can_translator_client",
			"connectionID": "0x12345678",
			"sequenceNo": "2",
			"data": [{
				"did": "A0E1",
				"value": "12A0E34",
				"responseCode": "0"
			}],
			"responseCode": "0"
		})"_json;
}