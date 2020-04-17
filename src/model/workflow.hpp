//
// Created by bla on 07/04/20.
//

#ifndef proc_comm_lib_argo_WORKFLOW_HPP
#define proc_comm_lib_argo_WORKFLOW_HPP


//  To parse this JSON data, first install
//
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     Workflow data = nlohmann::json::parse(jsonString);



#include <optional>
#include <stdexcept>
#include <regex>
#include <nlohmann/json.hpp>
#include <iostream>

namespace nlohmann {
    template<typename T>
    struct adl_serializer<std::shared_ptr<T>> {
        static void to_json(json &j, const std::shared_ptr<T> &opt) {
            if (!opt) j = nullptr; else j = *opt;
        }

        static std::shared_ptr<T> from_json(const json &j) {
            if (j.is_null()) return std::unique_ptr<T>(); else return std::unique_ptr<T>(new T(j.get<T>()));
        }
    };
}


namespace proc_comm_lib_argo::model {
    using nlohmann::json;

    inline json get_untyped(const json &j, const char *property) {
        if (j.find(property) != j.end()) {
            return j.at(property).get<json>();
        }
        return json();
    }

    inline json get_untyped(const json &j, std::string property) {
        return get_untyped(j, property.data());
    }

    template<typename T>
    inline std::shared_ptr<T> get_optional(const json &j, const char *property) {
        if (j.find(property) != j.end()) {
            return j.at(property).get<std::shared_ptr<T>>();
        }
        return std::shared_ptr<T>();
    }

    template<typename T>
    inline std::shared_ptr<T> get_optional(const json &j, std::string property) {
        return get_optional<T>(j, property.data());
    }

    class Labels {
    public:
        Labels() = default;

        virtual ~Labels() = default;

    private:
        std::shared_ptr<std::string> workflows_argoproj_io_completed;
        std::shared_ptr<std::string> workflows_argoproj_io_phase;

    public:
        std::shared_ptr<std::string>
        get_workflows_argoproj_io_completed() const { return workflows_argoproj_io_completed; }

        void set_workflows_argoproj_io_completed(
                std::shared_ptr<std::string> value) { this->workflows_argoproj_io_completed = value; }

        std::shared_ptr<std::string> get_workflows_argoproj_io_phase() const { return workflows_argoproj_io_phase; }

        void set_workflows_argoproj_io_phase(
                std::shared_ptr<std::string> value) { this->workflows_argoproj_io_phase = value; }
    };

    class Metadata {
    public:
        Metadata() = default;

        virtual ~Metadata() = default;

    private:
        std::shared_ptr<std::string> creation_timestamp;
        std::shared_ptr<std::string> generate_name;
        std::shared_ptr<int64_t> generation;
        std::shared_ptr<Labels> labels;
        std::shared_ptr<std::string> name;
        std::shared_ptr<std::string> metadata_namespace;
        std::shared_ptr<std::string> resource_version;
        std::shared_ptr<std::string> self_link;
        std::shared_ptr<std::string> uid;

    public:
        std::shared_ptr<std::string> get_creation_timestamp() const { return creation_timestamp; }

        void set_creation_timestamp(std::shared_ptr<std::string> value) { this->creation_timestamp = value; }

        std::shared_ptr<std::string> get_generate_name() const { return generate_name; }

        void set_generate_name(std::shared_ptr<std::string> value) { this->generate_name = value; }

        std::shared_ptr<int64_t> get_generation() const { return generation; }

        void set_generation(std::shared_ptr<int64_t> value) { this->generation = value; }

        std::shared_ptr<Labels> get_labels() const { return labels; }

        void set_labels(std::shared_ptr<Labels> value) { this->labels = value; }

        std::shared_ptr<std::string> get_name() const { return name; }

        void set_name(std::shared_ptr<std::string> value) { this->name = value; }

        std::shared_ptr<std::string> get_metadata_namespace() const { return metadata_namespace; }

        void set_metadata_namespace(std::shared_ptr<std::string> value) { this->metadata_namespace = value; }

        std::shared_ptr<std::string> get_resource_version() const { return resource_version; }

        void set_resource_version(std::shared_ptr<std::string> value) { this->resource_version = value; }

        std::shared_ptr<std::string> get_self_link() const { return self_link; }

        void set_self_link(std::shared_ptr<std::string> value) { this->self_link = value; }

        std::shared_ptr<std::string> get_uid() const { return uid; }

        void set_uid(std::shared_ptr<std::string> value) { this->uid = value; }
    };

    class Arguments {
    public:
        Arguments() = default;

        virtual ~Arguments() = default;

    private:

    public:
    };

    class Container {
    public:
        Container() = default;

        virtual ~Container() = default;

