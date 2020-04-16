//
// Created by bla on 09/04/20.
//

#include <eoepca/argo/application.hpp>
#include <string>
#include <list>
#include <proc-comm-lib-argo/workflowgenerator.hpp>

extern "C" long version() { return 1; }

/**
 * Creates a workflow yaml from run
 */
extern "C" void create_workflow_yaml(proc_comm_lib_argo::Run *run,std::list<std::string> &argoWorkflows) {
    // loop through all applications
    for (auto &app: run->getApplications()) {
        argoWorkflows.emplace_back(proc_comm_lib_argo::WorkflowGenerator::WorkflowGenerator::create_workflow_yaml(app.get()));
    }
}

/**
 * Creates a workflow yaml from app
 */
extern "C" void create_workflow_yaml_from_app(proc_comm_lib_argo::Application *app, std::string &argoWorkflow) {
        argoWorkflow=proc_comm_lib_argo::WorkflowGenerator::WorkflowGenerator::create_workflow_yaml(app);
}


