//
// Created by bla on 07/04/20.
//

#ifndef PROC_COMM_LIB_ARGO_WORKFLOWAPI_HPP
#define PROC_COMM_LIB_ARGO_WORKFLOWAPI_HPP


#include <iostream>
#include <eoepca/argo/application.hpp>
#include <string>
#include <list>
#include "../../../src/model/workflow.hpp"
#include "apiconfiguration.hpp"
#include "../../../src/model/apiresponse.hpp"


namespace proc_comm_lib_argo {

    static std::string default_namespace_constant="default";

    class WorkflowApi {

    public:
        WorkflowApi(std::shared_ptr<ApiConfiguration> configuration, std::string d_namespace=default_namespace_constant);
        virtual ~WorkflowApi();

        // api configuration getter and setter
        std::shared_ptr<ApiConfiguration> getConfiguration() const;
        void setConfiguration(std::shared_ptr<ApiConfiguration> configuration);

        // workflow api methods
        model::WorkflowList listWorkflows(std::string _namespace = default_namespace_constant);
        model::Workflow submitWorkflow(Application *application, std::string _namespace = default_namespace_constant);
        model::Workflow getWorkflowFromName(std::string_view workflow_name, std::string _namespace = default_namespace_constant);
        proc_comm_lib_argo::model::ApiResponse deleteWorkflowFromName(std::string_view workflow_name, std::string _namespace = default_namespace_constant);

    protected:
        std::shared_ptr<ApiConfiguration> api_configuration;
        std::string default_namespace;
    };


}

#endif //PROC_COMM_LIB_ARGO_WORKFLOWAPI_HPP
