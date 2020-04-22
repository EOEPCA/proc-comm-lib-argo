//
// Created by bla on 15/04/20.
//

#include <eoepca/argo/application.hpp>
#include <yaml-cpp-yaml-cpp-0.6.3/include/yaml-cpp/emittermanip.h>
#include <proc-comm-lib-argo/api/workflowgenerator.hpp>
#include <yaml-cpp-yaml-cpp-0.6.3/include/yaml-cpp/yaml.h>

namespace proc_comm_lib_argo {


    void WorkflowGenerator::addNewTemplate(YAML::Emitter &out, std::string name, NodeTemplate* node) {


        out << YAML::BeginMap;
        out << YAML::Key << "name";
        out << YAML::Value << name;

        out << YAML::Key << "inputs";
        out << YAML::BeginMap;
        out << YAML::Key << "parameters";
        out << YAML::BeginSeq;
        out << YAML::BeginMap;
        out << YAML::Key << "name";
        out << YAML::Value << "message";
        out << YAML::EndMap;
        out << YAML::EndSeq;
        out << YAML::EndMap;


        if(node->isUseShell()){
            out << YAML::Key << "container";
            out << YAML::BeginMap; // container begin map
            out << YAML::Key << "image";
            out << YAML::Value << node->getDockerImage().c_str();
            out << YAML::Key << "command";
            out << YAML::Value << YAML::Flow << YAML::BeginSeq << "sh" << "-c" << YAML::EndSeq;
            out << YAML::Key << "args";


            out << YAML::Value << YAML::Flow << YAML::BeginSeq ;

            std::string command = node->getCommand().c_str();
            for (auto const& param : node->getParams())
            {
                command += " {{workflow.parameters."+param.first+"}}";
            }
            command += " | tee /tmp/output.txt";
            out << command;
            out << YAML::EndSeq;
            out << YAML::EndMap; // container end map


            /// start outputs
            out << YAML::Key << "outputs";
            out << YAML::BeginMap;
            out << YAML::Key << "parameters";
            out << YAML::BeginSeq ;
            out << YAML::BeginMap;
            out << YAML::Key << "name";
            out << YAML::Value << "param";
            out << YAML::Key << "valueFrom";
            out << YAML::BeginMap;
            out << YAML::Key << "path";
            out << YAML::Value << "/tmp/output.txt";
            out << YAML::EndMap;
            out << YAML::EndMap;
            out << YAML::EndSeq;
            out << YAML::EndMap;
            //// end outputs


        } else {
            out << YAML::Key << "script";
            out << YAML::BeginMap;
            out << YAML::Key << "image";
            out << YAML::Value << node->getDockerImage().c_str();
            out << YAML::Key << "command";
            out << YAML::Value << YAML::Flow << YAML::BeginSeq << node->script.command << YAML::EndSeq;
            out << YAML::Key << "source";
            out << YAML::Value << YAML::Literal << node->script.source;
            out << YAML::EndMap;
        }
        out << YAML::Key << "resources";
        out << YAML::BeginMap;
        out << YAML::Key << "limits";
        out << YAML::BeginMap;
        out << YAML::Key << "memory";
        out << YAML::Value << node->limits.memory;
        out << YAML::Key << "cpu";
        out << YAML::Value << node->limits.cpu;
        out << YAML::EndMap;
        out << YAML::EndMap;
        out << YAML::EndMap;


    }
        /**
         * Adds new Template to yaml emitter
         * @param out
         * @param name
         * @param image
         * @param command
         * @param scriptLanguage
         * @param inputs
         * @param memory
         * @param cpu
         */
    void WorkflowGenerator::addNewTemplate(YAML::Emitter &out, std::string name, std::string image, std::string command, std::string scriptLanguage, std::map<std::string, std::string> inputs, std::string memory, std::string cpu) {

        out << YAML::BeginMap;
        out << YAML::Key << "name";
        out << YAML::Value << name;

        out << YAML::Key << "inputs";
        out << YAML::BeginMap;
        out << YAML::Key << "parameters";
        out << YAML::BeginSeq;
        out << YAML::BeginMap;
        out << YAML::Key << "name";
        out << YAML::Value << "message";
        out << YAML::EndMap;
        out << YAML::EndSeq;
        out << YAML::EndMap;


        out << YAML::Key << "script";
        out << YAML::BeginMap;
        out << YAML::Key << "image";
        out << YAML::Value << image;
        out << YAML::Key << "command";
        out << YAML::Value << YAML::Flow << YAML::BeginSeq << scriptLanguage << YAML::EndSeq;
        out << YAML::Key << "source";
        out << YAML::Value << YAML::Literal << command;
        out << YAML::EndMap;

        out << YAML::Key << "resources";
        out << YAML::BeginMap;
        out << YAML::Key << "limits";
        out << YAML::BeginMap;
        out << YAML::Key << "memory";
        out << YAML::Value << memory;
        out << YAML::Key << "cpu";
        out << YAML::Value << cpu;
        out << YAML::EndMap;
        out << YAML::EndMap;
        out << YAML::EndMap;

    }


