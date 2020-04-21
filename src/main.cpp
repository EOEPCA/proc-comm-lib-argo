#include <eoepca/argo/eoepcaargo.hpp>
#include <iostream>
#include <yaml-cpp/node/node.h>
#include <proc-comm-lib-argo/api/apiconfiguration.hpp>
#include <proc-comm-lib-argo/api/workflowapi.hpp>
#include <proc-comm-lib-argo/api/apiexception.hpp>


/**
 * Returns libeoepcaargo.so library
 * @return
 */
std::unique_ptr<EOEPCA::EOEPCAargo> getLib() {
    auto lib = std::make_unique<EOEPCA::EOEPCAargo>("./libeoepcaargo.so");
    if (!lib->IsValid()) {
        // build mac
        lib = std::make_unique<EOEPCA::EOEPCAargo>("./libeoepcaargo.dylib");
    }
    if (!lib->IsValid()) {
        //
        std::cout << "libeoepcaargo library not found\n";
        return nullptr;
    }
    return lib;
}


int main() {

    auto lib = getLib();
    if (lib == nullptr) {
        return 5;
    }

    // Create api configuration
    std::shared_ptr<proc_comm_lib_argo::ApiConfiguration> apiConf = std::make_shared<proc_comm_lib_argo::ApiConfiguration>();
    apiConf->setArgoApiBaseUrl("http://localhost:8080");


    // Instantiating workflow api
    std::shared_ptr<proc_comm_lib_argo::WorkflowApi> workflowApi = std::make_shared<proc_comm_lib_argo::WorkflowApi>(apiConf);


    // Submit workflow
    std::unique_ptr<proc_comm_lib_argo::Application> application = std::make_unique<proc_comm_lib_argo::Application>();
    application->setDockerImage("centos:7");
    application->addParam("message", "Hello World");
    application->setApplication("print(\"{{workflow.parameters.message}}\")");
    std::string workflowName;
    try {
        proc_comm_lib_argo::model::Workflow workflow = workflowApi->submitWorkflow(application.get());
        workflowName = workflow.get_metadata()->get_name()->c_str();
        std::cout << "Created worklflow name: " << workflow.get_metadata()->get_name()->c_str() << std::endl;
    } catch (proc_comm_lib_argo::ApiException e) {
        std::cout << "Oopss something went wrong " << std::endl;
        std::cout << "Error message: " << e.getMessage()->c_str() << std::endl;
        std::cout << "Error code: " << *e.getErrorCode().get() << std::endl;
        std::cout << "Content: " << e.getContent()->c_str() << std::endl;
    }
/*
    // List all workflows
    auto list = workflowApi->listWorkflows();
    std::cout << "Api version: " << list.get_api_version()->c_str();
    std::cout << "Namespace: " << list.get_items()->front().get_metadata()->get_metadata_namespace()->c_str() << std::endl;
    std::cout << "Number of workflows: " << list.get_items()->size() << std::endl;
    std::string wfName = list.get_items()->front().get_metadata()->get_name()->c_str();
    std::cout << "Name of first workflow: " << wfName << std::endl;

    try {
        auto workflow = workflowApi->getWorkflowFromName("eoepca-app-2mwkg");
        std::cout << "Name of workflow: " << workflow.get_metadata()->get_name()->c_str() << std::endl;
        std::cout << "Name of entrypoint: " << workflow.get_spec()->get_entrypoint()->c_str() << std::endl;
        std::cout << "status phase: " << workflow.get_status()->get_phase()->c_str() << std::endl;
    } catch (proc_comm_lib_argo::ApiException e) {
        std::cout << "Oopss something went wrong " << std::endl;
        std::cout << "Error message: " << e.getMessage()->c_str() << std::endl;
        std::cout << "Error code: " << *e.getErrorCode().get() << std::endl;
        std::cout << "Content: " << e.getContent()->c_str() << std::endl;
    }
*/


    try {
        auto status = workflowApi->deleteWorkflowFromName(workflowName);
        std::cout << "Delete status: " << status.get_status()->c_str();
    } catch (proc_comm_lib_argo::ApiException e) {
        std::cout << "Oopss something went wrong " << std::endl;
        std::cout << "Error message: " << e.getMessage()->c_str() << std::endl;
        std::cout << "Error code: " << *e.getErrorCode().get() << std::endl;
        std::cout << "Content: " << e.getContent()->c_str() << std::endl;
    }


    return 0;
}



