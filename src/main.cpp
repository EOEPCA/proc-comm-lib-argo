#include <eoepca/argo/eoepcaargo.hpp>
#include <iostream>
#include <yaml-cpp/node/node.h>
#include <stdio.h>
#include <proc-comm-lib-argo/argoworkflowapi.hpp>
#include <proc-comm-lib-argo/workflowgenerator.hpp>
#include <proc-comm-lib-argo/workflowutils.hpp>


/**
 * Returns libeoepcaargo.so library
 * @return
 */
std::unique_ptr<EOEPCA::EOEPCAargo> getLib(){
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

    auto lib=getLib();
    if (lib== nullptr){
        return 5;
    }

    std::unique_ptr<proc_comm_lib_argo::Application> application = std::make_unique<proc_comm_lib_argo::Application>();
    application->setDockerImage("centos:7");
    application->addParam("message","Hello World");
    application->setApplication("print(\"{{workflow.parameters.message}}\")");


    proc_comm_lib_argo::WorkflowApi api{};
    proc_comm_lib_argo::model::Workflow workflow = api.submitWorkflow(application.get());
    std::cout<< "Worklflow name: " << workflow.get_metadata()->get_name().get();

  return 0;
}



