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

    class KubernetesVolumeClaim {
        std::string volumeName = "";
        std::vector<std::string> accessModes = {"ReadWriteOnce"};
        std::string volumeSize = "1Gi";
        std::string volumeMountPath = "/mnt/vol";
    public:
        KubernetesVolumeClaim() = default;
        ~KubernetesVolumeClaim() = default;

        const std::string &getVolumeName() const {
            return volumeName;
        }
        void setVolumeName(const std::string &volumeName) {
            KubernetesVolumeClaim::volumeName = volumeName;
        }
        const std::string &getVolumeSize() const {
            return volumeSize;
        }
        void setVolumeSize(const std::string &volumeSize) {
            KubernetesVolumeClaim::volumeSize = volumeSize;
        }

        const std::vector<std::string> &getAccessModes() const {
            return accessModes;
        }
        void setAccessModes(const std::vector<std::string> &accessModes) {
            KubernetesVolumeClaim::accessModes = accessModes;
        }

        const std::string &getVolumeMountPath() const {
            return volumeMountPath;
        }
        void setVolumeMountPath(const std::string &volumeMountPath) {
            KubernetesVolumeClaim::volumeMountPath = volumeMountPath;
        }
    };

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
        std::map<std::string, std::pair<std::string, std::string>> secrerEnvVars{};
        bool useShell = true; // by default set to true, if false the script will be considered
        bool includeTee = false;

    public:
        NodeTemplate() = default;
        NodeTemplate(const NodeTemplate &) = delete;
        NodeTemplate(NodeTemplate &&) = delete;
        ~NodeTemplate() = default;

        // from script
        struct script {
            std::string command;
            std::string source;
        } script;

        struct limits {
            std::string memory = "32Mi";
            std::string cpu = "100m";
        } limits;

        // command
        const std::string &getCommand() const { return command; }
        void setCommand(const std::string &stageinApplication) { command = stageinApplication; }

        // command docker image
        const std::string &getDockerImage() const { return dockerImage; }
        void setDockerImage(const std::string &img) { dockerImage = img; }

        // command params
        void addParam(std::string key, std::string value) { params.insert(std::make_pair(key, value)); }
        const std::map<std::string, std::string> getParams() const { return params; }

        // use shell boolean
        bool isUseShell() const { return useShell; }
        void setUseShell(bool useShell) { NodeTemplate::useShell = useShell; }

        // environment variables
        const std::map<std::string, std::string> &getEnvVars() const { return envVars; }
        void setEnvVars(const std::map<std::string, std::string> &envVars) { NodeTemplate::envVars = envVars; }

        bool isIncludeTee() const { return includeTee; }
        void setIncludeTee(bool includeTee) { NodeTemplate::includeTee = includeTee; }

        const std::map<std::string, std::pair<std::string, std::string>> &getSecrerEnvVars() const { return secrerEnvVars; }
        void setSecrerEnvVars(const std::map<std::string, std::pair<std::string, std::string>> &secrerEnvVars) { NodeTemplate::secrerEnvVars = secrerEnvVars; }
    };

    /**
     * Application Class
     * represents the main command. Can contain a stage in node.
     */
    class Application : public NodeTemplate {

    private:
        std::unique_ptr<NodeTemplate> preProcessingNode;
        std::unique_ptr<NodeTemplate> postProcessingNode;
        std::string uuidBaseID;
        std::string runId;
        std::string resultId = "results";
        KubernetesVolumeClaim kubernetesVolumeClaim;

    public:
        Application() {

            // default stageout is a cat of the application's result
            std::unique_ptr<proc_comm_lib_argo::NodeTemplate> stageOutApplication = std::make_unique<proc_comm_lib_argo::NodeTemplate>();
            stageOutApplication->setDockerImage("blasco/eoepca-eo-tools");
            stageOutApplication->setUseShell(true);
            stageOutApplication->setCommand("echo");
            setPostProcessingNode(stageOutApplication);
        }
        Application(const Application &) = delete;
        Application(Application &&) = delete;
        ~Application() = default;

        // stage-in node
        const std::unique_ptr<NodeTemplate> &getPreProcessingNode() const { return preProcessingNode; }
        void setPreProcessingNode(std::unique_ptr<NodeTemplate> &_preProcessingNode) { preProcessingNode = std::move(_preProcessingNode); }

        // stage-out node
        const std::unique_ptr<NodeTemplate> &getPostProcessingNode() const { return postProcessingNode; }
        void setPostProcessingNode(std::unique_ptr<NodeTemplate> &_postProcessingNode) { postProcessingNode = std::move(_postProcessingNode); }

        const std::string &getUuidBaseId() const { return uuidBaseID; }
        void setUuidBaseId(const std::string &uuidBaseId) { uuidBaseID = uuidBaseId; }

        const std::string &getRunId() const { return runId; }
        void setRunId(const std::string &runId) { Application::runId = runId; }

        const std::string &getResultId() const { return resultId; }
        void setResultId(const std::string &resultId) { Application::resultId = resultId; }

        const KubernetesVolumeClaim &getKubernetesVolumeClaim() const { return kubernetesVolumeClaim; }
        void setKubernetesVolumeClaim(const KubernetesVolumeClaim &kubernetesVolumeClaim) { Application::kubernetesVolumeClaim = kubernetesVolumeClaim; }
    };

    class Run {
        std::list<std::unique_ptr<Application>> applications{};
    public:
        Run() {}
        ~Run() {}
        void moveApplication(std::unique_ptr<Application> &theApplication) {
            if (theApplication) {
                applications.emplace_back(std::move(theApplication));
            }
        }
        const std::list<std::unique_ptr<Application>> &getApplications() const {
            return applications;
        }

    };
}  // namespace proc-comm-lib-argo

#endif