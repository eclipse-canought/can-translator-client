/*********************************************************************
* Copyright (c) 9-7-2024 Cummins Inc
*
* This program and the accompanying materials are made
* available under the terms of the Eclipse Public License 2.0
* which is available at https://www.eclipse.org/legal/epl-2.0/
*
* SPDX-License-Identifier: EPL-2.0
**********************************************************************/
#include "translator.h"

void ::Translator::UDS::setConnectionId(const std::string &id)
{
    connectionId = id;
};

std::string Translator::UDS::getConnectionId()
{
    if (connectionId.empty())
    {
        // Fill in the empty strings with ecm tool address, ecu address and can format
        OpenCommunicationChannel("","","");
    }
    return connectionId;
}

jsonType Translator::UDS::OpenCommunicationChannel(const std::string &toolAddress, const std::string &ecuAddress,const std::string &canFormat)
{
    translator::opencommchannel::request::OpenCommChannel openCommChannel;
    std::string sequenceVal = translatorPointer->getSequence();
    openCommChannel.appID = global::CLIENT_ID;
    openCommChannel.sequenceNo = sequenceVal; 
    openCommChannel.toolAddress = toolAddress;
    openCommChannel.ecuAddress = ecuAddress;
    //Modify resource_name to desired value
    openCommChannel.resourceName = "resource_name";
    openCommChannel.canFormat.canPhysReqFormat = canFormat;
    openCommChannel.canFormat.canRespUSDTFormat = canFormat;
    jsonType finalRequest = openCommChannel;
    translatorPointer->SendMessageonInput(global::publish::OPEN_COMM_CHANNEL, finalRequest.dump());
    setConnectionId(translatorPointer->getResponse(sequenceVal)["connectionID"]);
    return {};
}

jsonType Translator::UDS::RequestCommunicationControl(const std::string &subFunction, const std::string &communicationType,
                                               const std::string &nodeIdentificationNumberHighByte, const std::string &nodeIdentificationNumberLowByte)
{
    translator::uds::request::CommunicationControl commControlRequest;
    commControlRequest.connectionID = getConnectionId();
    std::string sequenceVal = translatorPointer->getSequence();
    commControlRequest.appID = global::CLIENT_ID;
    commControlRequest.sequenceNo = sequenceVal;
    commControlRequest.subFunction = subFunction;
    commControlRequest.communicationType = communicationType;
    commControlRequest.nodeIdentificationNumberHighByte = nodeIdentificationNumberHighByte;
    commControlRequest.nodeIdentificationNumberLowByte = nodeIdentificationNumberLowByte;
    jsonType finalRequest = commControlRequest;
    translatorPointer->SendMessageonInput(global::publish::COMMUNICATION_CONTROL, finalRequest.dump());
    return translatorPointer->getResponse(sequenceVal);
}

jsonType Translator::UDS::TransferData(const std::string &data, const std::string &blockSequenceNumber)
{
    translator::uds::request::TransferData transferDataReq;
    transferDataReq.connectionID = getConnectionId();
    std::string sequenceVal = translatorPointer->getSequence();
    transferDataReq.appID = global::CLIENT_ID;
    transferDataReq.blockSequenceNumber = blockSequenceNumber;
    transferDataReq.sequenceNo = sequenceVal;
    transferDataReq.transferRequestParameterRecord = data;
    jsonType finalRequest = transferDataReq;
    translatorPointer->SendMessageonInput(global::publish::TRANSLATOR_UDS_TRANSFER_DATA, finalRequest.dump());
    return translatorPointer->getResponse(sequenceVal);
}

jsonType Translator::UDS::RequestTransferExit(const std::string &transferRequestParameterRecord)
{
    translator::uds::request::RequestTransferExit requestTransferExitObj;
    requestTransferExitObj.connectionID = getConnectionId();
    std::string sequenceVal = translatorPointer->getSequence();
    requestTransferExitObj.appID = global::CLIENT_ID;
    requestTransferExitObj.sequenceNo = sequenceVal;
    requestTransferExitObj.transferRequestParameterRecord = transferRequestParameterRecord;
    jsonType finalRequest = requestTransferExitObj;
    translatorPointer->SendMessageonInput(global::publish::TRANSLATOR_UDS_REQUEST_TRANSFER_EXIT, finalRequest.dump());
    return translatorPointer->getResponse(sequenceVal);
}

