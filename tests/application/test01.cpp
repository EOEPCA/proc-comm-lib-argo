
#include <eoepca/argo/application.hpp>
#include <proc_comm_lib_argo/argoworkflowapi.hpp>
#include <fstream>
#include <eoepca/argo/eoepcaargo.hpp>
#include "gtest/gtest.h"




TEST(ARGO_WORKFLOW_LIB, WorkflowGeneration) {


    auto lib = std::make_unique<EOEPCA::EOEPCAargo>("./cmake-build-debug/libeoepcaargo.so");
    if (!lib->IsValid()) {
        lib = std::make_unique<EOEPCA::EOEPCAargo>("./build/libeoepcaargo.so");
    }
    if (!lib->IsValid()) {
        //
        std::cout << "Library not found\n";
        EXPECT_TRUE(false);
    }


    std::string expected_yamlfile;
    std::string filename = "tests/application/data/test1_workflow.yaml";
    std::ifstream infile(filename);
    if (infile.good()) {
        std::stringstream sBuffer;
        sBuffer << infile.rdbuf();
        expected_yamlfile=sBuffer.str();
    }


    std::unique_ptr<proc_comm_lib_argo::Application> application = std::make_unique<proc_comm_lib_argo::Application>();
    application->addParam("hello");
    application->addParam("world");
    application->setApplication("echo");

    auto run = std::make_unique<proc_comm_lib_argo::Run>();
    run->setDockerImage("centos:7");
    run->moveApplication(application);



    std::list<std::string> argoWorkflows{};
    lib->create_workflow_yaml(run.get(), argoWorkflows);
    std::string yamlFile = argoWorkflows.front();


  EXPECT_EQ(yamlFile, expected_yamlfile);
}
