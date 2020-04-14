#include <eoepca/argo/application.hpp>
#include <eoepca/argo/eoepcaargo.hpp>
#include <fstream>
#include <iostream>
#include <yaml-cpp/node/node.h>
#include <yaml-cpp/yaml.h>

int main() {

  auto lib = std::make_unique<EOEPCA::EOEPCAargo>("./libeoepcaargo.so");
  if (!lib->IsValid()) {
    // build mac
    lib = std::make_unique<EOEPCA::EOEPCAargo>("./libeoepcaargo.dylib");
  }
  if (!lib->IsValid()) {
    //
    std::cout << "Library not found\n";
    return 5;
  }


  ///
  // WITHOUT STAGE IN
/*
  std::unique_ptr<proc_comm_lib_argo::Application> application = std::make_unique<proc_comm_lib_argo::Application>();
  application->addParam("message","HelloWorld");
  application->setApplication("print(\"{{workflow.parameters.message}}\")");
  application->setDockerImage("centos:7");

  auto run = std::make_unique<proc_comm_lib_argo::Run>();
  run->moveApplication(application);


  std::list<std::string> argoWorkflows{};
  lib->create_workflow_yaml(run.get(), argoWorkflows);
  for (auto &argoWorkflow : argoWorkflows) {
    std::cout << argoWorkflow << "\n";
  }
*/
  ////



    // WITH STAGE IN
    std::unique_ptr<proc_comm_lib_argo::Application> application = std::make_unique<proc_comm_lib_argo::Application>();
    application->addParam("message","HelloWorld");
    application->setApplication("print(\"{{inputs.parameters.message}}\")");
    application->setDockerImage("centos:7");

    std::unique_ptr<proc_comm_lib_argo::StageInApplication> stageInApplication = std::make_unique<proc_comm_lib_argo::StageInApplication>();
    stageInApplication->setApplication("print(\"preprocessed {{inputs.parameters.message}}\")");
    stageInApplication->setDockerImage("centos:7");
    application->setStageInApplication(stageInApplication);

    auto run = std::make_unique<proc_comm_lib_argo::Run>();
    run->moveApplication(application);


    std::list<std::string> argoWorkflows{};
    lib->create_workflow_yaml(run.get(), argoWorkflows);
    for (auto &argoWorkflow : argoWorkflows) {
        std::cout << argoWorkflow << "\n";
    }


  return 0;
}



