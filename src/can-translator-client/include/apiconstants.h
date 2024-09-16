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

#include <string>
#include <vector>
#include <map>
#include <nlohmann/json.hpp>

#ifdef GTEST
    const int RETRY_TIMEOUT = 1;
#else
    const int RETRY_TIMEOUT = 30; 
#endif
/*
    Config type definition
*/
using jsonType = nlohmann::json;

namespace global{
    const std::string CLIENT_ID = "can_translator_client";
    const std::string SERVER_ADDRESS	= "tcp://mosquitto:1883";
    const int MAX_ROUND_NUM = 200;
    namespace publish
    {
        /******************************************************************************
         * UDS Request MQTT topics
         *****************************************************************************/
        const std::string TRANSLATOR_UDS_READ_BY_ID ="diagstack/request/readdatabyidentifier";
        const std::string TRANSLATOR_UDS_ROUTINE_CONTROL="diagstack/request/routinecontrol";
        const std::string TRANSLATOR_UDS_REQUEST_DOWNLOAD = "diagstack/request/requestdownload";
        const std::string TRANSLATOR_UDS_TRANSFER_DATA = "diagstack/request/transferdata";
        const std::string TRANSLATOR_UDS_REQUEST_TRANSFER_EXIT = "diagstack/request/requesttransferexit";
        const std::string SET_CONFIG_PARAMETER = "diagstack/request/setconfigparameters";
        const std::string TRANSLATOR_UDS_WRITE ="diagstack/request/writedatabyidentifier";
        const std::string SESSION_CONTROL = "diagstack/request/diagnosticsessioncontrol";
        const std::string TESTER_PRESENT = "diagstack/request/sendtesterpresent";
        const std::string READ_DTC = "diagstack/request/readdtc";
        const std::string CLEAR_DTC = "diagstack/request/cleardtcs";
        const std::string READ_FREEZE_FRAMES = "diagstack/request/readfreezeframes";
        const std::string COMMUNICATION_CONTROL = "diagstack/request/communicationcontrol";

        /******************************************************************************
         * J1939/UDS common Request MQTT topics
         *****************************************************************************/
        const std::string OPEN_COMM_CHANNEL = "diagstack/request/opencommchannel";
        const std::string CLOSE_COMM_CHANNEL = "diagstack/request/closecommchannel";
        const std::string GET_ADDRESS_CLAIM = "diagstack/request/getclaimedaddress";
        /******************************************************************************
         * J1939 Request MQTT topics
         *****************************************************************************/
        const std::string TRANSLATOR_J1939_READ_PGNS = "diagstack/request/readpgns";
        const std::string TRANSLATOR_J1939_EXECUTE_MONITORING = "diagstack/request/executepgnmonitoring";
        const std::string TRANSLATOR_J1939_SELECT_MONITORING_PGNS = "diagstack/request/selectmonitoringpgns";
    }
    namespace subscribe{
        /******************************************************************************
         * UDS Response MQTT topics
         *****************************************************************************/
        const std::string TRANSLATOR_UDS_READ_BY_ID = "diagstack/response/readdatabyidentifier";
        const std::string TRANSLATOR_UDS_WRITE ="diagstack/response/writedatabyidentifier";
        const std::string TRANSLATOR_UDS_ROUTINE_CONTROL="diagstack/response/routinecontrol";
        const std::string TRANSLATOR_UDS_REQUEST_DOWNLOAD = "diagstack/response/requestdownload";
        const std::string TRANSLATOR_UDS_TRANSFER_DATA = "diagstack/response/transferdata";
        const std::string TRANSLATOR_UDS_REQUEST_TRANSFER_EXIT = "diagstack/response/requesttransferexit";
        const std::string SET_CONFIG_PARAMETER = "diagstack/response/setconfigparameters";
        const std::string SESSION_CONTROL = "diagstack/response/diagnosticsessioncontrol";
        const std::string TESTER_PRESENT = "diagstack/response/sendtesterpresent";
        const std::string READ_DTC = "diagstack/response/readdtc";
        const std::string CLEAR_DTC = "diagstack/response/cleardtcs";
        const std::string READ_FREEZE_FRAMES = "diagstack/response/readfreezeframes";
        const std::string COMMUNICATION_CONTROL = "diagstack/response/communicationcontrol";
       
        /******************************************************************************
         * J1939 Response MQTT topics
         *****************************************************************************/
        const std::string TRANSLATOR_J1939_READ_PGNS = "diagstack/response/readpgns";
        const std::string TRANSLATOR_J1939_EXECUTE_MONITORING = "diagstack/response/executepgnmonitoring";
        const std::string TRANSLATOR_J1939_SELECT_MONITORING_PGNS = "diagstack/response/selectmonitoringpgns";
        const std::string TRANSLATOR_J1939_GET_UPDATED_PGN_VALUES = "diagstack/response/getupdatedpgnvalues";
        /******************************************************************************
         * J1939/UDS common Response MQTT topics
         *****************************************************************************/
        const std::string OPEN_COMM_CHANNEL = "diagstack/response/opencommchannel";
        const std::string CLOSE_COMM_CHANNEL = "diagstack/response/closecommchannel";
        const std::string GET_ADDRESS_CLAIM = "diagstack/response/getclaimedaddress";
        const std::string GET_SET_ADDRESS = "diagstack/response/claimedaddress";
    }
}

