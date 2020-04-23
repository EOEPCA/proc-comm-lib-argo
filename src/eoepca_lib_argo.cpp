//
// Created by bla on 09/04/20.
//

#include <eoepca/argo/application.hpp>
#include <string>
#include <list>
#include <proc-comm-lib-argo/api/workflowgenerator.hpp>
#include <proc-comm-lib-argo/api/workflowapi.hpp>

extern "C" long version() { return 1; }

/**
 * Creates a workflow yaml from run
 */
extern "C" void create_workflow_yaml(proc_comm_lib_argo::Run *run, std::list<std::string> &argoWorkflows) {
    // loop through all applications
    for (auto &app: run->getApplications()) {
        argoWorkflows.emplace_back(proc_comm_lib_argo::WorkflowGenerator::WorkflowGenerator::create_workflow_yaml(app.get()));
    }
}

/**
 * Creates a workflow yaml from app
 */
extern "C" void create_workflow_yaml_from_app(proc_comm_lib_argo::Application *app, std::string &argoWorkflow) {
    argoWorkflow = proc_comm_lib_argo::WorkflowGenerator::WorkflowGenerator::create_workflow_yaml(app);
}




extern "C" void list_workflows(std::string_view _namespace, proc_comm_lib_argo::model::WorkflowList &workflowList, std::string_view argoBaseUrl) {

    // Create api configuration
    std::shared_ptr<proc_comm_lib_argo::ApiConfiguration> apiConf = std::make_shared<proc_comm_lib_argo::ApiConfiguration>();
    apiConf->setArgoApiBaseUrl(argoBaseUrl.data());

    // Instantiating workflow api
    std::shared_ptr<proc_comm_lib_argo::WorkflowApi> workflowApi = std::make_shared<proc_comm_lib_argo::WorkflowApi>(apiConf);

    // list method
    workflowList = workflowApi->listWorkflows(_namespace.data());

}

extern "C" void get_workflow_from_name(std::string_view workflow_name, std::string_view _namespace, proc_comm_lib_argo::model::Workflow &workflow, std::string_view argoBaseUrl) {

    // Create api configuration
    std::shared_ptr<proc_comm_lib_argo::ApiConfiguration> apiConf = std::make_shared<proc_comm_lib_argo::ApiConfiguration>();
    apiConf->setArgoApiBaseUrl(argoBaseUrl.data());

    // Instantiating workflow api
    std::shared_ptr<proc_comm_lib_argo::WorkflowApi> workflowApi = std::make_shared<proc_comm_lib_argo::WorkflowApi>(apiConf);

    // get method
    workflow = workflowApi->getWorkflowFromName(workflow_name.data(), _namespace.data());

}


extern "C" void submit_workflow(proc_comm_lib_argo::Application *application, std::string_view _namespace, proc_comm_lib_argo::model::Workflow &workflow, std::string_view argoBaseUrl) {

    // Create api configuration
    std::shared_ptr<proc_comm_lib_argo::ApiConfiguration> apiConf = std::make_shared<proc_comm_lib_argo::ApiConfiguration>();
    apiConf->setArgoApiBaseUrl(argoBaseUrl.data());

    // Instantiating workflow api
    std::shared_ptr<proc_comm_lib_argo::WorkflowApi> workflowApi = std::make_shared<proc_comm_lib_argo::WorkflowApi>(apiConf);

    // get method
    workflow = workflowApi->submitWorkflow(application, _namespace.data());

}


extern "C" void delete_workflow_from_name(std::string_view workflow_name, std::string_view _namespace, proc_comm_lib_argo::model::ApiResponse &response, std::string_view argoBaseUrl) {

    // Create api configuration
    std::shared_ptr<proc_comm_lib_argo::ApiConfiguration> apiConf = std::make_shared<proc_comm_lib_argo::ApiConfiguration>();
    apiConf->setArgoApiBaseUrl(argoBaseUrl.data());

    // Instantiating workflow api
    std::shared_ptr<proc_comm_lib_argo::WorkflowApi> workflowApi = std::make_shared<proc_comm_lib_argo::WorkflowApi>(apiConf);

    // get method
    response = workflowApi->deleteWorkflowFromName(workflow_name.data(), _namespace.data());

}

