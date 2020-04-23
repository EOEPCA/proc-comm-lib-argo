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


std::unique_ptr<EOEPCA::EOEPCAargo> getLibArgo2(){
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
    //auto code = getHttp("localhost:9200/apis/argoproj.io/v1alpha1/namespaces/default/workflows/", response);
    //std::cout << "Code: " << code << std::endl << "Content: " << response << std::endl;

    std::cout<<"calling list test";

    proc_comm_lib_argo::model::WorkflowList workflowList;
    std::string argo_namespace = "default";

    getLibArgo2()->list_workflows(argo_namespace, workflowList, "http://localhost:9200" );

/*    std::cout << "Number of workflows: " << workflowList.get_items()->size() << std::endl;
    std::cout << "Api version: " << workflowList.get_api_version()->c_str();
    std::cout << "Namespace: " << workflowList.get_items()->front().get_metadata()->get_metadata_namespace()->c_str() << std::endl;
    std::cout << "Number of workflows: " << workflowList.get_items()->size() << std::endl;
    std::string wfName = workflowList.get_items()->front().get_metadata()->get_name()->c_str();
    std::cout << "Name of first workflow: " << wfName << std::endl;*/

}

/*
TEST(TEST2_Argo_rest_api, Submit) {
    std::string response;
    auto code = postHttp("localhost:9200/apis/argoproj.io/v1alpha1/namespaces/default/workflows/","{\"hello\":\"ok\"}", response);
    std::cout << "Code: " << code << std::endl << "Content: " << response << std::endl;
}

TEST(TEST2_Argo_rest_api, Get) {
    std::string response;
    auto code = getHttp("localhost:9200/apis/argoproj.io/v1alpha1/namespaces/default/workflows/eoepca-app-qqcnk", response);
    std::cout << "Code: " << code << std::endl << "Content: " << response << std::endl;
}

TEST(TEST2_Argo_rest_api, Delete) {
    std::string response;
    auto code = deleteHttp("localhost:9200/apis/argoproj.io/v1alpha1/namespaces/default/workflows/eoepca-app-qqcnk", response);
    std::cout << "Code: " << code << std::endl << "Content: " << response << std::endl;
}*/
