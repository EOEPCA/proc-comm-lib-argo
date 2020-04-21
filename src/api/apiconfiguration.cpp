//
// Created by bla on 20/04/20.
//

#include <proc-comm-lib-argo/api/apiconfiguration.hpp>

namespace proc_comm_lib_argo {

    /**
     * Constructor
     * @param apiPath
     */
    ApiConfiguration::ApiConfiguration(std::string k8ApiPath, std::string argoApiPath) : k8ApiPath(k8ApiPath), argoApiPath(argoApiPath) {

    }

    /**
     * Destructor
     */
    ApiConfiguration::~ApiConfiguration() {}

    /**
     * Returns Argo Api base url
     * @return
     */
    const std::string &ApiConfiguration::getArgoApiBaseUrl() const {
        return argoApiBaseUrl;
    }

    /**
     * Sets Argo Api base url
     * @param value
     */
    void ApiConfiguration::setArgoApiBaseUrl(const std::string &value) {
        argoApiBaseUrl = value;
    }


    /**
 * Returns K8 Api base url
 * @return
 */
    const std::string &ApiConfiguration::getK8ApiBaseUrl() const {
        return k8ApiBaseUrl;
    }

    /**
     * Sets K8 Api base url
     * @param value
     */
    void ApiConfiguration::setK8ApiBaseUrl(const std::string &value) {
        k8ApiBaseUrl = value;
    }




    /**
     * Returns Argo api path
     * @return
     */
    const std::string &ApiConfiguration::getArgoApiPath() const {
        return argoApiPath;
    }

    /**
     * Sets  Argo api path
     * @param apiVersionPath
     */
    void ApiConfiguration::setArgoApiPath(const std::string &apiVersionPath) {
        argoApiPath = apiVersionPath;
    }

    /**
     * Returns Kubernetes Api Path
     * @return
     */
    void ApiConfiguration::setK8ApiPath(const std::string &path) {
        k8ApiPath=path;
    }

    /**
     * Sets Kubernetes Api Path
     * @return
     */
    const std::string &ApiConfiguration::getK8ApiPath() const {
        return k8ApiPath;
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

