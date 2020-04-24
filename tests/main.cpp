#include "gtest/gtest.h"
#include <string>
#include <httpmockserver/mock_server.h>
#include <httpmockserver/test_environment.h>
#include <fstream>


class HTTPMock : public httpmock::MockServer {
public:
    /// Create HTTP server on port 9200
    explicit HTTPMock(int port = 9200) : MockServer(port) {}

private:

    std::string getJsonContent(std::string path) {
        std::string json;
        std::ifstream infile(path);
        if (infile.good()) {
            std::stringstream sBuffer;
            sBuffer << infile.rdbuf();
            json = sBuffer.str();
        }
        return json;
    }


    /// Handler called by MockServer on HTTP request.
    Response responseHandler(const std::string &url, const std::string &method, const std::string &data, const std::vector<UrlArg> &urlArguments, const std::vector<Header> &headers) {

        // example get
        if (method == "GET" && matchesPrefix(url, "/example")) {
            // Do something and return response
            return Response(200, "Example: Fake HTTP response");
        }

        // Get workflow
        if (method == "GET" && matchesPrefix(url, "/apis/argoproj.io/v1alpha1/namespaces/default/workflows/eoepca-app-qqcnk")) {
            std::string get_json = getJsonContent("tests/application/data/test2_get_response.json");
            return Response(200, get_json.c_str());
        }

        // List workflows
        if (method == "GET" && matchesPrefix(url, "/apis/argoproj.io/v1alpha1/namespaces/default/workflows")) {
            std::string list_json = getJsonContent("tests/application/data/test2_list_response.json");
            return Response(200, list_json.c_str());
        }

        // Submit workflows
        if (method == "POST" && matchesPrefix(url, "/apis/argoproj.io/v1alpha1/namespaces/default/workflows")) {
            std::string list_json = getJsonContent("tests/application/data/test2_submit_response.json");
            return Response(200, list_json.c_str());
        }


        // Delete workflow
        if (method == "DELETE" && matchesPrefix(url, "/apis/argoproj.io/v1alpha1/namespaces/default/workflows/eoepca-app-qqcnk")) {
            std::string list_json = getJsonContent("tests/application/data/test2_delete_response.json");
            return Response(200, list_json.c_str());
        }


        // Return "URI not found" for the undefined methods
        return Response(404, "Not Found");
    }

    /// Return true if \p url starts with \p str.
    bool matchesPrefix(const std::string &url, const std::string &str) const {
        return url.substr(0, str.size()) == str;
    }
};

/// Server started
static httpmock::TestEnvironment<httpmock::MockServerHolder> *mock_server_env = nullptr;

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    // startup the server for the tests
    ::testing::Environment *const env = ::testing::AddGlobalTestEnvironment(httpmock::createMockServerEnvironment<HTTPMock>(9200));

    // set global env pointer
    mock_server_env = dynamic_cast<httpmock::TestEnvironment<httpmock::MockServerHolder> *>(env);

    return RUN_ALL_TESTS();
}