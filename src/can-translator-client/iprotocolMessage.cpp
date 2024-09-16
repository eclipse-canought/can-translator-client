/*********************************************************************
* Copyright (c) 9-7-2024 Cummins Inc
*
* This program and the accompanying materials are made
* available under the terms of the Eclipse Public License 2.0
* which is available at https://www.eclipse.org/legal/epl-2.0/
*
* SPDX-License-Identifier: EPL-2.0
**********************************************************************/

#include "mqtt/async_client.h"
#include "mqtt/client.h"
#include "iprotocolMessage.h"

/**
 * Class Constructor
 * @return NA
 * @param values- const std::string_view,const std::string_view
 */

IprotocolMessage::IprotocolMessage(const std::string_view & receivedDestination,const std::string_view & messagepayload)
{
    msgDestination.assign(receivedDestination);
	jsonType payload;
	if (!messagepayload.empty())
	{
		try
		{
			payload = jsonType::parse(messagepayload);
		}
		catch (const jsonType::exception &)
		{
			spdlog::error("Parsing error: ");
		}
	}
	msgPayload = payload;
   
}
/**
 * Get method to get mqtt topic
 * @return string
 * @param values NA
 */
std::string IprotocolMessage::getDestination() const
{
    return msgDestination;
}
/**
 * Get method to get mqtt payload
 * @return string
 * @param values NA
 */
jsonType IprotocolMessage::getPayload() const
{
    return msgPayload;
}