    private:
        std::shared_ptr<std::vector<std::string>> args;
        std::shared_ptr<std::vector<std::string>> command;
        std::shared_ptr<std::string> image;
        std::shared_ptr<std::string> name;
        std::shared_ptr<Arguments> resources;
        std::shared_ptr<std::string> source;

    public:
        std::shared_ptr<std::vector<std::string>> get_args() const { return args; }

        void set_args(std::shared_ptr<std::vector<std::string>> value) { this->args = value; }

        std::shared_ptr<std::vector<std::string>> get_command() const { return command; }

        void set_command(std::shared_ptr<std::vector<std::string>> value) { this->command = value; }

        std::shared_ptr<std::string> get_image() const { return image; }

        void set_image(std::shared_ptr<std::string> value) { this->image = value; }

        std::shared_ptr<std::string> get_name() const { return name; }

        void set_name(std::shared_ptr<std::string> value) { this->name = value; }

        std::shared_ptr<Arguments> get_resources() const { return resources; }

        void set_resources(std::shared_ptr<Arguments> value) { this->resources = value; }

        std::shared_ptr<std::string> get_source() const { return source; }

        void set_source(std::shared_ptr<std::string> value) { this->source = value; }
    };

    class Step {
    public:
        Step() = default;

        virtual ~Step() = default;

    private:
        std::shared_ptr<Arguments> arguments;
        std::shared_ptr<std::string> name;
        std::shared_ptr<std::string> step_template;
        std::shared_ptr<std::string> when;

    public:
        std::shared_ptr<Arguments> get_arguments() const { return arguments; }

        void set_arguments(std::shared_ptr<Arguments> value) { this->arguments = value; }

        std::shared_ptr<std::string> get_name() const { return name; }

        void set_name(std::shared_ptr<std::string> value) { this->name = value; }

        std::shared_ptr<std::string> get_step_template() const { return step_template; }

        void set_step_template(std::shared_ptr<std::string> value) { this->step_template = value; }

        std::shared_ptr<std::string> get_when() const { return when; }

        void set_when(std::shared_ptr<std::string> value) { this->when = value; }
    };

    class Template {
    public:
        Template() = default;

        virtual ~Template() = default;

    private:
        std::shared_ptr<Arguments> arguments;
        std::shared_ptr<Arguments> inputs;
        std::shared_ptr<Arguments> metadata;
        std::shared_ptr<std::string> name;
        std::shared_ptr<Arguments> outputs;
        std::shared_ptr<std::vector<std::vector<Step>>> steps;
        std::shared_ptr<Container> script;
        std::shared_ptr<Container> container;

    public:
        std::shared_ptr<Arguments> get_arguments() const { return arguments; }

        void set_arguments(std::shared_ptr<Arguments> value) { this->arguments = value; }

        std::shared_ptr<Arguments> get_inputs() const { return inputs; }

        void set_inputs(std::shared_ptr<Arguments> value) { this->inputs = value; }

        std::shared_ptr<Arguments> get_metadata() const { return metadata; }

        void set_metadata(std::shared_ptr<Arguments> value) { this->metadata = value; }

        std::shared_ptr<std::string> get_name() const { return name; }

        void set_name(std::shared_ptr<std::string> value) { this->name = value; }

        std::shared_ptr<Arguments> get_outputs() const { return outputs; }

        void set_outputs(std::shared_ptr<Arguments> value) { this->outputs = value; }

        std::shared_ptr<std::vector<std::vector<Step>>> get_steps() const { return steps; }

        void set_steps(std::shared_ptr<std::vector<std::vector<Step>>> value) { this->steps = value; }

        std::shared_ptr<Container> get_script() const { return script; }

        void set_script(std::shared_ptr<Container> value) { this->script = value; }

        std::shared_ptr<Container> get_container() const { return container; }

        void set_container(std::shared_ptr<Container> value) { this->container = value; }
    };

    class Spec {
    public:
        Spec() = default;

        virtual ~Spec() = default;

    private:
        std::shared_ptr<Arguments> arguments;
        std::shared_ptr<std::string> entrypoint;
        std::shared_ptr<std::vector<Template>> templates;

    public:
        std::shared_ptr<Arguments> get_arguments() const { return arguments; }

        void set_arguments(std::shared_ptr<Arguments> value) { this->arguments = value; }

        std::shared_ptr<std::string> get_entrypoint() const { return entrypoint; }

        void set_entrypoint(std::shared_ptr<std::string> value) { this->entrypoint = value; }

        std::shared_ptr<std::vector<Template>> get_templates() const { return templates; }

        void set_templates(std::shared_ptr<std::vector<Template>> value) { this->templates = value; }
    };

    class Condition {
    public:
        Condition() = default;

        virtual ~Condition() = default;

    private:
        std::shared_ptr<std::string> status;
        std::shared_ptr<std::string> type;

