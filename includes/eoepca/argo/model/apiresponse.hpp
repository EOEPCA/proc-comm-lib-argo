//
// Created by bla on 20/04/20.
//

#ifndef PROC_COMM_LIB_ARGO_APIRESPONSE_HPP
#define PROC_COMM_LIB_ARGO_APIRESPONSE_HPP


//  To parse this JSON data, first install
//
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     ApiResponse data = nlohmann::json::parse(jsonString);

#include <nlohmann/json.hpp>
#include <optional>
#include <stdexcept>
#include <regex>
#include "nlohmann.hpp"

namespace proc_comm_lib_argo::model {
    using nlohmann::json;


    class Details {
    public:
        Details() = default;
        virtual ~Details() = default;

    private:
        std::shared_ptr<std::string> name;
        std::shared_ptr<std::string> group;
        std::shared_ptr<std::string> kind;

    public:
        std::shared_ptr<std::string> get_name() const { return name; }
        void set_name(std::shared_ptr<std::string> value) { this->name = value; }

        std::shared_ptr<std::string> get_group() const { return group; }
        void set_group(std::shared_ptr<std::string> value) { this->group = value; }

        std::shared_ptr<std::string> get_kind() const { return kind; }
        void set_kind(std::shared_ptr<std::string> value) { this->kind = value; }
    };

    class ResponseMetadata {
    public:
        ResponseMetadata() = default;
        virtual ~ResponseMetadata() = default;

    private:

    public:
    };

    class ApiResponse {
    public:
        ApiResponse() = default;
        virtual ~ApiResponse() = default;

    private:
        std::shared_ptr<std::string> kind;
        std::shared_ptr<std::string> api_version;
        std::shared_ptr<ResponseMetadata> metadata;
        std::shared_ptr<std::string> status;
        std::shared_ptr<std::string> message;
        std::shared_ptr<std::string> reason;
        std::shared_ptr<Details> details;
        std::shared_ptr<int> code;

    public:
        std::shared_ptr<std::string> get_kind() const { return kind; }
        void set_kind(std::shared_ptr<std::string> value) { this->kind = value; }

        std::shared_ptr<std::string> get_api_version() const { return api_version; }
        void set_api_version(std::shared_ptr<std::string> value) { this->api_version = value; }

        std::shared_ptr<ResponseMetadata> get_metadata() const { return metadata; }
        void set_metadata(std::shared_ptr<ResponseMetadata> value) { this->metadata = value; }

        std::shared_ptr<std::string> get_status() const { return status; }
        void set_status(std::shared_ptr<std::string> value) { this->status = value; }

        std::shared_ptr<std::string> get_message() const { return message; }
        void set_message(std::shared_ptr<std::string> value) { this->message = value; }

        std::shared_ptr<std::string> get_reason() const { return reason; }
        void set_reason(std::shared_ptr<std::string> value) { this->reason = value; }

        std::shared_ptr<Details> get_details() const { return details; }
        void set_details(std::shared_ptr<Details> value) { this->details = value; }

        std::shared_ptr<int> get_code() const { return code; }
        void set_code(std::shared_ptr<int> value) { this->code = value; }
    };
}


namespace nlohmann {
    void from_json(const json & j, proc_comm_lib_argo::model::Details & x);
    void to_json(json & j, const proc_comm_lib_argo::model::Details & x);

    void from_json(const json & j, proc_comm_lib_argo::model::ResponseMetadata & x);
    void to_json(json & j, const proc_comm_lib_argo::model::ResponseMetadata & x);

    void from_json(const json & j, proc_comm_lib_argo::model::ApiResponse & x);
    void to_json(json & j, const proc_comm_lib_argo::model::ApiResponse & x);

    inline void from_json(const json & j, proc_comm_lib_argo::model::Details& x) {
        x.set_name(proc_comm_lib_argo::model::get_optional<std::string>(j, "name"));
        x.set_group(proc_comm_lib_argo::model::get_optional<std::string>(j, "group"));
        x.set_kind(proc_comm_lib_argo::model::get_optional<std::string>(j, "kind"));
    }

    inline void to_json(json & j, const proc_comm_lib_argo::model::Details & x) {
        j = json::object();
        j["name"] = x.get_name();
        j["group"] = x.get_group();
        j["kind"] = x.get_kind();
    }

    inline void from_json(const json & j, proc_comm_lib_argo::model::ResponseMetadata& x) {
    }

    inline void to_json(json & j, const proc_comm_lib_argo::model::ResponseMetadata & x) {
        j = json::object();
    }

    inline void from_json(const json & j, proc_comm_lib_argo::model::ApiResponse& x) {
        x.set_kind(proc_comm_lib_argo::model::get_optional<std::string>(j, "kind"));
        x.set_api_version(proc_comm_lib_argo::model::get_optional<std::string>(j, "apiVersion"));
        x.set_metadata(proc_comm_lib_argo::model::get_optional<proc_comm_lib_argo::model::ResponseMetadata>(j, "metadata"));
        x.set_status(proc_comm_lib_argo::model::get_optional<std::string>(j, "status"));
        x.set_message(proc_comm_lib_argo::model::get_optional<std::string>(j, "message"));
        x.set_reason(proc_comm_lib_argo::model::get_optional<std::string>(j, "reason"));
        x.set_details(proc_comm_lib_argo::model::get_optional<proc_comm_lib_argo::model::Details>(j, "details"));
        x.set_code(proc_comm_lib_argo::model::get_optional<int>(j, "code"));
    }

    inline void to_json(json & j, const proc_comm_lib_argo::model::ApiResponse & x) {
        j = json::object();
        j["kind"] = x.get_kind();
        j["apiVersion"] = x.get_api_version();
        j["metadata"] = x.get_metadata();
        j["status"] = x.get_status();
        j["message"] = x.get_message();
        j["reason"] = x.get_reason();
        j["details"] = x.get_details();
        j["code"] = x.get_code();
    }
}


#endif //PROC_COMM_LIB_ARGO_APIRESPONSE_HPP
