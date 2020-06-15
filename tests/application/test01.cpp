#include <eoepca/argo/application.hpp>
#include <fstream>
#include <gtest/gtest.h>
#include "testlibargoutils.hpp"

TEST(TEST1_WorkflowGeneration, Without_pre_processing_node) {

    auto lib = testing::TestLibArgoUtils::getLibArgo();
    std::string expected_yamlfile;
    std::string filename = "tests/application/data/test1_workflow.yaml";
    std::ifstream infile(filename);
    if (infile.good()) {
        std::stringstream sBuffer;
        sBuffer << infile.rdbuf();
        expected_yamlfile = sBuffer.str();
    }

    std::unique_ptr<proc_comm_lib_argo::Application> application = std::make_unique<proc_comm_lib_argo::Application>();
    application->setDockerImage("centos:7");
    application->setUseShell(true);
    application->setCommand("echo");
    application->setIncludeTee(true);
    application->addParam("message", "Hello");
    application->addParam("message1", "World");


    // post processing node
    std::unique_ptr<proc_comm_lib_argo::NodeTemplate> stageOutApplication = std::make_unique<proc_comm_lib_argo::NodeTemplate>();
    stageOutApplication->setDockerImage("centos:7");
    stageOutApplication->setUseShell(true);
    stageOutApplication->setCommand("echo");
    stageOutApplication->setIncludeTee(true);

    application->setPostProcessingNode(stageOutApplication);

    auto run = std::make_unique<proc_comm_lib_argo::Run>();
    run->moveApplication(application);
    std::list<std::string> argoWorkflows{};
    lib->create_workflow_yaml(run.get(), argoWorkflows);
    std::string yamlFile = argoWorkflows.front();

    EXPECT_EQ(yamlFile, expected_yamlfile);
}

TEST(TEST1_WorkflowGeneration, With_pre_processing_node) {

    auto lib = testing::TestLibArgoUtils::getLibArgo();

    std::string expected_yamlfile;
    std::string filename = "tests/application/data/test2_workflow.yaml";
    std::ifstream infile(filename);
    if (infile.good()) {
        std::stringstream sBuffer;
        sBuffer << infile.rdbuf();
        expected_yamlfile = sBuffer.str();
    }

    // application object
    std::unique_ptr<proc_comm_lib_argo::Application> application = std::make_unique<proc_comm_lib_argo::Application>();

    // pre processing node
    std::unique_ptr<proc_comm_lib_argo::NodeTemplate> stageInApplication = std::make_unique<proc_comm_lib_argo::NodeTemplate>();
    stageInApplication->setDockerImage("centos:7");
    stageInApplication->setUseShell(true);
    stageInApplication->setCommand("curl -s -L ");
    stageInApplication->setIncludeTee(true);

    // post processing node
    std::unique_ptr<proc_comm_lib_argo::NodeTemplate> stageOutApplication = std::make_unique<proc_comm_lib_argo::NodeTemplate>();
    stageOutApplication->setDockerImage("centos:7");
    stageOutApplication->setUseShell(true);
    stageOutApplication->setCommand("echo");
    stageOutApplication->setIncludeTee(true);

    // main application
    application->addParam("reference_input", "https://loripsum.net/generate.php?p=1&l=short");
    application->setDockerImage("centos:7");
    application->setUseShell(true);
    application->setCommand("echo");
    application->setIncludeTee(true);

    // adding pre processing to application
    application->setPreProcessingNode(stageInApplication);
    application->setPostProcessingNode(stageOutApplication);

    auto run = std::make_unique<proc_comm_lib_argo::Run>();
    run->moveApplication(application);
    std::list<std::string> argoWorkflows{};
    lib->create_workflow_yaml(run.get(), argoWorkflows);
    std::string yamlFile = argoWorkflows.front();

    EXPECT_EQ(yamlFile, expected_yamlfile);
}

TEST(TEST1_WorkflowGeneration, With_pre_processing_node_and_persistent_volume) {

    auto lib = testing::TestLibArgoUtils::getLibArgo();

    std::string expected_yamlfile;
    std::string filename = "tests/application/data/test3_workflow.yaml";
    std::ifstream infile(filename);
    if (infile.good()) {
        std::stringstream sBuffer;
        sBuffer << infile.rdbuf();
        expected_yamlfile = sBuffer.str();
    }


// application object
    std::unique_ptr<proc_comm_lib_argo::Application> application = std::make_unique<proc_comm_lib_argo::Application>();

// pre processing node
    std::unique_ptr<proc_comm_lib_argo::NodeTemplate> stageInApplication = std::make_unique<proc_comm_lib_argo::NodeTemplate>();
    stageInApplication->setDockerImage("blasco/eoepca-eo-tools");
    stageInApplication->setUseShell(true);
    stageInApplication->setCommand("stagein");

    std::unique_ptr<proc_comm_lib_argo::NodeTemplate> stageOutApplication = std::make_unique<proc_comm_lib_argo::NodeTemplate>();
    stageOutApplication->setDockerImage("blasco/eoepca-eo-tools");
    stageOutApplication->setUseShell(true);
    stageOutApplication->setCommand("cat");

// main application
    application->setRunId("eoepca");
    application->setUuidBaseId("21052020");
    application->addParam("reference_input", "https://catalog.terradue.com/sentinel3/search?uid=S3B_SL_1_RBT____20200520T050759_20200520T051059_20200520T060015_0179_039_105_0360_LN2_O_NR_004");
    application->setDockerImage("blasco/eoepca-eo-tools");
    application->setUseShell(true);
    application->setCommand("process_s3_metadata");

    proc_comm_lib_argo::KubernetesVolumeClaim kubernetesVolumeClaim;
    std::vector<std::string> accessModes;
    accessModes.push_back("ReadWriteOnce");
    kubernetesVolumeClaim.setAccessModes(accessModes);
    kubernetesVolumeClaim.setVolumeName("workingdir");
    kubernetesVolumeClaim.setVolumeSize("2Gi");
    application->setKubernetesVolumeClaim(kubernetesVolumeClaim);

// adding pre processing to application
    application->setPreProcessingNode(stageInApplication);
    application->setPostProcessingNode(stageOutApplication);

    auto run = std::make_unique<proc_comm_lib_argo::Run>();
    run->moveApplication(application);
    std::list<std::string> argoWorkflows{};
    lib->create_workflow_yaml(run.get(), argoWorkflows);
    std::string yamlFile = argoWorkflows.front();

    EXPECT_EQ(yamlFile, expected_yamlfile);
}