    public:
        std::shared_ptr<std::string> get_status() const { return status; }

        void set_status(std::shared_ptr<std::string> value) { this->status = value; }

        std::shared_ptr<std::string> get_type() const { return type; }

        void set_type(std::shared_ptr<std::string> value) { this->type = value; }
    };

    class Outputs {
    public:
        Outputs() = default;

        virtual ~Outputs() = default;

    private:
        std::shared_ptr<std::string> result;

    public:
        std::shared_ptr<std::string> get_result() const { return result; }

        void set_result(std::shared_ptr<std::string> value) { this->result = value; }
    };

    class Node {
    public:
        Node() = default;

        virtual ~Node() = default;

    private:
        std::shared_ptr<std::vector<std::string>> children;
        std::shared_ptr<std::string> display_name;
        std::shared_ptr<std::string> finished_at;
        std::shared_ptr<std::string> id;
        std::shared_ptr<std::string> name;
        std::shared_ptr<std::vector<std::string>> outbound_nodes;
        std::shared_ptr<std::string> phase;
        std::shared_ptr<std::string> started_at;
        std::shared_ptr<std::string> template_name;
        std::shared_ptr<std::string> type;
        std::shared_ptr<std::string> boundary_id;
        std::shared_ptr<Outputs> outputs;
        std::shared_ptr<std::string> message;

    public:
        std::shared_ptr<std::vector<std::string>> get_children() const { return children; }
        void set_children(std::shared_ptr<std::vector<std::string>> value) { this->children = value; }

        std::shared_ptr<std::string> get_display_name() const { return display_name; }
        void set_display_name(std::shared_ptr<std::string> value) { this->display_name = value; }

        std::shared_ptr<std::string> get_finished_at() const { return finished_at; }
        void set_finished_at(std::shared_ptr<std::string> value) { this->finished_at = value; }

        std::shared_ptr<std::string> get_id() const { return id; }
        void set_id(std::shared_ptr<std::string> value) { this->id = value; }

        std::shared_ptr<std::string> get_name() const { return name; }
        void set_name(std::shared_ptr<std::string> value) { this->name = value; }

        std::shared_ptr<std::vector<std::string>> get_outbound_nodes() const { return outbound_nodes; }
        void set_outbound_nodes(std::shared_ptr<std::vector<std::string>> value) { this->outbound_nodes = value; }

        std::shared_ptr<std::string> get_phase() const { return phase; }
        void set_phase(std::shared_ptr<std::string> value) { this->phase = value; }

        std::shared_ptr<std::string> get_started_at() const { return started_at; }
        void set_started_at(std::shared_ptr<std::string> value) { this->started_at = value; }

        std::shared_ptr<std::string> get_template_name() const { return template_name; }
        void set_template_name(std::shared_ptr<std::string> value) { this->template_name = value; }

        std::shared_ptr<std::string> get_type() const { return type; }
        void set_type(std::shared_ptr<std::string> value) { this->type = value; }

        std::shared_ptr<std::string> get_boundary_id() const { return boundary_id; }
        void set_boundary_id(std::shared_ptr<std::string> value) { this->boundary_id = value; }

        std::shared_ptr<Outputs> get_outputs() const { return outputs; }
        void set_outputs(std::shared_ptr<Outputs> value) { this->outputs = value; }

        std::shared_ptr<std::string> get_message() const { return message; }
        void set_message(std::shared_ptr<std::string> value) { this->message = value; }
    };

    class Status {
    public:
        Status() = default;

        virtual ~Status() = default;

    private:
        std::shared_ptr<std::vector<Condition>> conditions;
        std::shared_ptr<std::string> finished_at;
        std::shared_ptr<std::map<std::string, Node>> nodes;
        std::shared_ptr<std::string> phase;
        std::shared_ptr<std::string> started_at;

    public:
        std::shared_ptr<std::vector<Condition>> get_conditions() const { return conditions; }
        void set_conditions(std::shared_ptr<std::vector<Condition>> value) { this->conditions = value; }

        std::shared_ptr<std::string> get_finished_at() const { return finished_at; }
        void set_finished_at(std::shared_ptr<std::string> value) { this->finished_at = value; }

        std::shared_ptr<std::map<std::string, Node>> get_nodes() const { return nodes; }
        void set_nodes(std::shared_ptr<std::map<std::string, Node>> value) { this->nodes = value; }

        std::shared_ptr<std::string> get_phase() const { return phase; }
        void set_phase(std::shared_ptr<std::string> value) { this->phase = value; }

        std::shared_ptr<std::string> get_started_at() const { return started_at; }
        void set_started_at(std::shared_ptr<std::string> value) { this->started_at = value; }
    };

    class Workflow {
    public:
        Workflow() = default;

        virtual ~Workflow() = default;

