//
// Created by bla on 16/04/20.
//

#include <gtest/gtest.h>
#include <string>
#include <httpmockserver/mock_holder.h>
#include <eoepca/argo/eoepcaargo.hpp>
#include <eoepca/argo/model/apiresponse.hpp>
#include "testlibargoutils.hpp"

static std::string_view getMockServerUrl() {
    return "http://localhost:9200";
}

TEST(TEST2_Argo_rest_api, ListAll) {

    proc_comm_lib_argo::model::WorkflowList workflowList;
    std::string argo_namespace = "default";
    testing::TestLibArgoUtils::getLibArgo()->list_workflows(argo_namespace, workflowList, getMockServerUrl());
    int numberOfWorkflows = workflowList.get_items()->size();
    int expectedNumberOfWorkflows = 90;
    EXPECT_EQ(numberOfWorkflows, expectedNumberOfWorkflows);
}

TEST(TEST2_Argo_rest_api, Get) {

    proc_comm_lib_argo::model::Workflow workflow;
    std::string argo_namespace = "default";
    std::string workflowName= "eoepca-app-qqcnk";
    testing::TestLibArgoUtils::getLibArgo()->get_workflow_from_name(workflowName, argo_namespace, workflow, getMockServerUrl());
    std::string_view creation_timestamp = workflow.get_metadata()->get_creation_timestamp()->c_str();
    std::string_view expected_creation_timestamp ="2020-04-21T12:53:45Z";
    EXPECT_EQ(creation_timestamp, expected_creation_timestamp);
}


TEST(TEST2_Argo_rest_api, Submit) {

    proc_comm_lib_argo::model::Workflow workflow;
    std::string argo_namespace = "default";

    // sample application
    std::unique_ptr<proc_comm_lib_argo::Application> application = std::make_unique<proc_comm_lib_argo::Application>();
    application->setDockerImage("centos:7");
    application->addParam("message", "Hello World");
    application->setCommand("print(\"{{workflow.parameters.message}}\")");

    // submitting application
    testing::TestLibArgoUtils::getLibArgo()->submit_workflow(application.get(), argo_namespace, workflow, getMockServerUrl());
    std::string_view workflow_name = workflow.get_metadata()->get_name()->c_str();
    std::string expected_workflowName= "eoepca-app-vsdcp";

    EXPECT_EQ(workflow_name, expected_workflowName);
}


TEST(TEST2_Argo_rest_api, Delete) {

    proc_comm_lib_argo::model::ApiResponse apiResponse;
    std::string argo_namespace = "default";
    std::string workflowName= "eoepca-app-qqcnk";
    testing::TestLibArgoUtils::getLibArgo()->delete_workflow_from_name(workflowName, argo_namespace, apiResponse, getMockServerUrl());
    std::string_view delete_status = apiResponse.get_status()->c_str();
    std::string_view expected_delete_status ="Success";
    EXPECT_EQ(delete_status, expected_delete_status);
}


