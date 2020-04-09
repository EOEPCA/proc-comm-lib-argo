
#include <proc_comm_lib_argo/application.hpp>
#include <proc_comm_lib_argo/argoworkflowapi.hpp>
#include <fstream>
#include "gtest/gtest.h"

#define TEST_CASE_DIRECTORY GetDirectoryName(__FILE__)



bool is_file_exist(std::basic_string<char> fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}

TEST(ARGO_WORKFLOW_LIB, WorkflowGeneration) {


    std::cout << "Starting test" << std::endl;

    std::string filename = "application/data/test1_workflow.yaml";

    std::string expected_yamlfile = "asdasd";


    std::unique_ptr<proc_comm_lib_argo::Application> application = std::make_unique<proc_comm_lib_argo::Application>();
    application->addParam("hello");
    application->addParam("world");
    application->setApplication("echo");

    auto run = std::make_unique<proc_comm_lib_argo::Run>();
    run->setDockerImage("centos:7");
    run->moveApplication(application);

    std::unique_ptr<proc_comm_lib_argo::WorkflowUtils> workflowUtils = std::make_unique<proc_comm_lib_argo::WorkflowUtils>();
    std::string yamlFile = workflowUtils->create_workflow_yaml(run.get());


  EXPECT_EQ(yamlFile, expected_yamlfile);
}
