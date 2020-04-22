//
// Created by bla on 20/04/20.
//

#include <proc-comm-lib-argo/api/apiexception.hpp>

namespace proc_comm_lib_argo {

    /**
     * Constructor
     * @param errorCode
     * @param message
     * @param content
     */
    ApiException::ApiException(int errorCode, std::string_view message, std::string_view content):
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
    std::string_view ApiException::getContent() const {
        return content;
    }

    /**
     * Returns Error Message
     * @return
     */
    std::string_view ApiException::getMessage() const {
        return message;
    }

    int ApiException::getErrorCode() const {
        return errorCode;
    }

}