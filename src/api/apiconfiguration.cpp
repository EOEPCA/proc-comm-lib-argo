//
// Created by bla on 20/04/20.
//

#include <proc-comm-lib-argo/api/apiconfiguration.hpp>

namespace proc_comm_lib_argo {

    /**
     * Constructor
     * @param apiPath
     */
    ApiConfiguration::ApiConfiguration(std::string apiPath) : apiPath(apiPath) {
        apiPath = apiPath;
    }

    /**
     * Destructor
     */
    ApiConfiguration::~ApiConfiguration() {}

    /**
     * Returns base url
     * @return
     */
    const std::string &ApiConfiguration::getBaseUrl() const {
        return baseUrl;
    }

    /**
     * Sets base url
     * @param value
     */
    void ApiConfiguration::setBaseUrl(const std::string &value) {
        baseUrl = value;
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

    /**
     * Returns api path
     * @return
     */
    const std::string &ApiConfiguration::getApiPath() const {
        return apiPath;
    }

    /**
     * Sets api path
     * @param apiVersionPath
     */
    void ApiConfiguration::setApiPath(const std::string &apiVersionPath) {
        ApiConfiguration::apiPath = apiVersionPath;
    }

}

