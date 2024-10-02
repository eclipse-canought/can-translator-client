/*********************************************************************
* Copyright (c) 9-7-2024 Cummins Inc
*
* This program and the accompanying materials are made
* available under the terms of the Eclipse Public License 2.0
* which is available at https://www.eclipse.org/legal/epl-2.0/
*
* SPDX-License-Identifier: EPL-2.0
**********************************************************************/
#include "observer.h"

std::string Observer::OnMessage(const IprotocolMessage &message)
{
	const std::string topic = message.getDestination();
	const jsonType payload = message.getPayload();
	MessageHelper(topic,
				  payload);
	return "";
}

// Function to parse the message and payload for incoming mqtt message
void Observer::MainThreadFunc()
{
	while (true)
	{
		spdlog::debug("Enter Observer::waiting for message");
		auto message = holderQueue.Dequeue();
		if (!message)
		{
			spdlog::debug("Empty message from dequeue");
			return;
		}
		OnIncomingMessage(message.value().first,
						  message.value().second);
	}
	
}

void Observer::Initialize()
{
#if USE_TRANSLATOR
	for (const auto &redirectTopic : translator::list)
	{
		notificationMap[redirectTopic] = CONTAINER::TRANSLATOR;
	}
#endif
	for (const auto &redirectTopic : application::list)
	{
		notificationMap[redirectTopic] = CONTAINER::APPLICATION;
	}
	spdlog::debug("Enter Observer::Init");

	for (const auto &topic : application::Subscriptiontopics)
	{
		ListenToData(topic);
	}
	Init();
	
	mainThread = std::thread(&Observer::MainThreadFunc, this);
	
	spdlog::debug("Exit Observer::Init");
}

inline void Observer::MessageHelper(const std::string &topic, const jsonType &payload)
{
	auto containerName = topic.substr(0, topic.find('/'));
	
	if (notificationMap.find(containerName) != notificationMap.end())
	{
		spdlog::debug("Observer::MessageHelper topic container is {}",
					  containerName);

		if (notificationMap[containerName] == CONTAINER::APPLICATION)
		{
			holderQueue.Enqueue(std::make_pair(topic, payload));
		}
		else
		{
			threadPool.enqueue([this,
								containerName,
								topic,
								payload]()
							   { forwardPayload(containerName, topic, payload); });
		}
	}
}
void Observer::forwardPayload(const std::string &containerName,
							  const std::string &topic,
							  const jsonType &payload)
{
	spdlog::debug("Inside forward payload");
	switch (notificationMap[containerName])
	{
#if USE_TRANSLATOR
	case CONTAINER::TRANSLATOR:
		communicationLib->notify(topic, payload);
		break;
#endif
	default:
		return;
	}
}
void Observer::Init()
{
	// Intentionally unimplemented...
}

void Observer::SendMessageonInput(const std::string &topic,
								  const std::string &payload, 
								  const bool &retain)
{
	if (protocolClient != nullptr)
	{
		protocolClient->SendMessage(topic, payload, retain);
	}
}

std::string Observer::OnIncomingMessage(const std::string &topic,
								const jsonType &payload)
{
	return "";
}