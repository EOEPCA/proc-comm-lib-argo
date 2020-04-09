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

  std::cout << "Starting test" << std::endl;

  std::string filename = "file1.yaml";

  std::string txt;
  std::ifstream file(filename);

  if (file.is_open())
    while (file.good())
      getline(file, txt);
  file.close();

  std::cout << txt << std::endl;

  std::unique_ptr<proc_comm_lib_argo::Application> application =
      std::make_unique<proc_comm_lib_argo::Application>();
  application->addParam("hello");
  application->addParam("world");
  application->setApplication("echo");

  auto run = std::make_unique<proc_comm_lib_argo::Run>();
  run->setDockerImage("centos:7");
  run->moveApplication(application);

  // std::unique_ptr<proc_comm_lib_argo::WorkflowUtils> workflowUtils =
  // std::make_unique<proc_comm_lib_argo::WorkflowUtils>();

  std::list<std::string> argoWorkflows{};
  lib->create_workflow_yaml(run.get(), argoWorkflows);
  for (auto &argoWorkflow : argoWorkflows) {
    std::cout << argoWorkflow << "\n";
  }

  return 0;
}
