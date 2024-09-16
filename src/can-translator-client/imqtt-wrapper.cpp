/*********************************************************************
* Copyright (c) 9-7-2024 Cummins Inc
*
* This program and the accompanying materials are made
* available under the terms of the Eclipse Public License 2.0
* which is available at https://www.eclipse.org/legal/epl-2.0/
*
* SPDX-License-Identifier: EPL-2.0
**********************************************************************/
#include "imqtt-wrapper.h"
using json = nlohmann::json;

IMqttWrapper::IMqttWrapper(const std::string &serverURI,
						   const std::string &CLIENT_ID)
	: cli(std::make_unique<mqtt::async_client>(serverURI,
											   CLIENT_ID))
{
	spdlog::debug("Inside of MQTT Constructor initializing server " + serverURI);
};

void IMqttWrapper::ListenTo(const std::string &msgType)
{
	spdlog::debug("Inside MQTT listen call");
	cli->subscribe(msgType,QOS);
}

void IMqttWrapper::SendMessage(const std::string &topic, const std::string &payload, const bool &retain)
{
	spdlog::debug("The published topic is " + topic);
	spdlog::debug("The published payload is " + payload); 
	if(retain){
        cli->publish(topic,payload,QOS,true)->wait_for(TIMEOUT); 
	}else{
        cli->publish(topic,payload)->wait_for(TIMEOUT);  
	} 		
}

void IMqttWrapper::Connect(messageCallback &onMessageCallback1)
{
  	cli->set_connection_lost_handler([this](const std::string&)
     {
		  spdlog::error("Connection Lost");
		  IMqttWrapper::OnConnectionLost();
	 });

	cli->set_message_callback([&onMessageCallback1](mqtt::const_message_ptr msg) 
    {
		IprotocolMessage msgtowrapper(msg->get_topic(),msg->to_string());
		onMessageCallback1.OnMessage(msgtowrapper);
    });
    
   cli->connect(connOpts)->wait();
   spdlog::info("successfully connected to mqtt-broker");
 
}

void IMqttWrapper::Disconnect()
{
	cli->disconnect()->wait();
}

void IMqttWrapper::OnConnectionLost()
{
    spdlog::info("Reconnecting to broker");
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	try
	{
		cli->connect(connOpts)->wait();
	}
	catch (const mqtt::exception &exc)
	{
		std::string errMsg("Error: ");
		errMsg += exc.what();
		spdlog::error(errMsg);
		exit(1);
	}
}

void IMqttWrapper::OnConnect()
{
	/*  */	
}
