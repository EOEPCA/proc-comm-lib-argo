//
// Created by bla on 07/04/20.
//

#include <proc_comm_lib_argo/argoworkflowapi.hpp>
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
        stage_in_template["container"]["image"] = "centos:7";
        stage_in_template["container"]["command"][0] = "echo";
        stage_in_template["container"]["command"].SetStyle(YAML::EmitterStyle::Flow);
        std::vector<std::string> stage_in_template_args;
        stage_in_template_args.push_back("stage-in");
        stage_in_template["container"]["args"] = stage_in_template_args;
        stage_in_template["container"]["args"].SetStyle(YAML::EmitterStyle::Flow);
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


    // create workflow yaml from application class
    void WorkflowUtils::create_workflow_yaml(Run *run,std::list<std::string>& yaml_list) {


        // loop through all applications
        for (auto& app: run->getApplications())
        {
            std::string app_name = "eoepca";
            std::string app_template_name = app_name + "-template";
            std::string workflow_name = app_name + "-";

            std::string docker_image = run->getDockerImage();
            std::string app_command = app->getApplication();
            std::vector<std::string> app_args = app->getParams();

            // default values
            std::string apiVersion = "argoproj.io/v1alpha1";
            std::string kind = "Workflow";


            // root node
            YAML::Node doc;
            doc["apiVersion"] = apiVersion;
            doc["kind"] = kind;

            // name of the workflow spec
            doc["metadata"]["generateName"] = workflow_name;

            // first node to call
            doc["spec"]["entrypoint"] = "main";

            // templates
            doc["spec"]["templates"].push_back(getMainTemplateNode(app_name, app_template_name));
            doc["spec"]["templates"].push_back(getStageInTemplateNode());
            doc["spec"]["templates"].push_back(getStageOutTemplateNode());
            doc["spec"]["templates"].push_back(getAppTemplate(app_template_name, docker_image, app_command, app_args));

            YAML::Emitter out;
            out << doc;
            yaml_list.emplace_back(out.c_str());

        }


    }


    void example() {
        YAML::Emitter out;


        YAML::Node stage_in_template;
        stage_in_template["name"] = "test";
        stage_in_template["container"]["image"] = "test";
        stage_in_template["container"]["command"][0] = "test";
        stage_in_template["container"]["command"].SetStyle(YAML::EmitterStyle::Flow);
        std::vector<std::string> stage_in_template_args;
        stage_in_template_args.push_back("Hello World");
        stage_in_template["container"]["args"] = stage_in_template_args;
        stage_in_template["container"]["args"].SetStyle(YAML::EmitterStyle::Flow);
        stage_in_template["resources"]["limits"]["memory"] = "32Mi";
        stage_in_template["resources"]["limits"]["cpu"] = "100m";


        out << YAML::BeginMap;
        out << YAML::Key << "apiVersion";
        out << YAML::Value << "argoproj.io/v1alpha1";

        out << YAML::Key << "kind";
        out << YAML::Value << "workflow";

        out << YAML::Key << "metadata";
        out << YAML::BeginMap;
        out << YAML::Key << "generateName";
        out << YAML::Value << "hello-world";
        out << YAML::EndMap;

        out << YAML::Key << "spec";
        out << YAML::BeginMap;
        out << YAML::Key << "entrypoint";
        out << YAML::Value << "whalesay";


        out << YAML::Key << "templates";
        out << YAML::Value << YAML::BeginSeq;
        out << YAML::BeginMap;
        out << YAML::Key << "name";
        out << YAML::Value << "whalesay";

        out << YAML::Key << "container";
        out << YAML::BeginMap;
        out << YAML::Key << "image";
        out << YAML::Value << "docker/whalesay";

        out << YAML::Key << "command";
        out << YAML::Value << "[cowsay]";

        out << YAML::Key << "args";
        out << YAML::Value << "[hello world]";

        out << YAML::Key << "resources";
        out << YAML::BeginMap;
        out << YAML::Key << "limits";

        out << YAML::BeginMap;
        out << YAML::Key << "memory";
        out << YAML::Value << "32Mi";
        out << YAML::Key << "cpu";
        out << YAML::Value << "100m";
        out << YAML::EndMap;
        out << YAML::EndMap;

        out << YAML::EndMap;
        out << YAML::EndMap;


        out << YAML::EndSeq;


        std::cout << "Here's the output YAML:\n" << out.c_str();

    }
}
