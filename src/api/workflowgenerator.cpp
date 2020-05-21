//
// Created by bla on 15/04/20.
//

#include <eoepca/argo/application.hpp>
#include <yaml-cpp-yaml-cpp-0.6.3/include/yaml-cpp/emittermanip.h>
#include <proc-comm-lib-argo/api/workflowgenerator.hpp>
#include <yaml-cpp-yaml-cpp-0.6.3/include/yaml-cpp/yaml.h>

namespace proc_comm_lib_argo {

    void WorkflowGenerator::addNewTemplate(YAML::Emitter &out, std::string name, NodeTemplate *node, std::map<std::string, std::string> params, std::string outputParamName, bool initialNode = false, std::map<std::string, std::string> volume = {}) {

        out << YAML::BeginMap;
        out << YAML::Key << "name";
        out << YAML::Value << name;

        out << YAML::Key << "inputs";
        out << YAML::BeginMap;
        out << YAML::Key << "parameters";
        out << YAML::BeginSeq;

        for (auto const &param : params) {
            out << YAML::BeginMap;
            out << YAML::Key << "name";
            out << YAML::Value << param.first;
            out << YAML::EndMap;
        }

        out << YAML::EndSeq;
        out << YAML::EndMap;

        if (node->isUseShell()) {
            out << YAML::Key << "container";
            out << YAML::BeginMap; // container begin map
            out << YAML::Key << "image";
            out << YAML::Value << node->getDockerImage().c_str();
            out << YAML::Key << "command";
            out << YAML::Value << YAML::Flow << YAML::BeginSeq << "sh" << "-c" << YAML::EndSeq;
            out << YAML::Key << "args";

            out << YAML::Value << YAML::Flow << YAML::BeginSeq;

            std::string command = node->getCommand().c_str();

            for (auto const &param : params) {
                command += " '{{inputs.parameters." + param.first + "}}'";
            }

            if (node->isIncludeTee()) {
                command += "  | tee /tmp/output.txt";
            }
            out << command;
            out << YAML::EndSeq;

            if (volume.size() != 0) {
                out << YAML::Key << "volumeMounts";
                out << YAML::BeginSeq;
                out << YAML::BeginMap;
                out << YAML::Key << "name" << YAML::Value << volume["volumeName"];
                out << YAML::Key << "mountPath" << YAML::Value << volume["volumeMountPath"];
                out << YAML::EndMap;
                out << YAML::EndSeq;
            }

            out << YAML::EndMap; // container end map


            if (!outputParamName.empty()) {
                /// start outputs
                out << YAML::Key << "outputs";
                out << YAML::BeginMap;
                out << YAML::Key << "parameters";
                out << YAML::BeginSeq;
                out << YAML::BeginMap;
                out << YAML::Key << "name";
                out << YAML::Value << outputParamName;
                out << YAML::Key << "valueFrom";
                out << YAML::BeginMap;
                out << YAML::Key << "path";
                out << YAML::Value << "/tmp/output.txt";
                out << YAML::EndMap;
                out << YAML::EndMap;
                out << YAML::EndSeq;
                out << YAML::EndMap;
                //// end outputs
            }

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
     * Generates Yaml string from ADES command
     * @param app
     * @return
     */
    std::string WorkflowGenerator::generateYamlFromApp(Application &app) {
        YAML::Emitter out;

        std::map<std::string, std::string> volume = app.getVolume();

        std::string app_name = "eoepca-app";
        if (!app.getRunId().empty() && !app.getUuidBaseId().empty()) {
            app_name = app.getRunId() + app.getUuidBaseId();
        }
        std::string app_template_name = app_name + "-template";
        std::string workflow_name = app_name + "-";
        std::string workflow_namespace = "default";

        bool hasStageIn = app.getPreProcessingNode() != nullptr;

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
        out << YAML::Value << app_name + "-";
        out << YAML::Key << "namespace";
        out << YAML::Value << "default";
        out << YAML::EndMap;

        // spec
        out << YAML::Key << "spec" << YAML::BeginMap; // beginmap spec

        // entrypoint
        out << YAML::Key << "entrypoint";
        out << YAML::Value << "main";

        if (volume.size() != 0) {
            out << YAML::Key << "volumes";
            out << YAML::BeginSeq;
            out << YAML::BeginMap;
            out << YAML::Key << "name" << YAML::Value << volume["volumeName"];
            out << YAML::Key << "persistentVolumeClaim";
            out << YAML::BeginMap;
            out << YAML::Key << "claimName" << YAML::Value << volume["persistentVolumeClaimName"];
            out << YAML::EndMap;
            out << YAML::EndMap;
            out << YAML::EndSeq;
        }

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
        if (hasStageIn) {
            main_template["steps"][stepCounter][0]["arguments"]["parameters"][0]["name"] = "pre_processing_output";
            main_template["steps"][stepCounter][0]["arguments"]["parameters"][0]["value"] = "{{steps.stage-in.outputs.parameters.pre_processing_output}}";
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
        main_template["steps"][stepCounter][0]["arguments"]["parameters"][0]["name"] = "processing_output";
        if (app.isUseShell()) {
            main_template["steps"][stepCounter][0]["arguments"]["parameters"][0]["value"] = "{{steps." + app_name + ".outputs.parameters.processing_output}}";
        } else {
            main_template["steps"][stepCounter][0]["arguments"]["parameters"][0]["value"] = "{{steps." + app_name + ".outputs.parameters.result}}";
        }

        out << main_template;



        /// TEMPLATE DEFINITIONS

        // STAGEIN
        if (hasStageIn) {
            // begin stagein template
            for (std::map<std::string, std::string>::iterator it = app_args.begin(); it != app_args.end(); ++it) {
                app.getPreProcessingNode()->addParam(it->first, it->second);
            }
            std::map<std::string, std::string> stageinParams = app.getParams();
            WorkflowGenerator::addNewTemplate(out, "stage-in-template", app.getPreProcessingNode().get(), stageinParams, "pre_processing_output", false, volume);

            // APP
            // begin eoepca-app
            std::map<std::string, std::string> appParams;
            appParams.insert(std::make_pair("pre_processing_output", ""));
            WorkflowGenerator::addNewTemplate(out, app_template_name, &app, appParams, "processing_output", hasStageIn, volume);
        } else {
            // APP
            // begin eoepca-app
            WorkflowGenerator::addNewTemplate(out, app_template_name, &app, app.getParams(), "processing_output", hasStageIn, volume);
        }

        // STAGEOUT
        std::map<std::string, std::string> stageoutParams;
        stageoutParams.insert(std::make_pair("processing_output", ""));
        WorkflowGenerator::addNewTemplate(out, "stage-out-template", app.getPostProcessingNode().get(), stageoutParams, "", false, volume);

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
