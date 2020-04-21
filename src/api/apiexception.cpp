//
// Created by bla on 20/04/20.
//

#include "proc-comm-lib-argo/api/apiexception.hpp"

namespace proc_comm_lib_argo {

    /**
     * Constructor
     * @param errorCode
     * @param message
     * @param content
     */
    ApiException::ApiException(std::shared_ptr<int> errorCode, std::shared_ptr<std::string> message, std::shared_ptr<std::string> content):
            errorCode(errorCode), message(message), content(content) {
    }

    /**
     * Destructor
     */
    ApiException::~ApiException() { }


    /**
     * Returns error content
     * @return
     */
    std::shared_ptr<std::string> ApiException::getContent() const {
        return content;
    }

    /**
     * Returns Error Message
     * @return
     */
    std::shared_ptr<std::string> ApiException::getMessage() const {
        return message;
    }

    std::shared_ptr<int> ApiException::getErrorCode() const {
        return errorCode;
    }

}