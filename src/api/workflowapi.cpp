//
// Created by bla on 07/04/20.
//

#include <proc-comm-lib-argo/api/workflowapi.hpp>
#include <iostream>
#include <y2j-master/y2j.h>
#include <y2j-master/rapidjson/stringbuffer.h>
#include <y2j-master/rapidjson/prettywriter.h>
#include <proc-comm-lib-argo/api/workflowgenerator.hpp>
#include <beeblebrox/includes/zaphodhands/zaphodhand.hpp>
#include <beeblebrox/includes/beeblebrox/httpresponsestring.hpp>
#include <beeblebrox/includes/beeblebrox/httpcontentstring.hpp>
#include <eoepca/argo/model/apiexception.hpp>



namespace proc_comm_lib_argo {


    /**
     * Constructor
     * @param configuration
     * @param d_namespace
     */
    WorkflowApi::WorkflowApi(std::shared_ptr<ApiConfiguration> configuration, std::string_view d_namespace) : api_configuration(configuration), default_namespace(d_namespace) {

    }

    /**
     * Destructor
     */
    WorkflowApi::~WorkflowApi() {}

    /**
     * Returns Api Configuration
     * @return
     */
    std::shared_ptr<ApiConfiguration> WorkflowApi::getConfiguration() const {
        return api_configuration;
    }

    /**
     * Sets Api Configuration
     * @param configuration
     */
    void WorkflowApi::setConfiguration(std::shared_ptr<ApiConfiguration> configuration) {
        api_configuration = configuration;
    }

    /**
     * Http Get
     * @param id
     * @param ret
     * @return
     */
    long getHttp(std::string_view id, std::string &ret) {
        ZaphodHands::ZaphodHand hand{};
        std::string path{id};
        Beeblebrox::Uri uri(path.data());
        uri.followUri(true);
        uri << Beeblebrox::Uri::Method::GET;
        Beeblebrox::HttpResponseString response{};
        hand << &uri << &response;
        hand.Run();
        ret.assign(response.getContent());
        return uri.getHttpReturnCode();
    }


    /**
    * Http Get
    * @param url
    * @param response_content
    * @return
    */
    long deleteHttp(std::string_view url, std::string &response_content) {
        ZaphodHands::ZaphodHand hand{};
        std::string path{url};
        Beeblebrox::Uri uri(path.data());
        uri.followUri(true);
        uri << Beeblebrox::Uri::Method::DELETE;
        Beeblebrox::HttpResponseString response{};
        hand << &uri << &response;
        hand.Run();
        response_content.assign(response.getContent());
        return uri.getHttpReturnCode();
    }


    /**
     * Htpp Post
     * @param path
     * @param configDeployr
     * @param resp
     * @return
     */
    long postHttp(std::string_view path, std::string_view configDeployr, std::string &resp) {
        ZaphodHands::ZaphodHand hand{};
        std::string fPath{path};
        Beeblebrox::Uri uri(fPath.data());
        uri.followUri(true);
        uri << Beeblebrox::Uri::Method::POST;
        Beeblebrox::HttpContentString contentString{configDeployr.data()};
        Beeblebrox::HttpResponseString response{};
        hand << &uri << &response << &contentString;
        hand.Run();
        auto retCode = uri.getHttpReturnCode();
        resp.assign(response.getContent());
        return retCode;
    }


    /**
     * Submits an Argo Workflow from Ades Application
     * @param application
     * @param name
     * @return
     */
    model::Workflow WorkflowApi::submitWorkflow(Application *application, std::string_view argo_namespace) {

        // creating yaml workflow from command
        std::string yaml = proc_comm_lib_argo::WorkflowGenerator::create_workflow_yaml(application);

        // converting yaml to json
        const char *inputString = yaml.data();
        size_t inputSize = yaml.length();
        const char *errorMessage = nullptr;
        size_t errorLine = 0;
        y2j::JsonDocument document = y2j::yamlParseBytes(inputString, inputSize, &errorMessage, &errorLine);
        rapidjson::StringBuffer buffer;
        rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);
        std::string worlflowJson = buffer.GetString();

