//
// Created by bla on 20/04/20.
//

#include <proc-comm-lib-argo/api/apiconfiguration.hpp>

namespace proc_comm_lib_argo {

    /**
     * Constructor
     * @param apiPath
     */
    ApiConfiguration::ApiConfiguration(std::string argoApiPath, std::string k8ApiPath ) : argoWorkflowApiPath(argoApiPath), kubernetesApiPath(k8ApiPath) {

    }

    /**
     * Destructor
     */
    ApiConfiguration::~ApiConfiguration() {}

    /**
     * Returns Argo Api base url
     * @return
     */
    const std::string &ApiConfiguration::getKubernetesApiBaseUrl() const {
        return kubernetesApiBaseUrl;
    }

    /**
     * Sets Argo Api base url
     * @param value
     */
    void ApiConfiguration::setKubernetesApiBaseUrl(const std::string &value) {
        kubernetesApiBaseUrl = value;
    }


    /**
 * Returns K8 Api base url
 * @return
 */
    const std::string &ApiConfiguration::getArgoWorkflowApiBaseUrl() const {
        return argoWorkflowApiBaseUrl;
    }

    /**
     * Sets K8 Api base url
     * @param value
     */
    void ApiConfiguration::setArgoWorkflowApiBaseUrl(const std::string &value) {
        argoWorkflowApiBaseUrl = value;
    }




    /**
     * Returns Argo api path
     * @return
     */
    const std::string &ApiConfiguration::getArgoApiPath() const {
        return argoWorkflowApiPath;
    }

    /**
     * Sets  Argo api path
     * @param apiVersionPath
     */
    void ApiConfiguration::setArgoApiPath(const std::string &apiVersionPath) {
        argoWorkflowApiPath = apiVersionPath;
    }

    /**
     * Returns Kubernetes Api Path
     * @return
     */
    void ApiConfiguration::setK8ApiPath(const std::string &path) {
        kubernetesApiPath=path;
    }

    /**
     * Sets Kubernetes Api Path
     * @return
     */
    const std::string &ApiConfiguration::getK8ApiPath() const {
        return kubernetesApiPath;
    }

    /**
     * Returns default header
     * @return
     */
    std::map<std::string, std::string> ApiConfiguration::getDefaultHeaders() const {
        return defaultHeaders;
    }

    /**
     * Sets default header
     * @param value
     */
    void ApiConfiguration::setDefaultHeaders(std::map<std::string, std::string> value) {
        defaultHeaders = value;
    }

}