jsonType Translator::UDS::RoutineControlRequest(const std::string &routineControlOptionRecord, const std::string &routineIdentifier, const std::string &subFunction)
{
    translator::uds::request::RoutineControl routineControlReq;
    routineControlReq.appID = global::CLIENT_ID;
    routineControlReq.connectionID = getConnectionId();
    std::string sequenceVal = translatorPointer->getSequence();
    routineControlReq.sequenceNo = sequenceVal;
    routineControlReq.routineControlOptionRecord = routineControlOptionRecord;
    routineControlReq.routineIdentifier = routineIdentifier;
    routineControlReq.subFunction = subFunction;
    jsonType finalRequest = routineControlReq;
    translatorPointer->SendMessageonInput(global::publish::TRANSLATOR_UDS_ROUTINE_CONTROL, finalRequest.dump());
    auto receivedJson = translatorPointer->getResponse(sequenceVal);
    return receivedJson;
}

jsonType Translator::UDS::ReadByDataIdentifier(const std::vector<std::string> &did)
{
    translator::uds::request::ReadDataByIdentifier readDataReq;
    readDataReq.connectionID = getConnectionId();
    std::string sequenceVal = translatorPointer->getSequence();
    readDataReq.sequenceNo = sequenceVal;
    readDataReq.appID = global::CLIENT_ID;
    readDataReq.did = did;
    jsonType finalRequest = readDataReq;
    translatorPointer->SendMessageonInput(global::publish::TRANSLATOR_UDS_READ_BY_ID, finalRequest.dump());
    auto receivedJson = translatorPointer->getResponse(sequenceVal);
    return receivedJson;
}

jsonType Translator::UDS::RequestDownload(const std::string &address, const std::string &memsize,
                                          const std::string &dataFormatId,const std::string &alFormatIdentifier)
{
    translator::uds::request::RequestDownload calDownloadReq;
    calDownloadReq.connectionID = getConnectionId();
    std::string sequenceVal = translatorPointer->getSequence();
    calDownloadReq.appID = global::CLIENT_ID;
    calDownloadReq.sequenceNo = sequenceVal;
    calDownloadReq.dataFormatIdentifier = dataFormatId;
    calDownloadReq.addressAndLengthFormatIdentifier = alFormatIdentifier;
    calDownloadReq.memoryAddress = address;
    calDownloadReq.memorySize = memsize;
    jsonType finalRequest = calDownloadReq;
    translatorPointer->SendMessageonInput(global::publish::TRANSLATOR_UDS_REQUEST_DOWNLOAD, finalRequest.dump());
    return translatorPointer->getResponse(sequenceVal);
}

void Translator::UDS::CloseCommunicationChannel()
{
    translatorPointer->CloseCommunicationChannel(getConnectionId());
}

jsonType Translator::UDS::RequestTelematicsSession(const std::string &subFunction)
{
    translator::uds::request::DiagnosticsSessionControl sessionReq;
    sessionReq.connectionID = getConnectionId();
    std::string sequenceVal = translatorPointer->getSequence();
    sessionReq.appID = global::CLIENT_ID;
    sessionReq.sequenceNo = sequenceVal;
    sessionReq.subFunction = subFunction;
    jsonType finalRequest = sessionReq;
    translatorPointer->SendMessageonInput(global::publish::SESSION_CONTROL, finalRequest.dump());
    auto responseJson = translatorPointer->getResponse(sequenceVal);
    return responseJson;
}

jsonType Translator::UDS::WriteDataByIdentifier(const std::vector<translator::uds::request::WriteData> &data)
{
    translator::uds::request::WriteDataByIdentifier writeReq;
    writeReq.connectionID = getConnectionId();
    std::string sequenceVal = translatorPointer->getSequence();
    writeReq.appID = global::CLIENT_ID;
    writeReq.sequenceNo = sequenceVal;
    writeReq.data = data;
    jsonType finalRequest = writeReq;
    translatorPointer->SendMessageonInput(global::publish::TRANSLATOR_UDS_WRITE, finalRequest.dump());
    auto receivedJson = translatorPointer->getResponse(sequenceVal);
    return receivedJson;
}


jsonType Translator::UDS::SendTesterPresent(const std::string &subFunction)
{
    translator::uds::request::TesterPresent testerPresentReq;
    testerPresentReq.connectionID = getConnectionId();
    std::string seq = translatorPointer->getSequence();
    testerPresentReq.appID = global::CLIENT_ID;
    testerPresentReq.sequenceNo = seq;
    testerPresentReq.subFunction = subFunction;
    jsonType finalRequest = testerPresentReq;
    translatorPointer->SendMessageonInput(global::publish::TESTER_PRESENT, finalRequest.dump());
    return translatorPointer->getResponse(seq);
}