        // Submitting workflow
        // Workflow kind must uppercase
        worlflowJson = std::regex_replace(worlflowJson, std::regex("\"kind\": \"workflow\""), "\"kind\": \"Workflow\"");
        std::string response;
        postHttp(api_configuration->getArgoApiBaseUrl() + api_configuration->getArgoApiPath() + "/namespaces/" + argo_namespace.data() + "/workflows", worlflowJson, response);

        // checking response. If there is an error, an exception is thrown
        rapidjson::Document responseDoc;
        responseDoc.Parse(response.c_str());
        if (strcmp(responseDoc["kind"].GetString(), "Status") == 0) {
            std::cout << "throwing exception" << std::endl;
            proc_comm_lib_argo::model::ApiResponse apiResponse = nlohmann::json::parse(response);
            throw ApiException(*apiResponse.get_code().get(), apiResponse.get_message()->c_str(), response);
        }

        // if submit is successfull, the api returns the deleted workflow
        proc_comm_lib_argo::model::Workflow workflow = nlohmann::json::parse(response);
        return workflow;
    }

    /**
     * Finds Workflow by name
     * @param workflow_name
     * @param argo_namespace
     * @return
     */
    model::Workflow WorkflowApi::getWorkflowFromName(std::string_view workflow_name, std::string_view argo_namespace) {

        std::string response;
        getHttp(api_configuration->getArgoApiBaseUrl() + api_configuration->getArgoApiPath() + "/namespaces/" + argo_namespace.data() + "/workflows/" + workflow_name.data(), response);
        proc_comm_lib_argo::model::Workflow workflow = nlohmann::json::parse(response);
        if (workflow.get_kind()->compare("Workflow") != 0) {
            proc_comm_lib_argo::model::ApiResponse apiResponse = nlohmann::json::parse(response);
            throw ApiException(*apiResponse.get_code().get(), apiResponse.get_message()->c_str(), response);
        }
        return workflow;
    }

    /**
     * Deletes worklfow
     * @param workflow_name
     * @param argo_namespace
     * @return
     */
    model::ApiResponse WorkflowApi::deleteWorkflowFromName(std::string_view workflow_name, std::string_view argo_namespace) {

        std::string response;
        deleteHttp(api_configuration->getArgoApiBaseUrl() + api_configuration->getArgoApiPath() + "/namespaces/" + argo_namespace.data() + "/workflows/" + workflow_name.data(), response);
        proc_comm_lib_argo::model::ApiResponse apiResponse = nlohmann::json::parse(response);
        if (apiResponse.get_status()->compare("Failure") == 0) {
            throw ApiException(*apiResponse.get_code().get(), apiResponse.get_message()->c_str(), response);
        }

        return apiResponse;
    }

    /**
     * List all workflows
     * @param argo_namespace
     * @return
     */
    model::WorkflowList WorkflowApi::listWorkflows(std::string_view argo_namespace) {

        std::string response;
        std::cout<<api_configuration->getArgoApiBaseUrl()  + api_configuration->getArgoApiPath() + "/namespaces/" + argo_namespace.data() + "/workflows/";
        getHttp(api_configuration->getArgoApiBaseUrl() + api_configuration->getArgoApiPath() + "/namespaces/" + argo_namespace.data() + "/workflows/", response);
        std::cout<<response;
        proc_comm_lib_argo::model::WorkflowList workflowList = nlohmann::json::parse(response);
        if (workflowList.get_kind()->compare("WorkflowList") != 0) {
            proc_comm_lib_argo::model::ApiResponse apiResponse = nlohmann::json::parse(response);
            throw ApiException(*apiResponse.get_code().get(), apiResponse.get_message()->c_str(), response);
        }
        return workflowList;
    }


}