    private:
        std::shared_ptr<std::string> api_version;
        std::shared_ptr<std::string> kind;
        std::shared_ptr<Metadata> metadata;
        std::shared_ptr<Spec> spec;
        std::shared_ptr<Status> status;

    public:
        std::shared_ptr<std::string> get_api_version() const { return api_version; }
        void set_api_version(std::shared_ptr<std::string> value) { this->api_version = value; }

        std::shared_ptr<std::string> get_kind() const { return kind; }
        void set_kind(std::shared_ptr<std::string> value) { this->kind = value; }

        std::shared_ptr<Metadata> get_metadata() const { return metadata; }
        void set_metadata(std::shared_ptr<Metadata> value) { this->metadata = value; }

        std::shared_ptr<Spec> get_spec() const { return spec; }
        void set_spec(std::shared_ptr<Spec> value) { this->spec = value; }

        std::shared_ptr<Status> get_status() const { return status; }
        void set_status(std::shared_ptr<Status> value) { this->status = value; }
    };

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

    enum class Phase : int {
        ERROR, FAILED, SKIPPED, SUCCEEDED
    };



    class StatusClass {
    public:
        StatusClass() = default;

        virtual ~StatusClass() = default;

    private:
        std::shared_ptr<std::vector<Condition>> conditions;
        std::shared_ptr<std::string> finished_at;
        std::shared_ptr<std::map<std::string, Node>> nodes;
        std::shared_ptr<Phase> phase;
        std::shared_ptr<std::string> started_at;
        std::shared_ptr<std::string> message;

    public:
        std::shared_ptr<std::vector<Condition>> get_conditions() const { return conditions; }
        void set_conditions(std::shared_ptr<std::vector<Condition>> value) { this->conditions = value; }

        std::shared_ptr<std::string> get_finished_at() const { return finished_at; }
        void set_finished_at(std::shared_ptr<std::string> value) { this->finished_at = value; }

        std::shared_ptr<std::map<std::string, Node>> get_nodes() const { return nodes; }
        void set_nodes(std::shared_ptr<std::map<std::string, Node>> value) { this->nodes = value; }

        std::shared_ptr<Phase> get_phase() const { return phase; }
        void set_phase(std::shared_ptr<Phase> value) { this->phase = value; }

        std::shared_ptr<std::string> get_started_at() const { return started_at; }
        void set_started_at(std::shared_ptr<std::string> value) { this->started_at = value; }

        std::shared_ptr<std::string> get_message() const { return message; }
        void set_message(std::shared_ptr<std::string> value) { this->message = value; }
    };

    class Item {
    public:
        Item() = default;

        virtual ~Item() = default;

    private:
        std::shared_ptr<std::string> api_version;
        std::shared_ptr<std::string> kind;
        std::shared_ptr<Metadata> metadata;
        std::shared_ptr<Spec> spec;
        std::shared_ptr<StatusClass> status;

    public:
        std::shared_ptr<std::string> get_api_version() const { return api_version; }
        void set_api_version(std::shared_ptr<std::string> value) { this->api_version = value; }

        std::shared_ptr<std::string> get_kind() const { return kind; }
        void set_kind(std::shared_ptr<std::string> value) { this->kind = value; }

        std::shared_ptr<Metadata> get_metadata() const { return metadata; }
        void set_metadata(std::shared_ptr<Metadata> value) { this->metadata = value; }

        std::shared_ptr<Spec> get_spec() const { return spec; }
        void set_spec(std::shared_ptr<Spec> value) { this->spec = value; }

        std::shared_ptr<StatusClass> get_status() const { return status; }
        void set_status(std::shared_ptr<StatusClass> value) { this->status = value; }
    };


    class WorkflowList {
    public:
        WorkflowList() = default;

        virtual ~WorkflowList() = default;

    private:
        std::shared_ptr<std::string> api_version;
        std::shared_ptr<std::vector<Item>> items;
        std::shared_ptr<std::string> kind;
        std::shared_ptr<Metadata> metadata;

    public:
        std::shared_ptr<std::string> get_api_version() const { return api_version; }
        void set_api_version(std::shared_ptr<std::string> value) { this->api_version = value; }

        std::shared_ptr<std::vector<Item>> get_items() const { return items; }
        void set_items(std::shared_ptr<std::vector<Item>> value) { this->items = value; }

        std::shared_ptr<std::string> get_kind() const { return kind; }
        void set_kind(std::shared_ptr<std::string> value) { this->kind = value; }

        std::shared_ptr<Metadata> get_metadata() const { return metadata; }
        void set_metadata(std::shared_ptr<Metadata> value) { this->metadata = value; }
    };

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

}


namespace nlohmann {

    void from_json(const json &j, proc_comm_lib_argo::model::Labels &x);
    void to_json(json &j, const proc_comm_lib_argo::model::Labels &x);

