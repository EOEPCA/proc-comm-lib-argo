//
// Created by bla on 07/04/20.
//

#include <proc-comm-lib-argo/argoworkflowapi.hpp>
#include <iostream>
#include <y2j-master/y2j.h>
#include <y2j-master/rapidjson/stringbuffer.h>
#include <y2j-master/rapidjson/prettywriter.h>
#include <proc-comm-lib-argo/workflowgenerator.hpp>
#include <beeblebrox/includes/zaphodhands/zaphodhand.hpp>
#include <beeblebrox/includes/beeblebrox/httpresponsestring.hpp>
#include <beeblebrox/includes/beeblebrox/httpcontentstring.hpp>



namespace proc_comm_lib_argo {


    long getHttp(std::string_view id, std::string &ret) {

        ZaphodHands::ZaphodHand hand{};
        std::string path{id};

        Beeblebrox::Uri uri(path.data());
        uri.followUri(true);
        uri << Beeblebrox::Uri::Method::GET; // DEFAULT
        //  uri << Beeblebrox::Uri::Method::POST;
        //  uri << Beeblebrox::Uri::Method::PUT;
        //  uri << Beeblebrox::Uri::Method::DELETE

        Beeblebrox::HttpResponseString response{};
        hand << &uri << &response;
        hand.Run();

        //  response.getHeaders()
        //  response.getContent()


        ret.assign(response.getContent());
        return uri.getHttpReturnCode();
    }


    long postHttp(std::string_view path,
                               std::string_view configDeployr,
                               std::string &resp) {
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
     *
     * @param application
     * @param name
     * @return
     */
    proc_comm_lib_argo::model::Workflow WorkflowApi::submitWorkflow(Application *application, std::string argo_namespace) {

        std::string yaml = proc_comm_lib_argo::WorkflowGenerator::create_workflow_yaml(application);

        const char* inputString = yaml.data();
        size_t inputSize = yaml.length();
        const char* errorMessage = nullptr;
        size_t errorLine = 0;
        y2j::JsonDocument document = y2j::yamlParseBytes(inputString, inputSize, &errorMessage, &errorLine);
        rapidjson::StringBuffer buffer;
        rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);
        std::string worlflowJson = buffer.GetString();
        worlflowJson = "{\"workflow\":" + worlflowJson + "}";

        std::string response;
        postHttp("http://127.0.0.1:2746/api/v1/workflows/"+argo_namespace,worlflowJson,response);
        proc_comm_lib_argo::model::Workflow workflow = nlohmann::json::parse(response);


        return workflow;
    }

    proc_comm_lib_argo::model::Workflow
    WorkflowApi::getWorkflowFromName(std::string_view workflow_name, std::string argo_namespace) {
        return proc_comm_lib_argo::model::Workflow();
    }

    proc_comm_lib_argo::model::Workflow
    WorkflowApi::deleteWorkflowFromName(std::string_view workflow_name, std::string argo_namespace) {
        return proc_comm_lib_argo::model::Workflow();
    }

    model::WorkflowList WorkflowApi::listWorkflows(std::string argo_namespace) {

        std::string response;
        getHttp("http://localhost:8080/apis/argoproj.io/v1alpha1/namespaces/"+argo_namespace+"/workflows/",response);
        proc_comm_lib_argo::model::WorkflowList workflowList = nlohmann::json::parse(response);


        return workflowList;
    }
}
