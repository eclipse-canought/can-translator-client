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
#include "apiconstants.h"
#include "iintercontainer-messenger.h"
#include <spdlog/spdlog.h>

namespace translator{
    namespace setconfigparams{
        namespace request{

            struct ComParams {
                std::string configParamName;
                std::string configParamData;

            };

            struct SetConfigParams {
                std::string appID;
                std::string connectionID;
                std::string sequenceNo;
                std::vector <ComParams> comParams;
            };

            NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ComParams, configParamName, configParamData)
            NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SetConfigParams, appID, connectionID, sequenceNo, comParams)

        }

        namespace response {

            struct ConfigData {
                std::string configParamName;
                std::string responseCode;
            };

            struct SetConfigParamsResponse {
                std::string appID;
                std::string connectionID;
                std::string sequenceNo;
                std::vector <ConfigData> data;
                std::string responseCode;
            };

            NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ConfigData, configParamName, responseCode)
            NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SetConfigParamsResponse, appID, connectionID, sequenceNo, data, responseCode)
        }
    }
    namespace getclaimedaddress{
        namespace request{
		
            struct GetClaimedAddress {
                std::string appID;
                std::string sequenceNo;
                
            };

            NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(GetClaimedAddress, appID, sequenceNo)

        }

        namespace response {

            struct GetClaimedAddressResponse {
                std::string appID;
				std::string sequenceNo;
                std::string claimedAddress;
                std::string responseCode;
            };

            NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(GetClaimedAddressResponse, appID, sequenceNo, claimedAddress, responseCode)
        }
    }
    namespace opencommchannel{
        namespace request{

            struct CANFormat {
                std::string canPhysReqFormat;
                std::string canRespUSDTFormat;
            };

            struct OpenCommChannel {
                std::string appID;
                std::string sequenceNo;
                std::string toolAddress;
                std::string ecuAddress;
                CANFormat canFormat;
                std::string resourceName;
            };

            NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(CANFormat, canPhysReqFormat, canRespUSDTFormat)
            NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(OpenCommChannel, appID, sequenceNo, toolAddress, ecuAddress, canFormat, resourceName)
        }

        namespace response{
            struct OpenCommChannelResponse {
                std::string appID;
                std::string connectionID;
                std::string sequenceNo;
                std::string responseCode;
            };

            NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(OpenCommChannelResponse, appID, connectionID, sequenceNo, responseCode)
        }
    }

    namespace closecommchannel{
        namespace request{
            struct CloseCommChannel {
                std::string appID;
                std::string connectionID;
                std::string sequenceNo;
            };

            NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(CloseCommChannel, appID, connectionID, sequenceNo)
        }

        namespace response{
            struct CloseCommChannelResponse {
                std::string appID;
                std::string connectionID;
                std::string sequenceNo;
                std::string responseCode;
            };

            NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(CloseCommChannelResponse, appID, connectionID, sequenceNo, responseCode)
        }
    }
    namespace uds{
        namespace request{
            struct ReadDataByIdentifier{
                std::string appID;
                std::string connectionID;
                std::string sequenceNo;
                std::vector<std::string> did;
            };

            struct WriteData{
                std::string did;
                std::string value;
            };

            struct WriteDataByIdentifier{
                std::string appID;
                std::string connectionID;
                std::string sequenceNo;
                std::vector<WriteData> data;
            };
            
            struct RoutineControl{
                std::string appID;
                std::string connectionID;
                std::string sequenceNo;
                std::string subFunction;
                std::string routineIdentifier;
                std::string routineControlOptionRecord;
            };

            struct RequestDownload{
                std::string appID;
                std::string connectionID;
                std::string sequenceNo;
                std::string dataFormatIdentifier;
                std::string addressAndLengthFormatIdentifier;
                std::string memoryAddress;
                std::string memorySize;
            };

            struct TransferData{
                std::string appID;
                std::string connectionID;
                std::string sequenceNo;
                std::string blockSequenceNumber;
                std::string transferRequestParameterRecord;
            };

            struct RequestTransferExit{
                std::string appID;
                std::string connectionID;
                std::string sequenceNo;
                std::string transferRequestParameterRecord;
            };

            struct DiagnosticsSessionControl {
                std::string appID;
                std::string connectionID;
                std::string sequenceNo;
                std::string subFunction;
            };

            struct TesterPresent
            {
                std::string appID;
                std::string connectionID;
                std::string sequenceNo;
                std::string subFunction;
            };

            struct ReadDtc
            {
                std::string appID;
                std::string connectionID;
                std::string sequenceNo;
                std::string subFunction;
                std::string dtcStatusMask;
            };

            struct ClearDtc
            {
                std::string appID;
                std::string connectionID;
                std::string sequenceNo;
                std::string groupOfDTC;
                std::string memorySelection;
            };

            struct ReadFreezeFrame
            {
                std::string appID;
                std::string connectionID;
                std::string sequenceNo;
                std::string dtcStoredDataRecordNumber;
            };

            struct CommunicationControl
            {
                std::string appID;
                std::string connectionID;
                std::string sequenceNo;
                std::string subFunction;
                std::string communicationType;
                std::string nodeIdentificationNumberHighByte;
                std::string nodeIdentificationNumberLowByte;
            };

            NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ReadDataByIdentifier, appID, connectionID, sequenceNo, did)
            NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ClearDtc, appID, connectionID, sequenceNo, groupOfDTC, memorySelection)
            NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ReadFreezeFrame, appID, connectionID, sequenceNo, dtcStoredDataRecordNumber)
            NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(WriteData, did, value)
            NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(WriteDataByIdentifier, appID, connectionID, sequenceNo, data)
            NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(DiagnosticsSessionControl, appID, connectionID, sequenceNo, subFunction)
            NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(TesterPresent, appID, connectionID, sequenceNo, subFunction)
            NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(RoutineControl, appID, connectionID, sequenceNo, subFunction, routineIdentifier, routineControlOptionRecord)
            NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(RequestDownload, appID, connectionID, sequenceNo, dataFormatIdentifier, addressAndLengthFormatIdentifier, memoryAddress, memorySize)
            NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(TransferData, appID, connectionID, sequenceNo, blockSequenceNumber, transferRequestParameterRecord)
            NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(RequestTransferExit, appID, connectionID, sequenceNo, transferRequestParameterRecord)
            NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ReadDtc, appID, connectionID, sequenceNo, subFunction, dtcStatusMask)
            NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(CommunicationControl, appID, connectionID, sequenceNo, subFunction,communicationType,nodeIdentificationNumberHighByte,nodeIdentificationNumberLowByte)
            
        }
        
        namespace response{
            struct ReadResponse{
                std::string did;
                std::string value;
                std::string responseCode;
            };

            struct ReadDataByIdentifier{
                std::string appID;
                std::string connectionID;
                std::string sequenceNo;
                std::vector<ReadResponse> data;
                std::string responseCode;
            };

            struct WriteResponse{
                std::string did;
                std::string responseCode;
            };

            struct WriteDataByIdentifier{
                std::string appID;
                std::string connectionID;
                std::string sequenceNo;
                std::vector<WriteResponse> data;
                std::string responseCode;
            };

            struct RoutineControl{
                std::string appID;
                std::string connectionID;
                std::string sequenceNo;
                std::string data;
                std::string responseCode;
            };

            struct RequestDownload{
                std::string appID;
                std::string connectionID;
                std::string sequenceNo;
                std::string lengthFormatIdentifier;
                std::string maxNumberOfBlockLength;
                std::string responseCode;
            };

            struct TransferData{
                std::string appID;
                std::string connectionID;
                std::string sequenceNo;
                std::string blockSequenceNumber;
                std::string transferRequestParameterRecord;
                std::string responseCode;
            };

            struct RequestTransferExit
            {
                std::string appID;
                std::string connectionID;
                std::string sequenceNo;
                std::string transferRequestParameterRecord;
                std::string responseCode;
            };

            struct DiagnosticsSessionControl
            {
                std::string appID;
                std::string connectionID;
                std::string sequenceNo;
                std::string subFunction;
                std::string data;
                std::string responseCode;
            };

            struct TesterPresent
            {
                std::string appID;
                std::string connectionID;
                std::string sequenceNo;
                std::string subFunction;
                std::string responseCode;
            };

            struct DtcData
            {
                std::string reportType;
                std::string dtcStatusAvailabilityMask;
                std::string dtcAndStatusRecord;
            };

            struct ReadDtc
            {
                std::string appID;
                std::string connectionID;
                std::string sequenceNo;
                DtcData data;
                std::string responseCode;
            };

            struct ClearDtc
            {
                std::string appID;
                std::string connectionID;
                std::string sequenceNo;
                std::string responseCode;
            };

            struct ReadFreezeFrame
            {
                std::string appID;
                std::string connectionID;
                std::string sequenceNo;
                std::string dtcStoredDataRecordNumber;
                std::string data;
                std::string responseCode;
            };

            NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(DtcData, reportType, dtcStatusAvailabilityMask, dtcAndStatusRecord)
            NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ReadFreezeFrame, appID, connectionID, sequenceNo, dtcStoredDataRecordNumber, data, responseCode)
            NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ClearDtc, appID, connectionID, sequenceNo, responseCode)
            NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ReadDtc, appID, connectionID, sequenceNo,data,responseCode)
            NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ReadResponse, did, value, responseCode)
            NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ReadDataByIdentifier, appID, connectionID, sequenceNo,  data, responseCode)
            NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(WriteResponse, did, responseCode)
            NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(WriteDataByIdentifier, appID, connectionID, sequenceNo, data, responseCode)
            NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(TesterPresent, appID, connectionID, sequenceNo, subFunction, responseCode)
            NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(DiagnosticsSessionControl, appID, connectionID, sequenceNo, subFunction, data, responseCode)
            NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(RoutineControl, appID, connectionID, sequenceNo, data, responseCode)
            NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(RequestDownload, appID, connectionID, sequenceNo, lengthFormatIdentifier, maxNumberOfBlockLength, responseCode)
            NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(TransferData, appID, connectionID, sequenceNo, blockSequenceNumber,transferRequestParameterRecord, responseCode)
            NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(RequestTransferExit, appID, connectionID, sequenceNo, transferRequestParameterRecord,responseCode)
        }
    }
    namespace j1939
    {
        namespace request
        {
            struct ReadPGNs
            {
                std::string appID;
                std::string connectionID;
                std::string sequenceNo;
                std::vector<std::string> pgnNo;
            };
            
            struct SelectMonitoring{
                std::string appID;
                std::string connectionID;
                std::string sequenceNo;
                std::vector<std::string> pgnNo;
            };

            struct ExecuteMonitoring{
                std::string appID;
                std::string connectionID;
                std::string sequenceNo;
                std::string operation;
                std::string sampleRate;
            };

            NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ReadPGNs, appID, connectionID, sequenceNo, pgnNo)
            NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SelectMonitoring, appID, connectionID, sequenceNo, pgnNo)
            NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ExecuteMonitoring, appID, connectionID, sequenceNo, operation, sampleRate)

        }
        namespace response
        {
            struct spnResponse
            {
                std::string spnNo;
                std::string spnValue;
            };

            struct PgnData
            {
                std::string pgnNo;
                std::string rawData;
                bool decoded;
                std::vector<spnResponse> spn;
            };

            struct ReadPGNs
            {
                std::string appID;
                std::string connectionID;
                std::string sequenceNo;
                std::vector<PgnData> data;
                std::string responseCode;
            };
            struct SelectMonitoring{
                std::string appID;
                std::string connectionID;
                std::string sequenceNo;
                std::string responseCode;
            };

            struct ExecuteMonitoring{
                std::string appID;
                std::string connectionID;
                std::string sequenceNo;
                std::string responseCode;
            };

            NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(spnResponse, spnNo, spnValue)
            NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(PgnData, pgnNo, rawData, decoded, spn)
            NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ReadPGNs, appID, connectionID, sequenceNo, data, responseCode)
            NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SelectMonitoring, appID, connectionID, sequenceNo, responseCode)
            NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ExecuteMonitoring, appID, connectionID, sequenceNo, responseCode)


        }
    }
}
class Translator
{
private:
    std::shared_ptr<InterContainerMessenger> protocolClient;
    std::atomic<int> sequence{0};
    std::condition_variable receivedConditionVariable;
    std::mutex mainLock;
    std::string receivedSequence;
    jsonType receivedMessage;

