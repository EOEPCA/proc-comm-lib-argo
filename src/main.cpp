#include <eoepca/argo/eoepcaargo.hpp>
#include <iostream>
#include <yaml-cpp/node/node.h>
#include <proc-comm-lib-argo/api/apiconfiguration.hpp>
#include <proc-comm-lib-argo/api/workflowapi.hpp>
#include <eoepca/argo/model/apiexception.hpp>
#include <zconf.h>

/**
 * Returns libeoepcaargo.so library
 * @return
 */
std::unique_ptr<EOEPCA::EOEPCAargo> getLib() {
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

void test_workflow_generation() {

    auto lib = getLib();
    if (lib == nullptr) {
        throw 5;
    }

    ///
    // WITHOUT STAGE IN
    // WITH SCRIPT
    std::unique_ptr<proc_comm_lib_argo::Application> application = std::make_unique<proc_comm_lib_argo::Application>();
    application->setDockerImage("centos:7");
    application->setUseShell(false);
    application->addParam("message", "Hello");
    application->addParam("message1", "World");
    application->script.command = "python";
    application->script.source = "print(\"{{workflow.parameters.message}} {{workflow.parameters.message1}}\" )";

    ///
    // WITHOUT STAGE IN
    // WITHOUT SCRIPT
    std::unique_ptr<proc_comm_lib_argo::Application> application1 = std::make_unique<proc_comm_lib_argo::Application>();
    application1->setDockerImage("centos:7");
    application1->setUseShell(true);
    application1->setCommand("echo");
    application1->addParam("message", "Hello");
    application1->addParam("message1", "World");

    ///
    // WITH STAGE IN
    // WITH SCRIPT
    std::unique_ptr<proc_comm_lib_argo::Application> application2 = std::make_unique<proc_comm_lib_argo::Application>();
    application2->setUseShell(false);
    application2->addParam("message", "https://catalog.terradue.com/eoepca-sentinel3/search?format=atom&uid=S3A_SR_1_SRA____20200408T215451_20200408T224520_20200409T143326_3029_057_043______LN3_O_ST_003&do=terradue");
    application2->script.command = "python";
    application2->script.source = "print(\"Downloaded {{inputs.parameters.message}}\")";
    application2->setDockerImage("centos:7");

    std::unique_ptr<proc_comm_lib_argo::NodeTemplate> stageInApplication = std::make_unique<proc_comm_lib_argo::NodeTemplate>();
    stageInApplication->setUseShell(false);
    stageInApplication->script.command = "python";
    stageInApplication->script.source = "import urllib.request\n"
                                        "import xml.etree.ElementTree as ET\n"
                                        "url = '{{inputs.parameters.message}}'\n"
                                        "response = urllib.request.urlopen(url)\n"
                                        "xml = response.read()\n"
                                        "tree = ET.fromstring(xml)\n"
                                        "enclosure = tree[5][5].get('href')\n"
                                        "print(urllib.parse.quote(enclosure))";
    stageInApplication->setDockerImage("meetup/python");
    application2->setPreProcessingNode(stageInApplication);


    ///
    // RUN
    auto run = std::make_unique<proc_comm_lib_argo::Run>();
    run->moveApplication(application);
    run->moveApplication(application1);
    run->moveApplication(application2);
    std::list<std::string> argoWorkflows{};
    lib->create_workflow_yaml(run.get(), argoWorkflows);
    for (auto &argoWorkflow : argoWorkflows) {
        std::cout << argoWorkflow << "\n";
    }
}

void test_api() {

    // Create api configuration
    std::shared_ptr<proc_comm_lib_argo::ApiConfiguration> apiConf = std::make_shared<proc_comm_lib_argo::ApiConfiguration>();
    apiConf->setArgoApiBaseUrl("http://localhost:8080");
    apiConf->setK8ApiBaseUrl("http://127.0.0.1:2746");


    // Instantiating workflow api
    std::shared_ptr<proc_comm_lib_argo::WorkflowApi> workflowApi = std::make_shared<proc_comm_lib_argo::WorkflowApi>(apiConf);


    // Submit workflow
    std::unique_ptr<proc_comm_lib_argo::Application> application = std::make_unique<proc_comm_lib_argo::Application>();
    application->setDockerImage("centos:7");
    application->setUseShell(true);
    application->setCommand("echo");
    application->addParam("arg1", "Hello");
    application->addParam("arg2", "World");

    std::string workflowName;
    try {
        proc_comm_lib_argo::model::Workflow workflow = workflowApi->submitWorkflow(application.get());
        workflowName = workflow.get_metadata()->get_name()->c_str();
        std::cout << "Created worklflow name: " << workflow.get_metadata()->get_name()->c_str() << std::endl;
    } catch (proc_comm_lib_argo::ApiException e) {
        std::cout << "Oopss something went wrong " << std::endl;
        std::cout << "Error message: " << e.getMessage() << std::endl;
        std::cout << "Error code: " << e.getErrorCode() << std::endl;
        std::cout << "Content: " << e.getContent() << std::endl;
    }

    // List all workflows
    try {
        auto list = workflowApi->listWorkflows();
        std::cout << "Api version: " << list.get_api_version()->c_str();
        std::cout << "Namespace: " << list.get_items()->front().get_metadata()->get_metadata_namespace()->c_str() << std::endl;
        std::cout << "Number of workflows: " << list.get_items()->size() << std::endl;
        std::string wfName = list.get_items()->front().get_metadata()->get_name()->c_str();
        std::cout << "Name of first workflow: " << wfName << std::endl;
    } catch (proc_comm_lib_argo::ApiException e) {
        std::cout << "Oopss something went wrong " << std::endl;
        std::cout << "Error message: " << e.getMessage() << std::endl;
        std::cout << "Error code: " << e.getErrorCode() << std::endl;
        std::cout << "Content: " << e.getContent() << std::endl;
    }
    sleep(10);
    try {
        auto workflow = workflowApi->getWorkflowFromName(workflowName);
        std::cout << "Name of workflow: " << workflow.get_metadata()->get_name()->c_str() << std::endl;
        std::cout << "Name of entrypoint: " << workflow.get_spec()->get_entrypoint()->c_str() << std::endl;
        std::cout << "status phase: " << workflow.get_status()->get_phase()->c_str() << std::endl;
    } catch (proc_comm_lib_argo::ApiException e) {
        std::cout << "Oopss something went wrong " << std::endl;
        std::cout << "Error message: " << e.getMessage() << std::endl;
        std::cout << "Error code: " << e.getErrorCode() << std::endl;
        std::cout << "Content: " << e.getContent() << std::endl;
    }

    sleep(10);
    try {
        auto results = workflowApi->getWorkflowResultsFromName(workflowName);
        std::cout << "Results " << std::endl;

        for (auto &[k, p] : results) {
            std::cout << k << " " << p << "\n";
        }
    } catch (proc_comm_lib_argo::ApiException e) {
        std::cout << "Oopss something went wrong " << std::endl;
        std::cout << "Error message: " << e.getMessage() << std::endl;
        std::cout << "Error code: " << e.getErrorCode() << std::endl;
        std::cout << "Content: " << e.getContent() << std::endl;
    }

    try {
        auto status = workflowApi->deleteWorkflowFromName(workflowName);
        std::cout << "Delete status: " << status.get_status()->c_str();
    } catch (proc_comm_lib_argo::ApiException e) {
        std::cout << "Oopss something went wrong " << std::endl;
        std::cout << "Error message: " << e.getMessage() << std::endl;
        std::cout << "Error code: " << e.getErrorCode() << std::endl;
        std::cout << "Content: " << e.getContent() << std::endl;
    }


}
void pre_and_post_processing() {
    auto lib = getLib();
    if (lib == nullptr) {
        throw 5;
    }


    // application object
    std::unique_ptr<proc_comm_lib_argo::Application> application = std::make_unique<proc_comm_lib_argo::Application>();

    // pre processing node
    std::unique_ptr<proc_comm_lib_argo::NodeTemplate> stageInApplication = std::make_unique<proc_comm_lib_argo::NodeTemplate>();
    stageInApplication->setDockerImage("centos:7");
    stageInApplication->setUseShell(true);
    stageInApplication->setCommand("curl -s -L");


    // main application
    application->addParam("reference_input", "https://loripsum.net/generate.php?p=1&l=short");
    application->setDockerImage("centos:7");
    application->setUseShell(true);
    application->setCommand("echo");

    // adding pre processing to application
    application->setPreProcessingNode(stageInApplication);


    auto run = std::make_unique<proc_comm_lib_argo::Run>();
    run->moveApplication(application);
    std::list<std::string> argoWorkflows{};
    lib->create_workflow_yaml(run.get(), argoWorkflows);
    std::string yamlFile = argoWorkflows.front();
    std::cout << yamlFile << std::endl;
}

int main() {

    // workflow generation
    //test_workflow_generation();

    // testing api
    //test_api();

    // pre and post processing nodes
    pre_and_post_processing();

    return 0;
}



