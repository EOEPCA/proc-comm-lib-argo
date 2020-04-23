//
// Created by bla on 20/04/20.
//

#ifndef PROC_COMM_LIB_ARGO_APIEXCEPTION_HPP
#define PROC_COMM_LIB_ARGO_APIEXCEPTION_HPP

#include <map>
#include <memory>

namespace proc_comm_lib_argo {

    /**
     * ApiException Class
     */
    class ApiException : public std::exception {
    public:

        // Constructors
        ApiException(int errorCode, std::string_view message, std::string_view content = "");

        // Desctructors
        virtual ~ApiException();

        // Get Error Message
        std::string_view getMessage() const;


        // Get Headers
        std::map<std::string, std::string> &getHeaders();

        // Get Response
        std::string_view getContent() const;

        // Get Error code
        int getErrorCode() const;

        virtual const char *what() const throw() {
            return message.data();
        }


    protected:
        int errorCode;
        std::string_view message;
        std::string_view content;
        std::map<std::string, std::string> headers;
    };

}


#endif //PROC_COMM_LIB_ARGO_APIEXCEPTION_HPP