    void from_json(const json &j, proc_comm_lib_argo::model::Metadata &x);
    void to_json(json &j, const proc_comm_lib_argo::model::Metadata &x);

    void from_json(const json &j, proc_comm_lib_argo::model::Arguments &x);
    void to_json(json &j, const proc_comm_lib_argo::model::Arguments &x);

    void from_json(const json &j, proc_comm_lib_argo::model::Container &x);
    void to_json(json &j, const proc_comm_lib_argo::model::Container &x);

    void from_json(const json &j, proc_comm_lib_argo::model::Step &x);
    void to_json(json &j, const proc_comm_lib_argo::model::Step &x);

    void from_json(const json &j, proc_comm_lib_argo::model::Template &x);
    void to_json(json &j, const proc_comm_lib_argo::model::Template &x);

    void from_json(const json &j, proc_comm_lib_argo::model::Spec &x);
    void to_json(json &j, const proc_comm_lib_argo::model::Spec &x);

    void from_json(const json &j, proc_comm_lib_argo::model::Condition &x);
    void to_json(json &j, const proc_comm_lib_argo::model::Condition &x);

    void from_json(const json &j, proc_comm_lib_argo::model::Outputs &x);
    void to_json(json &j, const proc_comm_lib_argo::model::Outputs &x);

    void from_json(const json &j, proc_comm_lib_argo::model::Node &x);
    void to_json(json &j, const proc_comm_lib_argo::model::Node &x);

    void from_json(const json &j, proc_comm_lib_argo::model::Status &x);
    void to_json(json &j, const proc_comm_lib_argo::model::Status &x);

    void from_json(const json &j, proc_comm_lib_argo::model::Workflow &x);
    void to_json(json &j, const proc_comm_lib_argo::model::Workflow &x);

    void from_json(const json &j, proc_comm_lib_argo::model::Item &x);
    void to_json(json &j, const proc_comm_lib_argo::model::Item &x);

    void from_json(const json &j, proc_comm_lib_argo::model::WorkflowList &x);
    void to_json(json &j, const proc_comm_lib_argo::model::WorkflowList &x);

    void from_json(const json &j, proc_comm_lib_argo::model::Item &x);
    void to_json(json &j, const proc_comm_lib_argo::model::Item &x);

    void from_json(const json &j, proc_comm_lib_argo::model::StatusClass &x);
    void to_json(json &j, const proc_comm_lib_argo::model::StatusClass &x);

    void from_json(const json & j, proc_comm_lib_argo::model::Phase & x);
    void to_json(json & j, const proc_comm_lib_argo::model::Phase & x);


    inline void from_json(const json &j, proc_comm_lib_argo::model::Labels &x) {
        x.set_workflows_argoproj_io_completed(
                proc_comm_lib_argo::model::get_optional<std::string>(j, "workflows.argoproj.io/completed"));
        x.set_workflows_argoproj_io_phase(
                proc_comm_lib_argo::model::get_optional<std::string>(j, "workflows.argoproj.io/phase"));
    }

    inline void to_json(json &j, const proc_comm_lib_argo::model::Labels &x) {
        j = json::object();
        j["workflows.argoproj.io/completed"] = x.get_workflows_argoproj_io_completed();
        j["workflows.argoproj.io/phase"] = x.get_workflows_argoproj_io_phase();
    }

    inline void from_json(const json &j, proc_comm_lib_argo::model::Metadata &x) {
        x.set_creation_timestamp(proc_comm_lib_argo::model::get_optional<std::string>(j, "creationTimestamp"));
        x.set_generate_name(proc_comm_lib_argo::model::get_optional<std::string>(j, "generateName"));
        x.set_generation(proc_comm_lib_argo::model::get_optional<int64_t>(j, "generation"));
        x.set_labels(proc_comm_lib_argo::model::get_optional<proc_comm_lib_argo::model::Labels>(j, "labels"));
        x.set_name(proc_comm_lib_argo::model::get_optional<std::string>(j, "name"));
        x.set_metadata_namespace(proc_comm_lib_argo::model::get_optional<std::string>(j, "namespace"));
        x.set_resource_version(proc_comm_lib_argo::model::get_optional<std::string>(j, "resourceVersion"));
        x.set_self_link(proc_comm_lib_argo::model::get_optional<std::string>(j, "selfLink"));
        x.set_uid(proc_comm_lib_argo::model::get_optional<std::string>(j, "uid"));
    }

    inline void to_json(json &j, const proc_comm_lib_argo::model::Metadata &x) {
        j = json::object();
        j["creationTimestamp"] = x.get_creation_timestamp();
        j["generateName"] = x.get_generate_name();
        j["generation"] = x.get_generation();
        j["labels"] = x.get_labels();
        j["name"] = x.get_name();
        j["namespace"] = x.get_metadata_namespace();
        j["resourceVersion"] = x.get_resource_version();
        j["selfLink"] = x.get_self_link();
        j["uid"] = x.get_uid();
    }

