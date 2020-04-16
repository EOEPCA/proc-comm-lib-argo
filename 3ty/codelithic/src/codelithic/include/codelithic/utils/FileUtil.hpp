
#ifndef FILEUTIL_H
#define FILEUTIL_H

#include <stdbool.h>
#include <cstdio>
#include <fstream>
#include <map>
#include <sstream>
#include <vector>

namespace codelithic {

class FileUtil {
 public:
  FileUtil() = default;
  virtual ~FileUtil();

  /***
   * create recorsive path linux
   * @param path
   * @return
   */
  static int mkDir(const std::string &path);

  static int copyTextFile(char *source, char *dest);
  static bool is_file_exist(const char *fileName);
  static bool is_directory_exist(const char *fileName);

  static void writeContent(const char *fileName, const std::string &content);

  static void loadFile(std::string_view filePath, std::string &buffer);

  static int remove(const char *filename);

  static void deserialize(std::istream &in,
                          std::map<std::string, std::string> &map);
  static void deserialize(std::istream &in, std::vector<std::string> &vector);

  static void serialize(std::ostream &out,
                        std::map<std::string, std::string> &map);
  static void serialize(std::ostream &out, std::vector<std::string> &vector);

  //	std::stringbuf strBuffer;
  //	std::ostream os(&strBuffer);
  //	std::istream is(&strBuffer);
  //	is.seekg (0, is.beg);

 private:
};
}  // namespace codelithic
#endif /* FILEUTIL_H */
       // http://www.cplusplus.com/reference/istream/istream/seekg/
       // http://stackoverflow.com/questions/402283/stdwstring-vs-stdstring
       // https://github.com/leethomason/tinyxml2