    class UDS
    {
        Translator *translatorPointer;
        std::string connectionId;

    public:
        // UDS constructor
        explicit UDS(Translator *const translator) : translatorPointer(translator){

                                                     };
       

        /** @brief - set connection id upon succesful connection to the ecu
         * @param id - const string reference type representing connection id
         * @return void
         */
        void setConnectionId(const std::string &id);
      

        /** @brief - get connection id method to receive connection id 
         * @param None - No input parameters
         * @return string - returns connection id
         */
        std::string getConnectionId();

        /** @brief - OpenCommunicationChannel method opens a connection with requested ecu
         * @param None - No input parameters
         * @return jsonType - returns payload with connection details.
         */
        jsonType OpenCommunicationChannel(const std::string &toolAddress, const std::string &ecuAddress,const std::string &canFormat);
       

        /** @brief - Transfer data (0x36)method transfers data to the ECU.
         * @param data - string reference type representing data to be transferred
         * @param blockSequenceNumber - string  type increemented for subsequent transfer request
         * @return jsonType - returns jsonType type
         */
        jsonType TransferData(const std::string &data, const std::string &blockSequenceNumber);
    

        /** @brief - request transfer exit(0x37) method terminates a data tranfer to the ecu
         * @param transferRequestParameterRecord - string type representing parameter record to support data transfer
         * @return jsonType - returns jsonType type response payload
         */
        jsonType RequestTransferExit(const std::string &transferRequestParameterRecord);
      