    inline void from_json(const json &j, proc_comm_lib_argo::model::Arguments &x) {
    }

    inline void to_json(json &j, const proc_comm_lib_argo::model::Arguments &x) {
        j = json::object();
    }

    inline void from_json(const json &j, proc_comm_lib_argo::model::Container &x) {
        x.set_args(proc_comm_lib_argo::model::get_optional<std::vector<std::string>>(j, "args"));
        x.set_command(proc_comm_lib_argo::model::get_optional<std::vector<std::string>>(j, "command"));
        x.set_image(proc_comm_lib_argo::model::get_optional<std::string>(j, "image"));
        x.set_name(proc_comm_lib_argo::model::get_optional<std::string>(j, "name"));
        x.set_resources(proc_comm_lib_argo::model::get_optional<proc_comm_lib_argo::model::Arguments>(j, "resources"));
        x.set_source(proc_comm_lib_argo::model::get_optional<std::string>(j, "source"));
    }

    inline void to_json(json &j, const proc_comm_lib_argo::model::Container &x) {
        j = json::object();
        j["args"] = x.get_args();
        j["command"] = x.get_command();
        j["image"] = x.get_image();
        j["name"] = x.get_name();
        j["resources"] = x.get_resources();
        j["source"] = x.get_source();
    }

    inline void from_json(const json &j, proc_comm_lib_argo::model::Step &x) {
        x.set_arguments(proc_comm_lib_argo::model::get_optional<proc_comm_lib_argo::model::Arguments>(j, "arguments"));
        x.set_name(proc_comm_lib_argo::model::get_optional<std::string>(j, "name"));
        x.set_step_template(proc_comm_lib_argo::model::get_optional<std::string>(j, "template"));
        x.set_when(proc_comm_lib_argo::model::get_optional<std::string>(j, "when"));
    }

    inline void to_json(json &j, const proc_comm_lib_argo::model::Step &x) {
        j = json::object();
        j["arguments"] = x.get_arguments();
        j["name"] = x.get_name();
        j["template"] = x.get_step_template();
        j["when"] = x.get_when();
    }

    inline void from_json(const json &j, proc_comm_lib_argo::model::Template &x) {
        x.set_arguments(proc_comm_lib_argo::model::get_optional<proc_comm_lib_argo::model::Arguments>(j, "arguments"));
        x.set_inputs(proc_comm_lib_argo::model::get_optional<proc_comm_lib_argo::model::Arguments>(j, "inputs"));
        x.set_metadata(proc_comm_lib_argo::model::get_optional<proc_comm_lib_argo::model::Arguments>(j, "metadata"));
        x.set_name(proc_comm_lib_argo::model::get_optional<std::string>(j, "name"));
        x.set_outputs(proc_comm_lib_argo::model::get_optional<proc_comm_lib_argo::model::Arguments>(j, "outputs"));
        x.set_steps(proc_comm_lib_argo::model::get_optional<std::vector<std::vector<proc_comm_lib_argo::model::Step>>>(j,"steps"));
        x.set_script(proc_comm_lib_argo::model::get_optional<proc_comm_lib_argo::model::Container>(j, "script"));
        x.set_container(proc_comm_lib_argo::model::get_optional<proc_comm_lib_argo::model::Container>(j, "container"));
    }

    inline void to_json(json &j, const proc_comm_lib_argo::model::Template &x) {
        j = json::object();
        j["arguments"] = x.get_arguments();
        j["inputs"] = x.get_inputs();
        j["metadata"] = x.get_metadata();
        j["name"] = x.get_name();
        j["outputs"] = x.get_outputs();
        j["steps"] = x.get_steps();
        j["script"] = x.get_script();
        j["container"] = x.get_container();
    }

    inline void from_json(const json &j, proc_comm_lib_argo::model::Spec &x) {
        x.set_arguments(proc_comm_lib_argo::model::get_optional<proc_comm_lib_argo::model::Arguments>(j, "arguments"));
        x.set_entrypoint(proc_comm_lib_argo::model::get_optional<std::string>(j, "entrypoint"));
        x.set_templates(proc_comm_lib_argo::model::get_optional<std::vector<proc_comm_lib_argo::model::Template>>(j,"templates"));
    }

    inline void to_json(json &j, const proc_comm_lib_argo::model::Spec &x) {
        j = json::object();
        j["arguments"] = x.get_arguments();
        j["entrypoint"] = x.get_entrypoint();
        j["templates"] = x.get_templates();
    }

