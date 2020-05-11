//
// Created by bla on 07/04/20.
//

#ifndef PROC_COMM_LIB_ARGO_WORKFLOWAPI_HPP
#define PROC_COMM_LIB_ARGO_WORKFLOWAPI_HPP


#include <iostream>
#include <eoepca/argo/application.hpp>
#include <string>
#include <list>
#include <eoepca/argo/model/workflow.hpp>
#include <eoepca/argo/model/apiresponse.hpp>
#include <proc-comm-lib-argo/api/apiconfiguration.hpp>

namespace proc_comm_lib_argo {

    static std::string default_namespace_constant="default";

    class WorkflowApi {

    public:
        WorkflowApi(std::shared_ptr<ApiConfiguration> configuration, std::string_view d_namespace=default_namespace_constant);
        virtual ~WorkflowApi();

        // api configuration getter and setter
        std::shared_ptr<ApiConfiguration> getConfiguration() const;
        void setConfiguration(std::shared_ptr<ApiConfiguration> configuration);

        // workflow api methods
        model::WorkflowList listWorkflows(std::string_view _namespace = default_namespace_constant);
        model::Workflow submitWorkflow(Application *application, std::string_view _namespace = default_namespace_constant);
        model::Workflow getWorkflowFromName(std::string_view workflow_name, std::string_view _namespace = default_namespace_constant);
        model::ApiResponse deleteWorkflowFromName(std::string_view workflow_name, std::string_view _namespace = default_namespace_constant);
        std::list<std::pair<std::string, std::string>> getWorkflowResultsFromName(std::string_view workflow_name, std::string_view _namespace = default_namespace_constant);

    protected:
        std::shared_ptr<ApiConfiguration> api_configuration;
        std::string default_namespace;
    };


}

#endif //PROC_COMM_LIB_ARGO_WORKFLOWAPI_HPP
