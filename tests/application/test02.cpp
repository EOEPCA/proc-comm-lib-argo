//
// Created by bla on 16/04/20.
//


#include <gtest/gtest.h>
#include <string>
#include <httpmockserver/test_environment.h>
#include <httpmockserver/mock_holder.h>
#include <beeblebrox/includes/zaphodhands/zaphodhand.hpp>
#include <beeblebrox/includes/beeblebrox/httpresponsestring.hpp>
#include <beeblebrox/includes/beeblebrox/httpcontentstring.hpp>
#include <eoepca/argo/eoepcaargo.hpp>
#include <eoepca/argo/model/apiexception.hpp>
#include <eoepca/argo/model/apiresponse.hpp>


std::unique_ptr<EOEPCA::EOEPCAargo> getLibArgo2() {
    auto lib = std::make_unique<EOEPCA::EOEPCAargo>("./cmake-build-debug/libeoepcaargo.so");
    if (!lib->IsValid()) {
        lib = std::make_unique<EOEPCA::EOEPCAargo>("/project/build/libeoepcaargo.so");
    }
    if (!lib->IsValid()) {
        std::cout << "Library not found\n";
        EXPECT_TRUE(false);
    }
    return lib;
}

/// Port number server is tried to listen on
/// Number is being incremented while free port has not been found.
static const int server_port = 9200;

/// Server started in the main().
static httpmock::TestEnvironment<httpmock::MockServerHolder> *mock_server_env = nullptr;

/// Return URL server is listening at. E.g.: http://localhost:8080/
static std::string getServerUrl() {
    assert(nullptr != mock_server_env);
    const int port = mock_server_env->getMock()->getPort();
    std::ostringstream url;
    url << "http://localhost:" << port << "/";
    return url.str();
}

/**
 * Http Get
 * @param id
 * @param ret
 * @return
 */
long getHttp(std::string_view id, std::string &ret) {
    ZaphodHands::ZaphodHand hand{};
    std::string path{id};
    Beeblebrox::Uri uri(path.data());
    uri.followUri(true);
    uri << Beeblebrox::Uri::Method::GET;
    Beeblebrox::HttpResponseString response{};
    hand << &uri << &response;
    hand.Run();
    ret.assign(response.getContent());
    return uri.getHttpReturnCode();
}


/**
* Http Delete
* @param url
* @param response_content
* @return
*/
long deleteHttp(std::string_view url, std::string &response_content) {
    ZaphodHands::ZaphodHand hand{};
    std::string path{url};
    Beeblebrox::Uri uri(path.data());
    uri.followUri(true);
    uri << Beeblebrox::Uri::Method::DELETE;
    Beeblebrox::HttpResponseString response{};
    hand << &uri << &response;
    hand.Run();
    response_content.assign(response.getContent());
    return uri.getHttpReturnCode();
}


/**
 * Htpp Post
 * @param path
 * @param configDeployr
 * @param resp
 * @return
 */
long postHttp(std::string_view path, std::string_view configDeployr, std::string &resp) {
    ZaphodHands::ZaphodHand hand{};
    std::string fPath{path};
    Beeblebrox::Uri uri(fPath.data());
    uri.followUri(true);
    uri << Beeblebrox::Uri::Method::POST;
    Beeblebrox::HttpContentString contentString{configDeployr.data()};
    Beeblebrox::HttpResponseString response{};
    hand << &uri << &response << &contentString;
    hand.Run();
    auto retCode = uri.getHttpReturnCode();
    resp.assign(response.getContent());
    return retCode;
}


TEST(TEST2_Argo_rest_api, ListAll) {

    proc_comm_lib_argo::model::WorkflowList workflowList;
    std::string argo_namespace = "default";
    getLibArgo2()->list_workflows(argo_namespace, workflowList, "http://localhost:9200");
    int numberOfWorkflows = workflowList.get_items()->size();
    int expectedNumberOfWorkflows = 90;
    EXPECT_EQ(numberOfWorkflows, expectedNumberOfWorkflows);
}

TEST(TEST2_Argo_rest_api, Get) {

    proc_comm_lib_argo::model::Workflow workflow;
    std::string argo_namespace = "default";
    std::string workflowName= "eoepca-app-qqcnk";
    getLibArgo2()->get_workflow_from_name(workflowName, argo_namespace, workflow, "http://localhost:9200");
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
    getLibArgo2()->submit_workflow(application.get(), argo_namespace, workflow, "http://localhost:9200");
    std::string_view workflow_name = workflow.get_metadata()->get_name()->c_str();
    std::string expected_workflowName= "eoepca-app-vsdcp";

    EXPECT_EQ(workflow_name, expected_workflowName);
}


TEST(TEST2_Argo_rest_api, Delete) {

    proc_comm_lib_argo::model::ApiResponse apiResponse;
    std::string argo_namespace = "default";
    std::string workflowName= "eoepca-app-qqcnk";
    getLibArgo2()->delete_workflow_from_name(workflowName, argo_namespace, apiResponse, "http://localhost:9200");
    std::string_view delete_status = apiResponse.get_status()->c_str();
    std::string_view expected_delete_status ="Success";
    EXPECT_EQ(delete_status, expected_delete_status);
}