    inline void from_json(const json &j, proc_comm_lib_argo::model::Condition &x) {
        x.set_status(proc_comm_lib_argo::model::get_optional<std::string>(j, "status"));
        x.set_type(proc_comm_lib_argo::model::get_optional<std::string>(j, "type"));
    }

    inline void to_json(json &j, const proc_comm_lib_argo::model::Condition &x) {
        j = json::object();
        j["status"] = x.get_status();
        j["type"] = x.get_type();
    }

    inline void from_json(const json &j, proc_comm_lib_argo::model::Outputs &x) {
        x.set_result(proc_comm_lib_argo::model::get_optional<std::string>(j, "result"));
    }

    inline void to_json(json &j, const proc_comm_lib_argo::model::Outputs &x) {
        j = json::object();
        j["result"] = x.get_result();
    }

    inline void from_json(const json &j, proc_comm_lib_argo::model::Node &x) {
        x.set_children(proc_comm_lib_argo::model::get_optional<std::vector<std::string>>(j, "children"));
        x.set_display_name(proc_comm_lib_argo::model::get_optional<std::string>(j, "displayName"));
        x.set_finished_at(proc_comm_lib_argo::model::get_optional<std::string>(j, "finishedAt"));
        x.set_id(proc_comm_lib_argo::model::get_optional<std::string>(j, "id"));
        x.set_name(proc_comm_lib_argo::model::get_optional<std::string>(j, "name"));
        x.set_outbound_nodes(proc_comm_lib_argo::model::get_optional<std::vector<std::string>>(j, "outboundNodes"));
        x.set_phase(proc_comm_lib_argo::model::get_optional<std::string>(j, "phase"));
        x.set_started_at(proc_comm_lib_argo::model::get_optional<std::string>(j, "startedAt"));
        x.set_template_name(proc_comm_lib_argo::model::get_optional<std::string>(j, "templateName"));
        x.set_type(proc_comm_lib_argo::model::get_optional<std::string>(j, "type"));
        x.set_boundary_id(proc_comm_lib_argo::model::get_optional<std::string>(j, "boundaryID"));
        x.set_outputs(proc_comm_lib_argo::model::get_optional<proc_comm_lib_argo::model::Outputs>(j, "outputs"));
        x.set_message(proc_comm_lib_argo::model::get_optional<std::string>(j, "message"));
    }

    inline void to_json(json &j, const proc_comm_lib_argo::model::Node &x) {
        j = json::object();
        j["children"] = x.get_children();
        j["displayName"] = x.get_display_name();
        j["finishedAt"] = x.get_finished_at();
        j["id"] = x.get_id();
        j["name"] = x.get_name();
        j["outboundNodes"] = x.get_outbound_nodes();
        j["phase"] = x.get_phase();
        j["startedAt"] = x.get_started_at();
        j["templateName"] = x.get_template_name();
        j["type"] = x.get_type();
        j["boundaryID"] = x.get_boundary_id();
        j["outputs"] = x.get_outputs();
        j["message"] = x.get_message();
    }

    inline void from_json(const json &j, proc_comm_lib_argo::model::Status &x) {
        x.set_conditions(proc_comm_lib_argo::model::get_optional<std::vector<proc_comm_lib_argo::model::Condition>>(j,"conditions"));
        x.set_finished_at(proc_comm_lib_argo::model::get_optional<std::string>(j, "finishedAt"));
        x.set_nodes(proc_comm_lib_argo::model::get_optional<std::map<std::string, proc_comm_lib_argo::model::Node>>(j,"nodes"));
        x.set_phase(proc_comm_lib_argo::model::get_optional<std::string>(j, "phase"));
        x.set_started_at(proc_comm_lib_argo::model::get_optional<std::string>(j, "startedAt"));
    }

    inline void to_json(json &j, const proc_comm_lib_argo::model::Status &x) {
        j = json::object();
        j["conditions"] = x.get_conditions();
        j["finishedAt"] = x.get_finished_at();
        j["nodes"] = x.get_nodes();
        j["phase"] = x.get_phase();
        j["startedAt"] = x.get_started_at();
    }

    inline void from_json(const json &j, proc_comm_lib_argo::model::Workflow &x) {
        x.set_api_version(proc_comm_lib_argo::model::get_optional<std::string>(j, "apiVersion"));
        x.set_kind(proc_comm_lib_argo::model::get_optional<std::string>(j, "kind"));
        x.set_metadata(proc_comm_lib_argo::model::get_optional<proc_comm_lib_argo::model::Metadata>(j, "metadata"));
        x.set_spec(proc_comm_lib_argo::model::get_optional<proc_comm_lib_argo::model::Spec>(j, "spec"));
        x.set_status(proc_comm_lib_argo::model::get_optional<proc_comm_lib_argo::model::Status>(j, "status"));
    }

