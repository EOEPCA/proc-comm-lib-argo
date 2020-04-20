//
// Created by bla on 15/04/20.
//

#include <string>
#include <y2j-master/y2j.h>
#include <y2j-master/rapidjson/prettywriter.h>
#include <proc-comm-lib-argo/api/workflowutils.hpp>


namespace proc_comm_lib_argo {

    /**
     * Converts Yaml string to Json string
     * for furter informations check https://github.com/tangrams/y2j
     * @param yaml
     * @return
     */
    std::string Workflow_utils::convertYamlToJson(std::string_view yaml) {

        const char *inputString = yaml.data();
        size_t inputSize = yaml.length();
        const char *errorMessage = nullptr;
        size_t errorLine = 0;

        y2j::JsonDocument document = y2j::yamlParseBytes(inputString, inputSize, &errorMessage, &errorLine);
        rapidjson::StringBuffer buffer;
        rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);
        return buffer.GetString();
    }

    /**
     * Pretty prints Json string
     * @param json
     * @return
     */
    std::string Workflow_utils::prettyPrintJson(std::string_view json) {
        rapidjson::Document document;
        document.Parse(json.data());
        rapidjson::StringBuffer buffer;
        rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);
        return buffer.GetString();
    }


}


