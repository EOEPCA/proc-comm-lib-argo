

#include <chrono>
#include <functional>
#include <iostream>
#include <memory>

#include <cgicc/HTTPHeader.h>

#include "codelithic/site/Application.hpp"
#include "codelithic/site/Controller.hpp"
#include "codelithic/site/Templates.hpp"

#include "codelithic/site_ext/PageSite.hpp"
#include "codelithic/site_ext/SiteView.hpp"
#include "codelithic/site_ext/Template.hpp"
#include "codelithic/site_ext/TemplateLoader.hpp"

#include "codelithic/delegate/Delegate.hpp"
#include "codelithic/delegate/MultiCastDelegate.hpp"

namespace PAGE {

class Dashboard : public codelithic::site::ext::SitePage {
 public:
  Dashboard() = default;

  bool parr(const std::string& path, const std::string& routPath) {
    std::string prefix("/dashboard");
    return path.compare(0, prefix.size(), prefix) == 0;
  }

  void prepareRoutePage() override {
    if (indexRoute == nullptr) {
      //***************************************************************************************************
      // Route indexRoute
      //***************************************************************************************************
      indexRoute = new codelithic::site::Route();
      indexRoute->shouldBeLogged = false;
      indexRoute->redirectTo = "/login";
      //---------------------------------------------------------------------------
      // use lambda or function
      //---------------------------------------------------------------------------
      // indexRoute->dRoute=codelithic::delegate
      // _CODELITHIC_DELEGATE_ROUTE::create<Dashboard, &Dashboard::parr>(this);
      indexRoute->dRoute = [](const std::string& path,
                              const std::string& routPath) -> bool {
        // std::unique_ptr<std::FILE, decltype(&std::fclose)>
        // fp(std::fopen("/tmp/demo.txt", "wb"),&std::fclose);
        // std::fwrite("s\n",1,2,fp.get());
        // std::fprintf(fp.get(),"%d",path.compare(0, prefix.size(), prefix));

        std::string prefix("/dashboard");
        return path.compare(0, prefix.size(), prefix) == 0;
      };
      //---------------------------------------------------------------------------
      indexRoute->dContent = codelithic::delegate
          CODELITHIC_DELEGATE_CONTENT::create<Dashboard, &Dashboard::index>(
              this);
      addRoute(indexRoute);
      //***************************************************************************************************

      //***************************************************************************************************
      // Route indexRoute2
      //***************************************************************************************************
      indexRoute2 = new codelithic::site::Route();
      indexRoute2->shouldBeLogged = false;
      indexRoute2->redirectTo = "/login";
      indexRoute2->dRoute = [](const std::string& path,
                               const std::string& routPath) -> bool {
        std::string prefix("/testlambda");
        return path.compare(0, prefix.size(), prefix) == 0;
      };
      //---------------------------------------------------------------------------
      // use lambda or function
      //---------------------------------------------------------------------------
      // indexRoute2->dContent=codelithic::delegate
      // CODELITHIC_DELEGATE_CONTENT::create<Dashboard,
      // &Dashboard::index>(this);
      indexRoute2->dContent =
          [](std::vector<std::string>* val,
             codelithic::site::PageParameters& params) -> void* {
        auto out = params.getOutput();
        *out << "Content-Type: application/json\n\n";
        *out << "{\"CIAO\":\"pollo\",\"SALE\",12}";
        return nullptr;
      };
      //---------------------------------------------------------------------------
      addRoute(indexRoute2);
      //***************************************************************************************************
    }
  }

  virtual ~Dashboard() {
    delete indexRoute;
    delete indexRoute2;
  }

 private:
  codelithic::site::Route* indexRoute{nullptr};
  codelithic::site::Route* indexRoute2{nullptr};

  void* index(std::vector<std::string>* val,
              codelithic::site::PageParameters& params) {
    //------------------------------------------------------------------------------------------------------------------------
    codelithic::site::ext::TemplateLoader<codelithic::site::ext::SiteView> _tl(
        std::string("main.lsd"));
    _tl.get()->setValue("CIAO", (char*)"NONSO");
    params.renderView(dynamic_cast<codelithic::site::ViewAbstract*>(_tl.get()));
    //------------------------------------------------------------------------------------------------------------------------
    // std::unique_ptr<codelithic::SiteView> D(new
    // codelithic::SiteView("main.lsd")); D->setValue("CIAO",(char*)"POLLame");
    // // params.render(D->getContentHeader());
    // // params.render(static_cast<codelithic::ViewAbstract*>(D.get()));
    // params.renderView(static_cast<codelithic::ViewAbstract*>(D.get()));
    //------------------------------------------------------------------------------------------------------------------------
    // auto out=params.getOutput();
    // *out << "Content-Type: application/json\n\n";
    // *out << "{\"CIAO\":\"pollo\",\"SALE\",12}";
    //------------------------------------------------------------------------------------------------------------------------
    // auto out=params.getOutput();
    // *out << "Content-Type: application/xml\n\n";
    // *out << "<?xml version=\"1.0\"
    // encoding=\"UTF-8\"?><t><a>ciao</a><b>bolla</b></t>";
    //------------------------------------------------------------------------------------------------------------------------

    return nullptr;
  }
};
}  // namespace PAGE

// pkill ./codelithic_test
// cgi-fcgi -start -connect :8000 ./codelithic_test
// pkill ./codelithic_test; sleep 1;cgi-fcgi -start -connect :8000
// ./codelithic_test
int main(int argc, const char** argv, char** envp) {
  codelithic::site::ext::Template themes;
  themes.registerTemplates(
      "/home/emmet/Projects/CREAM/codelithic/src/test/template");
  //    themes.registerTemplates("/Projects/codelithic/src/test/template");
  codelithic::site::Application application;
  codelithic::site::Controller* controller = application.getController();

  //----------------------------------------------REGISTER PAGE
  // TODO: should be use make_unique!!!!
  auto dashboard = std::unique_ptr<PAGE::Dashboard>(new PAGE::Dashboard());
  controller->registerPage(dashboard.get());
  //----------------------------------------------REGISTER PAGE

  //----------------------------------------------REGISTER ROUTE SINGLE
  // TODO: should be use make_unique!!!!
  auto route =
      std::unique_ptr<codelithic::site::Route>(new codelithic::site::Route());
  route->shouldBeLogged = false;
  route->redirectTo = "/login";
  route->dRoute = [](const std::string& path,
                     const std::string& routPath) -> bool {
    std::string prefix("/");
    return path.compare(0, prefix.size(), prefix) == 0;
  };
  route->dContent = [](std::vector<std::string>* val,
                       codelithic::site::PageParameters& params) -> void* {
    auto out = params.getOutput();
    *out << "Content-Type: application/json\n\n";
    *out << "{\"route\":\"SINGLE\"}";
    return nullptr;
  };
  controller->registerRoute(route.get());
  //----------------------------------------------REGISTER ROUTE SINGLE

  try {
    application.starThread(argc, argv, envp);
  } catch (...) {
  }

  return 0;
}
