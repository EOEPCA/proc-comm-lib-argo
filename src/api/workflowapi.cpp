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


namespace proc_comm_lib_argo {


    /**
     * Contructor
     * @param configuration
     * @param d_namespace
     */
    WorkflowApi::WorkflowApi(std::shared_ptr<ApiConfiguration> configuration, std::string d_namespace) : api_configuration(configuration), default_namespace(d_namespace) {

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
    proc_comm_lib_argo::model::Workflow WorkflowApi::submitWorkflow(Application *application, std::string argo_namespace) {

        std::string yaml = proc_comm_lib_argo::WorkflowGenerator::create_workflow_yaml(application);

        const char *inputString = yaml.data();
        size_t inputSize = yaml.length();
        const char *errorMessage = nullptr;
        size_t errorLine = 0;
        y2j::JsonDocument document = y2j::yamlParseBytes(inputString, inputSize, &errorMessage, &errorLine);
        rapidjson::StringBuffer buffer;
        rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);
        std::string worlflowJson = buffer.GetString();
        worlflowJson = "{\"workflow\":" + worlflowJson + "}";

        std::string response;
        postHttp(api_configuration->getBaseUrl() + "/" + api_configuration->getApiPath() + "/namespaces/" + argo_namespace, worlflowJson, response);
        proc_comm_lib_argo::model::Workflow workflow = nlohmann::json::parse(response);


        return workflow;
    }

    /**
     * Finds Workflow by name
     * @param workflow_name
     * @param argo_namespace
     * @return
     */
    proc_comm_lib_argo::model::Workflow WorkflowApi::getWorkflowFromName(std::string_view workflow_name, std::string argo_namespace) {
        return proc_comm_lib_argo::model::Workflow();
    }

    /**
     * Deletes worklfow
     * @param workflow_name
     * @param argo_namespace
     * @return
     */
    proc_comm_lib_argo::model::Workflow WorkflowApi::deleteWorkflowFromName(std::string_view workflow_name, std::string argo_namespace) {
        return proc_comm_lib_argo::model::Workflow();
    }

    /**
     * List all workflows
     * @param argo_namespace
     * @return
     */
    model::WorkflowList WorkflowApi::listWorkflows(std::string argo_namespace) {

        std::string response;
        getHttp(api_configuration->getBaseUrl() + "/" + api_configuration->getApiPath() + "/namespaces/" + argo_namespace + "/workflows/", response);
        proc_comm_lib_argo::model::WorkflowList workflowList = nlohmann::json::parse(response);
        return workflowList;
    }


}
