//
// Created by bla on 07/04/20.
//

#include <proc-comm-lib-argo/argoworkflowapi.hpp>
#include <iostream>
#include <yaml-cpp/yaml.h>
#include <fstream>
#include "../model/workflow.hpp"

namespace proc_comm_lib_argo {



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
                        out << YAML::Value << YAML::Literal << command;
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

        bool hasStageIn=app.getStageInApplication()!=NULL;


        std::string docker_image = app.getDockerImage();
        std::string app_command = app.getApplication();
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

        int stepCounter=0;
        if(hasStageIn){
            main_template["steps"][stepCounter][0]["name"] = "stage-in";
            main_template["steps"][stepCounter][0]["template"] = "stage-in-template";
            int paramCounter=0;
            for (std::map<std::string,std::string>::iterator it = app_args.begin(); it != app_args.end(); ++it) {
                main_template["steps"][stepCounter][0]["arguments"]["parameters"][paramCounter]["name"] = it->first;
                main_template["steps"][stepCounter][0]["arguments"]["parameters"][paramCounter]["value"] = "{{workflow.parameters."+it->first+"}}";
                paramCounter++;
            }
            stepCounter++;
        }


        main_template["steps"][stepCounter][0]["name"] = app_name;
        main_template["steps"][stepCounter][0]["template"] = app_template_name;
        main_template["steps"][stepCounter][0]["arguments"]["parameters"][0]["name"]="message";
        if(hasStageIn){
            main_template["steps"][stepCounter][0]["arguments"]["parameters"][0]["value"]="{{steps.stage-in.outputs.result}}";}
        else{
            int paramCounter=0;
            for (std::map<std::string,std::string>::iterator it = app_args.begin(); it != app_args.end(); ++it) {
                main_template["steps"][stepCounter][0]["arguments"]["parameters"][paramCounter]["name"] = it->first;
                main_template["steps"][stepCounter][0]["arguments"]["parameters"][paramCounter]["value"] ="{{workflow.parameters."+it->first+"}}";
                paramCounter++;
            }
        }
        stepCounter++;

        main_template["steps"][stepCounter][0]["name"] = "stage-out";
        main_template["steps"][stepCounter][0]["template"] = "stage-out-template";
        main_template["steps"][stepCounter][0]["arguments"]["parameters"][0]["name"]="message";
        main_template["steps"][stepCounter][0]["arguments"]["parameters"][0]["value"]="{{steps."+app_name+".outputs.result}}";




        out << main_template;

        if(hasStageIn) {
            // begin stagein template
            addNewTemplate(out, "stage-in-template", app.getStageInApplication()->getDockerImage(), app.getStageInApplication()->getApplication(), "python", {}, "32Mi", "100m");
        }

        // begin eoepca-app
        addNewTemplate(out,app_template_name, docker_image, app_command, "python",{},"32Mi","100m" );


        // begin stageout template
        addNewTemplate(out,"stage-out-template", "centos:7", "print(\"Results: {{inputs.parameters.message}}\")", "python",{},"32Mi","100m" );


        out << YAML::EndSeq; // end sequence templates

        out << YAML::EndMap; // endmap spec

        std::cout <<  out.c_str();

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