        /** @brief - routine control request (0x31) method to execute defined steps sequentially
         * @param routineControlOptionRecord - string type to pass data to routine identifier
         * @param routineIdentifier - string type to identify local routine
         * @param subFunction - string type representing selected control for the routine.
         * @return jsonType - returns jsonType type response payload
         */
        jsonType RoutineControlRequest(const std::string &routineControlOptionRecord, const std::string &routineIdentifier, const std::string &subFunction);
       
        /** @brief - read by data identifier method(0x22) requests data values for requested data identifiers
         * @param did - const vector<string> type for two byte dataidentifier(DID)
         * @return jsonType - returns jsonType type response payload
         */
        jsonType ReadByDataIdentifier(const std::vector<std::string> &did);
        
        /** @brief - request download (0x34) initiates data transfer to ECU
         * @param address - string type representing starting point of memory where data is to be written
         * @param memsize - string type representing the memory size of total amount of data transferred
         * @param dataFormatId - string type specifying one byte value for compression
         * @param alFormatIdentifier - one byte value defining length of memory address and address paramter
         * @return jsonType - returns jsonType type reponse payload
         */
        jsonType RequestDownload(const std::string &address, const std::string &memsize,
                                 const std::string &dataFormatId,const std::string &alFormatIdentifier);
      

