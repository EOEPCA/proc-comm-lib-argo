//
// Created by bla on 20/04/20.
//

#ifndef PROC_COMM_LIB_ARGO_APICONFIGURATION_HPP
#define PROC_COMM_LIB_ARGO_APICONFIGURATION_HPP


#include <map>


namespace proc_comm_lib_argo {

    static std::string K8_API_PATH="/apis/argoproj.io/v1alpha1";
    static std::string ARGO_API_PATH="/api/v1";

    /**
     * ApiConfiguration class
     * contains all the configurations needed to communicate with Argo and Kubernetes Rest Api
     */
    class ApiConfiguration {
    public:
        // Constructor
        ApiConfiguration(std::string k8ApiPath=ARGO_API_PATH, std::string argoApiPath=K8_API_PATH);

        // Destructor
        virtual ~ApiConfiguration();

        // Argo api base url
        const std::string &getKubernetesApiBaseUrl() const;
        void setKubernetesApiBaseUrl(const std::string &value);

        // Kubernetes api base url
        const std::string &getArgoWorkflowApiBaseUrl() const;
        void setArgoWorkflowApiBaseUrl(const std::string &value);

        // Argo api path
        const std::string &getArgoApiPath() const;
        void setArgoApiPath(const std::string &path);

        // Kubernetes api path
        const std::string &getK8ApiPath() const;
        void setK8ApiPath(const std::string &path);

        // default headers for http calls
        std::map<std::string, std::string> getDefaultHeaders() const;
        void setDefaultHeaders( const std::map<std::string, std::string> value);

    protected:
        std::string kubernetesApiBaseUrl;
        std::string argoWorkflowApiBaseUrl;
        std::string kubernetesApiPath;
        std::string argoWorkflowApiPath;
        std::map<std::string, std::string> defaultHeaders;
    };

}


#endif //PROC_COMM_LIB_ARGO_APICONFIGURATION_HPP
