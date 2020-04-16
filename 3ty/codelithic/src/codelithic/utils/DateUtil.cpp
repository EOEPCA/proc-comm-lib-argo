
#include "codelithic/utils/DateUtil.hpp"

namespace codelithic {

std::string DateUtil::getNow(std::string format) {
  // http://en.cppreference.com/w/cpp/io/manip/put_time
  std::time_t t = std::time(nullptr);
  // std::tm tm = *std::localtime(&t);

  std::ostringstream oss;
  // fixed in gcc5!!!!
  // oss << std::put_time(&tm, format.c_str());

  char mbstr[100];
  if (std::strftime(mbstr, sizeof(mbstr), format.c_str(), std::localtime(&t))) {
    oss << mbstr;
  }
  return oss.str();
}
}