jsonType Translator::UDS::RequestReadDtc(const std::string &subFunction, const std::string &dtcStatusMask)
{
    translator::uds::request::ReadDtc readReq;
    readReq.connectionID = getConnectionId();
    std::string seq = translatorPointer->getSequence();
    readReq.appID = global::CLIENT_ID;
    readReq.sequenceNo = seq;
    readReq.subFunction = subFunction;
    readReq.dtcStatusMask = dtcStatusMask;
    jsonType finalRequest = readReq;
    translatorPointer->SendMessageonInput(global::publish::READ_DTC, finalRequest.dump());
    return translatorPointer->getResponse(seq);
}

jsonType Translator::UDS::RequestClearDtc(const std::string &groupOfDTC, const std::string &memorySelection)
{
    translator::uds::request::ClearDtc clearReq;
    clearReq.connectionID = getConnectionId();
    std::string seq = translatorPointer->getSequence();
    clearReq.appID = global::CLIENT_ID;
    clearReq.sequenceNo = seq;
    clearReq.groupOfDTC = groupOfDTC;
    clearReq.memorySelection = memorySelection;
    jsonType finalRequest = clearReq;
    translatorPointer->SendMessageonInput(global::publish::CLEAR_DTC, finalRequest.dump());
    return translatorPointer->getResponse(seq);
}

jsonType Translator::UDS::RequestReadFreezeFrame(const std::string &dtcStoredDataRecordNumber)
{
    translator::uds::request::ReadFreezeFrame readFramesReq;
    readFramesReq.connectionID = getConnectionId();
    std::string seq = translatorPointer->getSequence();
    readFramesReq.appID = global::CLIENT_ID;
    readFramesReq.sequenceNo = seq;
    readFramesReq.dtcStoredDataRecordNumber = dtcStoredDataRecordNumber;
    jsonType finalRequest = readFramesReq;
    translatorPointer->SendMessageonInput(global::publish::READ_FREEZE_FRAMES, finalRequest.dump());
    return translatorPointer->getResponse(seq);
}


void Translator::J1939::CloseCommunicationChannel()
{
    translatorPointer->CloseCommunicationChannel(getConnectionId());
}

jsonType Translator::J1939::OpenCommunicationChannel(const std::string &toolAddress, const std::string &ecuAddress,const std::string &canFormat)
{
    translator::opencommchannel::request::OpenCommChannel openCommChannel;
    std::string sequenceVal = translatorPointer->getSequence();
    openCommChannel.appID = global::CLIENT_ID;
    openCommChannel.sequenceNo = sequenceVal; 
    openCommChannel.toolAddress = toolAddress;
    openCommChannel.ecuAddress = ecuAddress;
     //Modify resource_name to suitable value
    openCommChannel.resourceName = "resource_name";
    openCommChannel.canFormat.canPhysReqFormat = canFormat;
    openCommChannel.canFormat.canRespUSDTFormat = canFormat;
    jsonType finalRequest = openCommChannel;
    translatorPointer->SendMessageonInput(global::publish::OPEN_COMM_CHANNEL, finalRequest.dump());
    setConnectionId(translatorPointer->getResponse(sequenceVal)["connectionID"]);
    return translatorPointer->getResponse(sequenceVal);
}

std::string Translator::J1939::getConnectionId()
{
    if (connectionId.empty())
    {
        // Fill in the empty strings with ecm tool address, ecu address and can format
        OpenCommunicationChannel("", "", "");
    }
    return connectionId;
}

jsonType Translator::J1939::ReadJ1939PGNs(const std::vector<std::string> pgns)
{
    translator::j1939::request::ReadPGNs j1939Req;
    j1939Req.appID = global::CLIENT_ID;
    j1939Req.connectionID = getConnectionId();
    std::string sequenceVal = translatorPointer->getSequence();
    j1939Req.sequenceNo = sequenceVal;
    j1939Req.pgnNo = pgns;
    jsonType finalRequest = j1939Req;
    translatorPointer->SendMessageonInput(global::publish::TRANSLATOR_J1939_READ_PGNS, finalRequest.dump());
    jsonType jresponse = translatorPointer->getResponse(sequenceVal);
    spdlog::debug(jresponse.dump(4));
    return jresponse;
}
jsonType Translator::J1939::ExecutePGNMonitoring(const std::string &operation, const std::string &sampleRate)
{
    translator::j1939::request::ExecuteMonitoring executeMonitorReq;
    executeMonitorReq.appID = global::CLIENT_ID;
    executeMonitorReq.connectionID = getConnectionId();
    std::string sequenceVal = translatorPointer->getSequence();
    executeMonitorReq.sequenceNo = sequenceVal;
    executeMonitorReq.operation = operation;
    executeMonitorReq.sampleRate = sampleRate;
    jsonType finalRequest = executeMonitorReq;
    translatorPointer->SendMessageonInput(global::publish::TRANSLATOR_J1939_EXECUTE_MONITORING,
                                          finalRequest.dump());
    jsonType jresponse = translatorPointer->getResponse(sequenceVal);
   
    return jresponse;
}

