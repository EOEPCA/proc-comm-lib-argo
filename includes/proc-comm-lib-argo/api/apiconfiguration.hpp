//
// Created by bla on 20/04/20.
//

#ifndef PROC_COMM_LIB_ARGO_APICONFIGURATION_HPP
#define PROC_COMM_LIB_ARGO_APICONFIGURATION_HPP


#include <map>


namespace proc_comm_lib_argo {

    static std::string ARGO_API_PATH="/apis/argoproj.io/v1alpha1";
    static std::string K8_API_PATH="/api/v1";

    /**
     * ApiConfiguration class
     * contains all the configurations needed to communicate with Argo and Kubernetes Rest Api
     */
    class ApiConfiguration {
    public:
        // Constructor
        ApiConfiguration(std::string k8ApiPath=K8_API_PATH, std::string argoApiPath=ARGO_API_PATH);

        // Destructor
        virtual ~ApiConfiguration();

        // Argo api base url
        const std::string &getArgoApiBaseUrl() const;
        void setArgoApiBaseUrl(const std::string &value);

        // Kubernetes api base url
        const std::string &getK8ApiBaseUrl() const;
        void setK8ApiBaseUrl(const std::string &value);

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
        std::string argoApiBaseUrl;
        std::string k8ApiBaseUrl;
        std::string argoApiPath;
        std::string k8ApiPath;
        std::map<std::string, std::string> defaultHeaders;
    };

}


#endif //PROC_COMM_LIB_ARGO_APICONFIGURATION_HPP
