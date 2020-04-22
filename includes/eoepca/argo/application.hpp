//
// Created by bla on 07/04/20.
//

#ifndef PROC_COMM_LIB_ARGO_APPLICATION_HPP
#define PROC_COMM_LIB_ARGO_APPLICATION_HPP

#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <vector>

namespace proc_comm_lib_argo {

    /**
     * NodeTemplate Class
     * this class represents a template in an argo workflow
     */
    class NodeTemplate {

        // cmd from
        std::string dockerImage{""};
        std::string command{""};
        std::map<std::string, std::string> params;
        std::map<std::string, std::string> envVars{};
        bool useShell=true; // by default set to true, if false the script will be considered

    public:
        NodeTemplate() = default;
        NodeTemplate(const NodeTemplate&) = delete;
        NodeTemplate(NodeTemplate&&) = delete;
        ~NodeTemplate() = default;

        // from script
        struct script {
            std::string command;
            std::string source;
        } script;

        struct limits {
            std::string memory="32Mi";
            std::string cpu="100m";
        } limits;

        // command
        const std::string& getCommand() const { return command; }
        void setCommand(const std::string& stageinApplication) { command = stageinApplication; }

        // command docker image
        const std::string& getDockerImage() const { return dockerImage; }
        void setDockerImage(const std::string& img) { dockerImage = img; }

        // command params
        void addParam(std::string key, std::string value) { params.insert(std::make_pair(key, value)); }
        const std::map<std::string, std::string> getParams() const { return params; }


        // use shell boolean
        bool isUseShell() const { return useShell; }
        void setUseShell(bool useShell) { NodeTemplate::useShell = useShell; }

        // environment variables
        const std::map<std::string, std::string> &getEnvVars() const { return envVars;}
        void setEnvVars(const std::map<std::string, std::string> &envVars) { NodeTemplate::envVars = envVars;}

    };

    /**
     * Application Class
     * represents the main command. Can contain a stage in node.
     */
    class Application : public NodeTemplate {
        std::unique_ptr<NodeTemplate> stageInNode;
    public:
        Application() = default;
        Application(const Application&) = delete;
        Application(Application&&) = delete;
        ~Application() = default;

        // stage-in node
        const std::unique_ptr<NodeTemplate>& getStageInNode() const { return stageInNode; }
        void setStageInApplication(std::unique_ptr<NodeTemplate>& stageInApplication_ ){ stageInNode = std::move(stageInApplication_); }

    };


    class Run {
        std::list<std::unique_ptr<Application>> applications{};
    public:
        Run() {}
        ~Run() {}
        void moveApplication(std::unique_ptr<Application>& theApplication) {
            if (theApplication) {
                applications.emplace_back(std::move(theApplication));
            }
        }
        const std::list<std::unique_ptr<Application>>& getApplications() const {
            return applications;
        }

    };
}  // namespace proc-comm-lib-argo

#endif