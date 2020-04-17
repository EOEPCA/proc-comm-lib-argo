//
// Created by bla on 16/04/20.
//


#include <gtest/gtest.h>
#include <string>
#include <httpmockserver/test_environment.h>
#include <httpmockserver/mock_holder.h>
#include <beeblebrox/includes/zaphodhands/zaphodhand.hpp>
#include <beeblebrox/includes/beeblebrox/httpresponsestring.hpp>


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


long getHttp(std::string_view id, std::string &ret) {

    ZaphodHands::ZaphodHand hand{};
    std::string path{id};

    Beeblebrox::Uri uri(path.data());
    uri.followUri(true);
    uri << Beeblebrox::Uri::Method::GET; // DEFAULT
    //  uri << Beeblebrox::Uri::Method::POST;
    //  uri << Beeblebrox::Uri::Method::PUT;
    //  uri << Beeblebrox::Uri::Method::DELETE

    Beeblebrox::HttpResponseString response{};
    hand << &uri << &response;
    hand.Run();

    //  response.getHeaders()
    //  response.getContent()


    ret.assign(response.getContent());
    return uri.getHttpReturnCode();
}


TEST(MyTest, dummyTest) {
    // Here should be implementation of test case using HTTP server.
    // HTTP requests are processed by HTTPMock::responseHandler(...)
    // I. e.: when HTTP POST request is sent on localhost:9200/example, then
    // response with status code 500 and body "Fake HTTP response" is returned.


    std::string response;
    auto code = getHttp("localhost:9200/blas", response);
    std::cout<<"Code: "<< code <<std::endl<< "Content: "  <<response<<std::endl;
}



