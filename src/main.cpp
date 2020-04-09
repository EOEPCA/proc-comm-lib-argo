#include <iostream>
#include <proc_comm_lib_argo/application.hpp>
#include <yaml-cpp-yaml-cpp-0.6.3/include/yaml-cpp/node/node.h>
#include <yaml-cpp-yaml-cpp-0.6.3/include/yaml-cpp/yaml.h>
#include <fstream>
#include <proc_comm_lib_argo/argoworkflowapi.hpp>

int main() {

    std::cout << "Starting test" << std::endl;

    std::string filename = "file1.yaml";

    std::string txt;
    std::ifstream file(filename);

    if (file.is_open())
        while (file.good())
            getline(file, txt);
    file.close();

    std::cout << txt << std::endl;




    std::unique_ptr<proc_comm_lib_argo::Application> application = std::make_unique<proc_comm_lib_argo::Application>();
    application->addParam("hello");
    application->addParam("world");
    application->setApplication("echo");

    auto run = std::make_unique<proc_comm_lib_argo::Run>();
    run->setDockerImage("centos:7");
    run->moveApplication(application);

    std::unique_ptr<proc_comm_lib_argo::WorkflowUtils> workflowUtils = std::make_unique<proc_comm_lib_argo::WorkflowUtils>();
    workflowUtils->create_workflow_yaml(run.get());

    return 0;
}
