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
        ApiException(std::shared_ptr<int> errorCode, std::shared_ptr<std::string> message, std::shared_ptr<std::string> content = nullptr);


        // Desctructors
        virtual ~ApiException();

        // Get Error Message
        std::shared_ptr<std::string> getMessage() const;


        // Get Headers
        std::map<std::string, std::string> &getHeaders();

        // Get Response
        std::shared_ptr<std::string> getContent() const;

        // Get Error code
        std::shared_ptr<int> getErrorCode() const;

        virtual const char *what() const throw() {
            return message->c_str();
        }


    protected:
        std::shared_ptr<int> errorCode;
        std::shared_ptr<std::string> message;
        std::shared_ptr<std::string> content;
        std::map<std::string, std::string> headers;
    };

}


#endif //PROC_COMM_LIB_ARGO_APIEXCEPTION_HPP
