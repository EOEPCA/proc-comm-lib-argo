
#ifndef SERVICES_H
#define SERVICES_H

namespace codelithic {

namespace site {
//
//    template<class T>
//    class Service {
//    public:
//        bool addInstance(T* i) {
//            if (l_instance != nullptr) {
//                return false;
//            }
//            return l_instance = i;
//        }
//    private:
//        T* l_instance = nullptr;
//    };

class Services {
 public:
  Services();

  virtual ~Services();

 private:
};
}  // namespace site
}  // namespace codelithic
#endif /* SERVICES_H */
