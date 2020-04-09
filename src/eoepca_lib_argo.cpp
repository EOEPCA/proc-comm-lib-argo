//
// Created by bla on 09/04/20.
//

#include <eoepca/argo/application.hpp>
#include <proc_comm_lib_argo/argoworkflowapi.hpp>
#include <memory>
#include <string>
#include <list>

extern "C" long version() { return 1; }

extern "C" std::list<std::string> create_workflow_yaml(proc_comm_lib_argo::Run *run) {

    auto argo = std::make_unique<proc_comm_lib_argo::WorkflowUtils>();

    return argo->create_workflow_yaml(run);
}


