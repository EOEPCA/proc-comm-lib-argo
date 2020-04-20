//
// Created by bla on 20/04/20.
//

#ifndef PROC_COMM_LIB_ARGO_APICONFIGURATION_HPP
#define PROC_COMM_LIB_ARGO_APICONFIGURATION_HPP


#include <map>


namespace proc_comm_lib_argo {

    static std::string apiPathConstant="/apis/argoproj.io/v1alpha1";
    class ApiConfiguration {
    public:
        ApiConfiguration(std::string apiPath=apiPathConstant);

        virtual ~ApiConfiguration();

        const std::string &getBaseUrl() const;
        void setBaseUrl(const std::string &value);

        std::map<std::string, std::string> getDefaultHeaders() const;
        void setDefaultHeaders( const std::map<std::string, std::string> value);

        const std::string &getApiPath() const;
        void setApiPath(const std::string &apiVersionPath);

    protected:
        std::string baseUrl;
        std::string apiPath;
        std::map<std::string, std::string> defaultHeaders;
    };

}


#endif //PROC_COMM_LIB_ARGO_APICONFIGURATION_HPP
