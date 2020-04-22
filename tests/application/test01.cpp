
#include <eoepca/argo/application.hpp>
#include <fstream>
#include <eoepca/argo/eoepcaargo.hpp>
#include "gtest/gtest.h"


std::unique_ptr<EOEPCA::EOEPCAargo> getLibArgo(){
    auto lib = std::make_unique<EOEPCA::EOEPCAargo>("./cmake-build-debug/libeoepcaargo.so");
    if (!lib->IsValid()) {
        lib = std::make_unique<EOEPCA::EOEPCAargo>("/project/build/libeoepcaargo.so");
    }
    if (!lib->IsValid()) {
        std::cout << "Library not found\n";
        EXPECT_TRUE(false);
    }
    return lib;
}


TEST(TEST1_WorkflowGeneration, Without_stage_in) {


    auto lib = getLibArgo();

    std::string expected_yamlfile;
    std::string filename = "tests/application/data/test1_workflow.yaml";
    std::ifstream infile(filename);
    if (infile.good()) {
        std::stringstream sBuffer;
        sBuffer << infile.rdbuf();
        expected_yamlfile=sBuffer.str();
    }


    std::unique_ptr<proc_comm_lib_argo::Application> application = std::make_unique<proc_comm_lib_argo::Application>();
    application->setDockerImage("centos:7");
    application->setUseShell(true);
    application->setCommand("echo");
    application->addParam("message", "Hello");
    application->addParam("message1", "World");

    auto run = std::make_unique<proc_comm_lib_argo::Run>();
    run->moveApplication(application);
    std::list<std::string> argoWorkflows{};
    lib->create_workflow_yaml(run.get(), argoWorkflows);
    std::string yamlFile = argoWorkflows.front();


  EXPECT_EQ(yamlFile, expected_yamlfile);
}

TEST(TEST1_WorkflowGeneration, Without_stage_in_with_script) {


    auto lib = getLibArgo();

    std::string expected_yamlfile;
    std::string filename = "tests/application/data/test2_workflow.yaml";
    std::ifstream infile(filename);
    if (infile.good()) {
        std::stringstream sBuffer;
        sBuffer << infile.rdbuf();
        expected_yamlfile=sBuffer.str();
    }

    std::unique_ptr<proc_comm_lib_argo::Application> application = std::make_unique<proc_comm_lib_argo::Application>();
    application->setDockerImage("centos:7");
    application->setUseShell(false);
    application->addParam("message", "Hello");
    application->addParam("message1", "World");
    application->script.command = "python";
    application->script.source = "print(\"{{workflow.parameters.message}} {{workflow.parameters.message1}}\" )";

    auto run = std::make_unique<proc_comm_lib_argo::Run>();
    run->moveApplication(application);
    std::list<std::string> argoWorkflows{};
    lib->create_workflow_yaml(run.get(), argoWorkflows);
    std::string yamlFile = argoWorkflows.front();


    EXPECT_EQ(yamlFile, expected_yamlfile);
}


TEST(TEST1_WorkflowGeneration, With_stage_in) {

    auto lib = getLibArgo();

    std::string expected_yamlfile;
    std::string filename = "tests/application/data/test3_workflow.yaml";
    std::ifstream infile(filename);
    if (infile.good()) {
        std::stringstream sBuffer;
        sBuffer << infile.rdbuf();
        expected_yamlfile=sBuffer.str();
    }

    std::unique_ptr<proc_comm_lib_argo::Application> application = std::make_unique<proc_comm_lib_argo::Application>();
    application->setUseShell(false);
    application->addParam("message","https://catalog.terradue.com/eoepca-sentinel3/search?format=atom&uid=S3A_SR_1_SRA____20200408T215451_20200408T224520_20200409T143326_3029_057_043______LN3_O_ST_003&do=terradue");
    application->script.command="python";
    application->script.source="print(\"Downloaded {{inputs.parameters.message}}\")";
    application->setDockerImage("centos:7");

    std::unique_ptr<proc_comm_lib_argo::NodeTemplate> stageInApplication = std::make_unique<proc_comm_lib_argo::NodeTemplate>();
    stageInApplication->setUseShell(false);
    stageInApplication->script.command="python";
    stageInApplication->script.source="import urllib.request\n"
                                      "import xml.etree.ElementTree as ET\n"
                                      "url = '{{inputs.parameters.message}}'\n"
                                      "response = urllib.request.urlopen(url)\n"
                                      "xml = response.read()\n"
                                      "tree = ET.fromstring(xml)\n"
                                      "enclosure = tree[5][5].get('href')\n"
                                      "print(urllib.parse.quote(enclosure))";
    stageInApplication->setDockerImage("meetup/python");
    application->setStageInApplication(stageInApplication);


    auto run = std::make_unique<proc_comm_lib_argo::Run>();
    run->moveApplication(application);
    std::list<std::string> argoWorkflows{};
    lib->create_workflow_yaml(run.get(), argoWorkflows);
    std::string yamlFile = argoWorkflows.front();


    EXPECT_EQ(yamlFile, expected_yamlfile);

}


TEST(TEST1_WorkflowGeneration, From_app) {


    auto lib = getLibArgo();

    std::string expected_yamlfile;
    std::string filename = "tests/application/data/test2_workflow.yaml";
    std::ifstream infile(filename);
    if (infile.good()) {
        std::stringstream sBuffer;
        sBuffer << infile.rdbuf();
        expected_yamlfile=sBuffer.str();
    }


    std::unique_ptr<proc_comm_lib_argo::Application> application = std::make_unique<proc_comm_lib_argo::Application>();
    application->setDockerImage("centos:7");
    application->setUseShell(false);
    application->addParam("message", "Hello");
    application->addParam("message1", "World");
    application->script.command = "python";
    application->script.source = "print(\"{{workflow.parameters.message}} {{workflow.parameters.message1}}\" )";

    std::string argoWorkflow;
    lib->create_workflow_yaml_from_app(application.get(), argoWorkflow);

    EXPECT_EQ(argoWorkflow, expected_yamlfile);
}