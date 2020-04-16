
#ifndef LSD_DATEUTIL_H
#define LSD_DATEUTIL_H

#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

// http://stackoverflow.com/questions/16357999/current-date-and-time-as-string

namespace codelithic {

class DateUtil {
 public:
  static std::string getNow(std::string format = "%d-%m-%Y %H-%M-%S");
};
}  // namespace codelithic

#endif  // LSD_DATEUTIL_H
