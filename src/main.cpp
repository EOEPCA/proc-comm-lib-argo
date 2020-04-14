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

  std::unique_ptr<proc_comm_lib_argo::Application> application = std::make_unique<proc_comm_lib_argo::Application>();
  application->setDockerImage("centos:7");
  application->addParam("message","Hello World");
  application->setApplication("print(\"{{workflow.parameters.message}}\")");


  ///
  // WITH STAGE IN

/*    std::unique_ptr<proc_comm_lib_argo::Application> application = std::make_unique<proc_comm_lib_argo::Application>();
    application->addParam("message","https://catalog.terradue.com/eoepca-sentinel3/search?format=atom&uid=S3A_SR_1_SRA____20200408T215451_20200408T224520_20200409T143326_3029_057_043______LN3_O_ST_003&do=terradue");
    application->setApplication("print(\"Downloaded {{inputs.parameters.message}}\")");
    application->setDockerImage("centos:7");

    std::unique_ptr<proc_comm_lib_argo::StageInApplication> stageInApplication = std::make_unique<proc_comm_lib_argo::StageInApplication>();
    stageInApplication->setApplication("import urllib.request\n"
                                       "import xml.etree.ElementTree as ET\n"
                                       "url = '{{inputs.parameters.message}}' \n"
                                       "response = urllib.request.urlopen(url)\n"
                                       "xml = response.read()\n"
                                       "tree = ET.fromstring(xml)\n"
                                       "enclosure = tree[5][5].get('href')\n"
                                       "print(urllib.parse.quote(enclosure))");
    stageInApplication->setDockerImage("meetup/python");
    application->setStageInApplication(stageInApplication);


 */
    ///
    // RUN
    auto run = std::make_unique<proc_comm_lib_argo::Run>();
    run->moveApplication(application);
    std::list<std::string> argoWorkflows{};
    lib->create_workflow_yaml(run.get(), argoWorkflows);
    for (auto &argoWorkflow : argoWorkflows) {
        std::cout << argoWorkflow << "\n";
    }


  return 0;
}