        /** @brief - close communication channel to close communication channel
         * @param None - No input parameters
         * @return void
         */
        void CloseCommunicationChannel();

        /** @brief - ReadDTC(0x19) method allows to read the diagnostic trouble code
         * @param subFunction - string type representing subfunction to select DTC report type
         * @param dtcStatusMask - string type reuesting DTC info whose status is equivalent to dtcStatusMask
         * @return jsonType - returns jsonType type reponse payload
         */
        jsonType RequestReadDtc(const std::string &subFunction, const std::string &dtcStatusMask);

        /** @brief - RequestTelematicsSession(0x10) method is used to enable different diagnostic sessions in ECU
         * @param subFunction - string type representing subfunction parameter to diagnosticSessionType
         * @return jsonType - returns jsonType type reponse payload
         */

        jsonType RequestTelematicsSession(const std::string &subFunction);

      
        /** @brief - SendTesterPresent(0x3E) method is used to indicate to an ECU that a client is still connected to the vehichle
         * @param subFunction -  string type representing zerosubfunction parameter
         * @return jsonType - returns jsonType type reponse payload
         */

        jsonType SendTesterPresent(const std::string &subFunction);

        /** @brief - ClearDTC(0x14) method allows to clear the diagnostic trouble code
          * @param groupOfDTC - string type representing 3-byte value indicating the group of dtc.
          * @param memorySelection - parameter used to describe respective user defined memory for retrival
          * @return jsonType - returns jsonType type reponse payload
          */

        jsonType RequestClearDtc(const std::string &groupOfDTC, const std::string &memorySelection);

        /** @brief - ReadFreezeFrame(0x19) method allows to read DTC stored record
          * @param dtcStoredDataRecordNumber - string type representing 3-byte value indicating the group of dtc.
          * @return jsonType - returns jsonType type reponse payload
          */
        jsonType RequestReadFreezeFrame(const std::string &dtcStoredDataRecordNumber);

        jsonType WriteDataByIdentifier(const std::vector<translator::uds::request::WriteData> &data);

        /** @brief - RequestCommunicationControl(0x28) request to toggle transmission or reception of ecu msgs
         * @param subFunction - string type representing subFunction parameter controlType contains information related to communication type
         * @param communicationType - string type representing the kind of communication to be controlled
         * @param nodeIdentificationNumberHighByte - string parameter to identify node on a subnetwork.
         * @param nodeIdentificationNumberLowByte - string parameter to identify node on a subnetwork.
         * @return jsonType - returns jsonType type reponse payload
         */
        jsonType RequestCommunicationControl(const std::string &subFunction, const std::string &communicationType,
                                               const std::string &nodeIdentificationNumberHighByte, const std::string &nodeIdentificationNumberLowByte);
    };
    class J1939
    {
        Translator *translatorPointer;
        std::string connectionId;

