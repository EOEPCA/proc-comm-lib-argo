//
// Created by bla on 07/04/20.
//

#include <proc-comm-lib-argo/argoworkflowapi.hpp>
#include <iostream>
#include <yaml-cpp/yaml.h>
#include <fstream>
#include "../model/workflow.hpp"

namespace proc_comm_lib_argo {


    YAML::Node getMainTemplateNode(std::string app_name, std::string app_template_name) {

        YAML::Node main_template;
        main_template["name"] = "main";
        main_template["steps"][0][0]["name"] = "stage-in";
        main_template["steps"][0][0]["template"] = "stage-in-template";
        main_template["steps"][1][0]["name"] = app_name;
        main_template["steps"][1][0]["template"] = app_template_name;
        main_template["steps"][2][0]["name"] = "stage-out";
        main_template["steps"][2][0]["template"] = "stage-out-template";
        return main_template;
    }

    YAML::Node getStageInTemplateNode() {
        YAML::Node stage_in_template;
        stage_in_template["name"] = "stage-in-template";
        stage_in_template["container"]["script"]["image"] = "centos:7";
        stage_in_template["container"]["script"]["command"][0] = "echo";
        stage_in_template["container"]["script"]["command"].SetStyle(YAML::EmitterStyle::Flow);


        YAML::Emitter script_out;

        YAML::Node scriptNode;
        script_out << YAML::Literal << "print('stage-in')";



        stage_in_template["container"]["script"]["source"] = script_out.c_str();
        stage_in_template["resources"]["limits"]["memory"] = "32Mi";
        stage_in_template["resources"]["limits"]["cpu"] = "100m";

        return stage_in_template;
    }


    YAML::Node getStageOutTemplateNode() {
        YAML::Node stage_out_template;
        stage_out_template["name"] = "stage-out-template";
        stage_out_template["container"]["image"] = "centos:7";
        stage_out_template["container"]["command"][0] = "echo";
        stage_out_template["container"]["command"].SetStyle(YAML::EmitterStyle::Flow);
        std::vector<std::string> stage_out_template_args;
        stage_out_template_args.push_back("stage-out");
        stage_out_template["container"]["args"] = stage_out_template_args;
        stage_out_template["container"]["args"].SetStyle(YAML::EmitterStyle::Flow);
        stage_out_template["resources"]["limits"]["memory"] = "32Mi";
        stage_out_template["resources"]["limits"]["cpu"] = "100m";

        return stage_out_template;
    }


    YAML::Node getAppTemplate(std::string app_template_name, std::string docker_image, std::string app_command,
                              std::vector<std::string> app_args) {

        YAML::Node app_template;
        app_template["name"] = app_template_name;
        app_template["container"]["image"] = docker_image;
        app_template["container"]["command"][0] = app_command;
        app_template["container"]["command"].SetStyle(YAML::EmitterStyle::Flow);
        app_template["container"]["args"] = app_args;
        app_template["container"]["args"].SetStyle(YAML::EmitterStyle::Flow);
        app_template["resources"]["limits"]["memory"] = "32Mi";
        app_template["resources"]["limits"]["cpu"] = "100m";

        return app_template;

    }



    void addNewTemplate(YAML::Emitter &out, std::string name, std::string image, std::string command, std::string scriptLanguage, std::map<std::string, std::string> inputs, std::string memory, std::string  cpu ){

            out << YAML::BeginMap ;
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
                        out << YAML::Value << YAML::Literal << command;//"print(\"{{inputs.parameters.message}}  + stage-out\")";
                    out << YAML::EndMap ;

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


    void generateYamlFromApp(Application &app) {
        YAML::Emitter out;

        std::string app_name = "eoepca-app";
        std::string app_template_name = app_name + "-template";
        std::string workflow_name = app_name + "-";
        std::string workflow_namespace = "default";

        std::string docker_image = app.getDockerImage();
        std::string app_command = "print(\"Results: {{inputs.parameters.message}}\")"; //app->getApplication();
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
                    for (std::map<std::string,std::string>::iterator it = app_args.begin(); it != app_args.end(); ++it) {
                        out << YAML::BeginMap;
                        out << YAML::Key<< "name" << YAML::Value << it->first;
                        out << YAML::Key<< "value" << YAML::Value << it->second;
                        out << YAML::EndMap;
                    }
                out << YAML::EndSeq;
            out << YAML::EndMap;

        out << YAML::Key << "templates" << YAML::BeginSeq; // begin sequence templates


        YAML::Node main_template;
        main_template["name"] = "main";
        main_template["steps"][0][0]["name"] = "stage-in";
        main_template["steps"][0][0]["template"] = "stage-in-template";
        main_template["steps"][0][0]["arguments"]["parameters"][0]["name"]="message";
        main_template["steps"][0][0]["arguments"]["parameters"][0]["value"]="{{workflow.parameters.message}}";

        main_template["steps"][1][0]["name"] = app_name;
        main_template["steps"][1][0]["template"] = app_template_name;
        main_template["steps"][1][0]["arguments"]["parameters"][0]["name"]="message";
        main_template["steps"][1][0]["arguments"]["parameters"][0]["value"]="{{steps.stage-in.outputs.result}}";

        main_template["steps"][2][0]["name"] = "stage-out";
        main_template["steps"][2][0]["template"] = "stage-out-template";
        main_template["steps"][2][0]["arguments"]["parameters"][0]["name"]="message";
        main_template["steps"][2][0]["arguments"]["parameters"][0]["value"]="{{steps."+app_name+".outputs.result}}";
        out << main_template;


        // begin stagein template
        addNewTemplate(out,"stage-in-template", "centos:7", "print(\"stage-in\")", "python",{},"32Mi","100m" );


        // begin eoepca-app
        addNewTemplate(out,app_template_name, docker_image, app_command, "python",{},"32Mi","100m" );


        // begin stageout template
        addNewTemplate(out,"stage-out-template", "centos:7", "print(\"Results: {{inputs.parameters.message}}\")", "python",{},"32Mi","100m" );


        out << YAML::EndSeq; // end sequence templates

        out << YAML::EndMap; // endmap spec

        std::cout << "Here's the output YAML:\n" << out.c_str();

    }

// create workflow yaml from application class
    void WorkflowUtils::create_workflow_yaml(Run *run,std::list<std::string>& yaml_list) {


        // loop through all applications
        for (auto &app: run->getApplications())
        {
            generateYamlFromApp( *app);
        }


    }




}