    /**
     * Generates Yaml string from ADES command
     * @param app
     * @return
     */
    std::string WorkflowGenerator::generateYamlFromApp(Application &app) {
        YAML::Emitter out;

        std::string app_name = "eoepca-app";
        std::string app_template_name = app_name + "-template";
        std::string workflow_name = app_name + "-";
        std::string workflow_namespace = "default";

        bool hasStageIn = app.getStageInNode() != NULL;


        std::string docker_image = app.getDockerImage();
        std::string app_command = app.getCommand();
        std::map<std::string, std::string> app_args = app.getParams();

        // default values
        std::string apiVersion = "argoproj.io/v1alpha1";
        std::string kind = "Workflow";

        out << YAML::BeginMap;

        //
        // api version
        out << YAML::Key << "apiVersion";
        out << YAML::Value << "argoproj.io/v1alpha1";

        //
        // kind
        out << YAML::Key << "kind";
        out << YAML::Value << "workflow";

        // metadata
        out << YAML::Key << "metadata";
        out << YAML::BeginMap;
        out << YAML::Key << "generateName";
        out << YAML::Value << "eoepca-app-";
        out << YAML::Key << "namespace";
        out << YAML::Value << "default";
        out << YAML::EndMap;

        // spec
        out << YAML::Key << "spec" << YAML::BeginMap; // beginmap spec

        // entrypoint
        out << YAML::Key << "entrypoint";
        out << YAML::Value << "main";

        out << YAML::Key << "arguments";
        out << YAML::BeginMap;
        out << YAML::Key << "parameters";
        out << YAML::BeginSeq;
        for (std::map<std::string, std::string>::iterator it = app_args.begin(); it != app_args.end(); ++it) {
            out << YAML::BeginMap;
            out << YAML::Key << "name" << YAML::Value << it->first;
            out << YAML::Key << "value" << YAML::Value << it->second;
            out << YAML::EndMap;
        }
        out << YAML::EndSeq;
        out << YAML::EndMap;

        out << YAML::Key << "templates" << YAML::BeginSeq; // begin sequence templates

        YAML::Node main_template;
        main_template["name"] = "main";

        int stepCounter = 0;
        if (hasStageIn) {
            main_template["steps"][stepCounter][0]["name"] = "stage-in";
            main_template["steps"][stepCounter][0]["template"] = "stage-in-template";
            int paramCounter = 0;
            for (std::map<std::string, std::string>::iterator it = app_args.begin(); it != app_args.end(); ++it) {
                main_template["steps"][stepCounter][0]["arguments"]["parameters"][paramCounter]["name"] = it->first;
                main_template["steps"][stepCounter][0]["arguments"]["parameters"][paramCounter]["value"] = "{{workflow.parameters." + it->first + "}}";
                paramCounter++;
            }
            stepCounter++;
        }


        main_template["steps"][stepCounter][0]["name"] = app_name;
        main_template["steps"][stepCounter][0]["template"] = app_template_name;
        main_template["steps"][stepCounter][0]["arguments"]["parameters"][0]["name"] = "message";
        if (hasStageIn) {
            main_template["steps"][stepCounter][0]["arguments"]["parameters"][0]["value"] = "{{steps.stage-in.outputs.result}}";
        } else {
            int paramCounter = 0;
            for (std::map<std::string, std::string>::iterator it = app_args.begin(); it != app_args.end(); ++it) {
                main_template["steps"][stepCounter][0]["arguments"]["parameters"][paramCounter]["name"] = it->first;
                main_template["steps"][stepCounter][0]["arguments"]["parameters"][paramCounter]["value"] = "{{workflow.parameters." + it->first + "}}";
                paramCounter++;
            }
        }
        stepCounter++;

        main_template["steps"][stepCounter][0]["name"] = "stage-out";
        main_template["steps"][stepCounter][0]["template"] = "stage-out-template";
        main_template["steps"][stepCounter][0]["arguments"]["parameters"][0]["name"] = "message";
        if(app.isUseShell()){
            main_template["steps"][stepCounter][0]["arguments"]["parameters"][0]["value"] = "{{steps." + app_name + ".outputs.parameters.param}}";
        }
        else {
            main_template["steps"][stepCounter][0]["arguments"]["parameters"][0]["value"] = "{{steps." + app_name + ".outputs.result}}";
        }

        out << main_template;

        if (hasStageIn) {
            // begin stagein template
            WorkflowGenerator::addNewTemplate(out, "stage-in-template", app.getStageInNode().get());
        }

        // begin eoepca-app
        //WorkflowGenerator::addNewTemplate(out, app_template_name, docker_image, app_command, "python", {}, "32Mi", "100m");
        WorkflowGenerator::addNewTemplate(out, app_template_name, &app );

        // begin stageout template
        WorkflowGenerator::addNewTemplate(out, "stage-out-template", "centos:7", "print(\"Results: {{inputs.parameters.message}}\")", "python", {}, "32Mi", "100m");

        out << YAML::EndSeq; // end sequence templates
        out << YAML::EndMap; // endmap spec

        return out.c_str();

    }


    /**
     * creates workflow yaml from ADES Application
     * @param app
     * @return
     */
    std::string WorkflowGenerator::create_workflow_yaml(Application *app) {
        return generateYamlFromApp(*app);

    }


};
