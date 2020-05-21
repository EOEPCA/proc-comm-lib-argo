//
// Created by bla on 15/04/20.
//

#ifndef PROC_COMM_LIB_ARGO_WORKFLOWGENERATOR_HPP
#define PROC_COMM_LIB_ARGO_WORKFLOWGENERATOR_HPP

#include <yaml-cpp-yaml-cpp-0.6.3/include/yaml-cpp/yaml.h>

namespace proc_comm_lib_argo {

    class WorkflowGenerator {
    public:
        static std::string create_workflow_yaml(Application *app);

    private:
        // Disallow creating an instance of this object
        WorkflowGenerator();

        static std::string generateYamlFromApp(Application &app);

          static void addNewTemplate(YAML::Emitter &out, std::string name, NodeTemplate *node,  std::map<std::string, std::string> params, std::string outputParamName, bool has_stagein, std::map<std::string, std::string> volume);
    };
}

#endif //PROC_COMM_LIB_ARGO_WORKFLOWGENERATOR_HPP
