/*********************************************************************
* Copyright (c) 9-7-2024 Cummins Inc
*
* This program and the accompanying materials are made
* available under the terms of the Eclipse Public License 2.0
* which is available at https://www.eclipse.org/legal/epl-2.0/
*
* SPDX-License-Identifier: EPL-2.0
**********************************************************************/

#ifndef __I_MQTT_WRAPPER
#define __I_MQTT_WRAPPER

#include "mqtt/async_client.h"
#include "iprotocolMessage.h"
#include <nlohmann/json.hpp>
#include "iintercontainer-messenger.h"

#ifdef GTEST
	const auto TIMEOUT = std::chrono::seconds(1);
	const auto KEEPALIVEINTERVAL = std::chrono::seconds(1);
#else
	const auto TIMEOUT = std::chrono::seconds(10);
	const auto KEEPALIVEINTERVAL = std::chrono::seconds(45);
#endif

class IMqttWrapper : public InterContainerMessenger
{
public:

    //Non-parameterized constructor
    IMqttWrapper();

    //parameterized constructor
    explicit IMqttWrapper(messageCallback messageCallback);

    //parameterized constructor
    IMqttWrapper(const std::string &serverURI, const std::string &clientId);

    //IMqttWrapper Copy constructor
    IMqttWrapper(IMqttWrapper const &) = delete;

    //InterContainerMessenger Move constructor
    IMqttWrapper(IMqttWrapper &&) = delete;

    //InterContainerMessenger Copy assignment
    IMqttWrapper &operator=(IMqttWrapper const &) = delete;

    //InterContainerMessenger Move assignment
    IMqttWrapper &operator=(IMqttWrapper &&) = delete;

    /** @brief - ListenTo method to subscribe to mqtt topic
     * @param topic - mqtt topic
     * @return void
     */
    void ListenTo(const std::string &topic) override;

    /** @brief - SendMessage method to publish payload on mqtt topic
     * @param topic - string type mqtt topic for publishing message
     * @param payload - string type mqtt message payload
     * @param retain - option to retain mqtt message
     * @return void
     */

    void SendMessage(const std::string &topic, const std::string &payload, const bool &retain) override;

    /** @brief - OnConnect method to perform actions after connections
     * @return void
     */

    void OnConnect() override;

    /** @brief - OnConnectionLost method to perform actions after loss of mqtt connection
     * @return void
     */

    void OnConnectionLost() override;

    /** @brief - Connect method to perform actions after loss of mqtt connection
     * @return void
     */

    void Connect(messageCallback &onMessageCallback) override;

    /** @brief - Disconnect method to disconnect mqtt connection
     * @return void
     */

    void Disconnect() override;

     /** @brief - class destructor
     */

    ~IMqttWrapper() override = default;

private:
    std::unique_ptr<mqtt::async_client> cli;
    mqtt::connect_options connOpts = mqtt::connect_options_builder()
	.clean_session(false)
    .keep_alive_interval(KEEPALIVEINTERVAL)
	.finalize();
    const int QOS = 1;
};

#endif