jsonType Translator::J1939::createSelectMonPGNReq(const std::vector<std::string>& pgns)
{
    translator::j1939::request::SelectMonitoring selectMonitorReq;
    selectMonitorReq.appID = global::CLIENT_ID;
    selectMonitorReq.connectionID = getConnectionId();
    std::string sequenceVal = translatorPointer->getSequence();
    selectMonitorReq.sequenceNo = sequenceVal;
    selectMonitorReq.pgnNo = pgns;
    jsonType finalRequest = selectMonitorReq;
    translatorPointer->SendMessageonInput(global::publish::TRANSLATOR_J1939_SELECT_MONITORING_PGNS,
                                          finalRequest.dump());
    jsonType jresponse = translatorPointer->getResponse(sequenceVal);
    
    return jresponse;
}

jsonType Translator::getResponse(const std::string &sequenceVal,const int time)
{
    auto sec = std::chrono::seconds(1);
    std::unique_lock<std::mutex> lock(mainLock);
    if (receivedConditionVariable.wait_for(lock,
                                           time * sec,
                                           [this,
                                            &sequenceVal]
                                           {
                                               return receivedSequence == sequenceVal;
                                           }))
    {
        spdlog::debug("Got response for sequence" + sequenceVal);
        return receivedMessage;
    }
    else
    {
        spdlog::debug("Timed out" + sequenceVal);
        jsonType j_null;
        receivedMessage = j_null;
        return receivedMessage;
    }
}

void Translator::notify(const std::string &topic, const jsonType message)
{
    std::unique_lock<std::mutex> lock(mainLock);
    spdlog::debug("Inside notify");
    if (topic == global::subscribe::GET_SET_ADDRESS)
    {
        receivedSequence = topic;
        receivedMessage = message;
        receivedConditionVariable.notify_one();
    }
    else if (message["appID"] == global::CLIENT_ID)
    {
        receivedMessage = message;
        receivedSequence = message["sequenceNo"];
        receivedConditionVariable.notify_one();
    }
}

jsonType Translator::WaitForAddressClaimBroadcast()
{
    spdlog::debug("Waiting for address claim");
    return getResponse(global::subscribe::GET_SET_ADDRESS);
}

jsonType Translator::RequestGetAddressClaim()
{
    translator::getclaimedaddress::request::GetClaimedAddress getClaimAdd;
    std::string sequenceVal = getSequence();
    getClaimAdd.appID = global::CLIENT_ID;
    getClaimAdd.sequenceNo = sequenceVal;
    jsonType finalRequest = getClaimAdd;
    SendMessageonInput(global::publish::GET_ADDRESS_CLAIM, finalRequest.dump());
    spdlog::debug("Exiting Addressclaim");
    return getResponse(sequenceVal);
}

void Translator::CloseCommunicationChannel(const std::string &connectionId)
{
    translator::closecommchannel::request::CloseCommChannel closeCommChannel;
    std::string sequenceVal = getSequence();
    closeCommChannel.appID = global::CLIENT_ID;
    closeCommChannel.connectionID = connectionId;
    closeCommChannel.sequenceNo = sequenceVal;
    jsonType finalRequest = closeCommChannel;
    SendMessageonInput(global::publish::CLOSE_COMM_CHANNEL, finalRequest.dump());
    getResponse(sequenceVal);
}

jsonType Translator::RequestSetConfigParameter(const std::string &connectionId,const std::vector<translator::setconfigparams::request::ComParams> &params)
{
    translator::setconfigparams::request::SetConfigParams setConfigParam;
    std::string sequenceVal = getSequence();
    setConfigParam.appID = global::CLIENT_ID;
    setConfigParam.sequenceNo = sequenceVal;
    setConfigParam.connectionID = connectionId;
    setConfigParam.comParams = params;
    jsonType finalRequest = setConfigParam;
    SendMessageonInput(global::publish::SET_CONFIG_PARAMETER, finalRequest.dump());
    return getResponse(sequenceVal);
}