    inline void to_json(json &j, const proc_comm_lib_argo::model::Workflow &x) {
        j = json::object();
        j["apiVersion"] = x.get_api_version();
        j["kind"] = x.get_kind();
        j["metadata"] = x.get_metadata();
        j["spec"] = x.get_spec();
        j["status"] = x.get_status();
    }


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


    inline void from_json(const json & j, proc_comm_lib_argo::model::Phase & x) {
        if (j == "Error") x = proc_comm_lib_argo::model::Phase::ERROR;
        else if (j == "Failed") x = proc_comm_lib_argo::model::Phase::FAILED;
        else if (j == "Skipped") x = proc_comm_lib_argo::model::Phase::SKIPPED;
        else if (j == "Succeeded") x = proc_comm_lib_argo::model::Phase::SUCCEEDED;
        else throw "Input JSON does not conform to schema";
    }

    inline void to_json(json & j, const proc_comm_lib_argo::model::Phase & x) {
        switch (x) {
            case proc_comm_lib_argo::model::Phase::ERROR: j = "Error"; break;
            case proc_comm_lib_argo::model::Phase::FAILED: j = "Failed"; break;
            case proc_comm_lib_argo::model::Phase::SKIPPED: j = "Skipped"; break;
            case proc_comm_lib_argo::model::Phase::SUCCEEDED: j = "Succeeded"; break;
            default: throw "This should not happen";
        }
    }



    inline void from_json(const json &j, proc_comm_lib_argo::model::Item &x) {
        x.set_api_version(
                proc_comm_lib_argo::model::get_optional<std::string>(j, "apiVersion"));
        x.set_kind(proc_comm_lib_argo::model::get_optional<std::string>(j, "kind"));
        x.set_metadata(proc_comm_lib_argo::model::get_optional<proc_comm_lib_argo::model::Metadata>(j, "metadata"));
        x.set_spec(proc_comm_lib_argo::model::get_optional<proc_comm_lib_argo::model::Spec>(j, "spec"));
        x.set_status(proc_comm_lib_argo::model::get_optional<proc_comm_lib_argo::model::StatusClass>(j, "status"));
    }

    inline void to_json(json &j, const proc_comm_lib_argo::model::Item &x) {
        j = json::object();
        j["apiVersion"] = x.get_api_version();
        j["kind"] = x.get_kind();
        j["metadata"] = x.get_metadata();
        j["spec"] = x.get_spec();
        j["status"] = x.get_status();
    }

    inline void from_json(const json &j, proc_comm_lib_argo::model::StatusClass &x) {
        x.set_conditions(proc_comm_lib_argo::model::get_optional<std::vector<proc_comm_lib_argo::model::Condition>>(j,"conditions"));
        x.set_finished_at(proc_comm_lib_argo::model::get_optional<std::string>(j, "finishedAt"));
        x.set_nodes(proc_comm_lib_argo::model::get_optional<std::map<std::string, proc_comm_lib_argo::model::Node>>(j,"nodes"));
        x.set_phase(proc_comm_lib_argo::model::get_optional<proc_comm_lib_argo::model::Phase>(j, "phase"));
        x.set_started_at(proc_comm_lib_argo::model::get_optional<std::string>(j, "startedAt"));
        x.set_message(proc_comm_lib_argo::model::get_optional<std::string>(j, "message"));
    }

    inline void to_json(json &j, const proc_comm_lib_argo::model::StatusClass &x) {
        j = json::object();
        j["conditions"] = x.get_conditions();
        j["finishedAt"] = x.get_finished_at();
        j["nodes"] = x.get_nodes();
        j["phase"] = x.get_phase();
        j["startedAt"] = x.get_started_at();
        j["message"] = x.get_message();
    }


    inline void from_json(const json &j, proc_comm_lib_argo::model::WorkflowList &x) {
        std::cout<<"Api version::::: "<<proc_comm_lib_argo::model::get_optional<std::string>(j, "apiVersion");
        x.set_api_version(proc_comm_lib_argo::model::get_optional<std::string>(j, "apiVersion"));
        x.set_items(proc_comm_lib_argo::model::get_optional<std::vector<proc_comm_lib_argo::model::Item>>(j, "items"));
        x.set_kind(proc_comm_lib_argo::model::get_optional<std::string>(j, "kind"));
        x.set_metadata(proc_comm_lib_argo::model::get_optional<proc_comm_lib_argo::model::Metadata>(j, "metadata"));
    }

    inline void to_json(json &j, const proc_comm_lib_argo::model::WorkflowList &x) {
        j = json::object();
        j["apiVersion"] = x.get_api_version();
        j["items"] = x.get_items();
        j["kind"] = x.get_kind();
        j["metadata"] = x.get_metadata();
    }
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

}


#endif //proc_comm_lib_argo::model_WORKFLOW_HPP
