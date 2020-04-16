//
// Created by bla on 07/04/20.
//

#ifndef PROC_COMM_LIB_ARGO_ARGOWORKFLOWAPI_HPP
#define PROC_COMM_LIB_ARGO_ARGOWORKFLOWAPI_HPP


#include <iostream>
#include <eoepca/argo/application.hpp>
#include <string>
#include <list>
#include "../../src/model/workflow.hpp"


namespace proc_comm_lib_argo {


    class WorkflowApi {

    public:
        WorkflowApi() {};

        ~WorkflowApi() {};

        proc_comm_lib_argo::model::Workflow listWorkflows(std::string name = "default");

        proc_comm_lib_argo::model::Workflow submitWorkflow(Application *application, std::string name = "default");

        proc_comm_lib_argo::model::Workflow
        getWorkflowFromName(std::string_view workflow_name, std::string name = "default");

        proc_comm_lib_argo::model::Workflow
        deleteWorkflowFromName(std::string_view workflow_name, std::string name = "default");
    };
}

#endif //PROC_COMM_LIB_ARGO_ARGOWORKFLOWAPI_HPP