        /** @brief - set connection id upon succesful connection to the ecu
         * @param id - const string reference type representing connection id
         * @return void
         */
        void setConnectionId(const std::string &id)
        {
            connectionId = id;
        }

        /** @brief - get connection id method to receive connection id 
         * @param None - No input parameters
         * @return string - returns connection id
         */
        std::string getConnectionId();        

    public:
        explicit J1939(Translator *const translator) : translatorPointer(translator)
        {
        }

        void CloseCommunicationChannel();
        

        jsonType OpenCommunicationChannel(const std::string &toolAddress, const std::string &ecuAddress,const std::string &canFormat);
        
        
        /** @brief - ReadJ1939PGNs method allows to read PGN and SPN values
          * @param pgns - vector of pgn's string list
          * @return jsonType - returns jsonType type reponse payload
          */
        jsonType ReadJ1939PGNs(const std::vector<std::string> pgns);
        
        /** @brief - ExecutePGNMonitoring method enables start and stop of pgn monitoring
          * @param operation - string type representing start/stop
          * @param sampleRate - String type input indicating the frequency of PGN monitoring
          * @return jsonType - returns jsonType type reponse payload
          */

        nlohmann::json ExecutePGNMonitoring(const std::string& operation, const std::string& sampleRate);
        

        /** @brief - createSelectMonPGNReq method enables useres to select PGN's for monitoring
          * @param pgns - vector of pgn's string list
          * @return jsonType - returns jsonType type reponse payload
          */
        nlohmann::json createSelectMonPGNReq(const std::vector<std::string>& pgns);
       

    };
    std::unique_ptr<UDS> uds;
    std::unique_ptr<J1939> j1939;
public:
    
    // Translator constructor
    explicit Translator(std::shared_ptr<InterContainerMessenger> Client) : protocolClient(Client)
    {
        uds = std::make_unique<UDS>(this);
        j1939 = std::make_unique<J1939>(this);
    }

    ~Translator() = default;

    /** @brief - SendMessageonInput - publishes mqtt message
     * @param topic - const string reference type representing mqtt topic
     * @param payload - const string reference type representing payload to be published
     * @return void
     */
    void SendMessageonInput(const std::string &topic, const std::string &payload, const bool &retain = false) const
    {
        if (protocolClient != nullptr)
        {
            protocolClient->SendMessage(topic, payload, retain);
        }
    }

    /** @brief - get uds value
     * @param None - No input parameters
     * @return UDS pointer
     */
    std::unique_ptr<UDS> &getUDSPtr()
    {
        return uds;
    }

    /** @brief - getSequence method give the squenece number of the published message
     * @param None - No input parameters
     * @return string - returns string type
     */
    std::string getSequence()
    {
        sequence = (sequence + 1) % global::MAX_ROUND_NUM;
        return to_string(sequence);
    }

    /** @brief - getResponse fetches the response payload for specific sequence no
     * @param sequenceVal - const string reference type
     * @return jsonType - returns jsonType type
     */
    jsonType getResponse(const std::string &sequenceVal,
                         const int time = RETRY_TIMEOUT);
    
    /** @brief - notify method notifies other containers
     * @param topic - const string reference type
     * @param message - const jsonType type
     * @return jsonType - returns jsonType type
     */
    void notify(const std::string &topic, const jsonType message);

    /** @brief - RequestSetConfigParameter is used to set the parameter value
     * @param params - array of config parameters.
     * @return jsonType - returns jsonType type reponse payload
     */
    jsonType RequestSetConfigParameter(const std::string &connectionId, const std::vector<translator::setconfigparams::request::ComParams> &params);

    /** @brief - WaitForAddressClaimBroadcast method waits for the address claim
     * @param None - No input parameters
     * @return jsonType - returns jsonType type
     */
    jsonType WaitForAddressClaimBroadcast();
   
    /** @brief - request get address claim method
     * @param None - No input parameters
     * @return jsonType - returns jsonType type
     */
    jsonType RequestGetAddressClaim();
    

    /** @brief - closes J1939 communication channel method
     * @param connectionId - const string reference type
     * @return void
     */
    void CloseCommunicationChannel(const std::string &connectionId);
};