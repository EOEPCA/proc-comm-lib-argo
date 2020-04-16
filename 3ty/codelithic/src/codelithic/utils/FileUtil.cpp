

#include "codelithic/utils/FileUtil.hpp"

#include <cstdio>
#include <iostream>

#include <sys/stat.h>
#include <sys/types.h>

namespace codelithic {

/***
 * path, to create a complete directory add "/" at the end.
 * '/path1/path2/path3' -> creates /path1/path2
 * '/path1/path2/path3/' -> creates /path1/path2/path3/
 * @param path
 * @return
 */
int FileUtil::mkDir(const std::string &path) {
  mode_t mode = S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH;

  if (mkdir(path.c_str(), mode) == -1) {
    if (errno == EEXIST) {
      return -2;
    }
  }

  size_t start_pos = 1;
  while ((start_pos = path.find("/", start_pos)) != std::string::npos) {
    auto P = path.substr(0, start_pos);
    start_pos = (start_pos + 1);

    if (mkdir(P.c_str(), mode) == -1) {
      auto Y = errno;

      if (errno != EEXIST) {
        return -1;
      }
    }
  }

  return 0;
}

bool FileUtil::is_directory_exist(const char *directoryName) {
  struct stat info {};

  if (stat(directoryName, &info) != 0) {
    return false;
  } else if (info.st_mode & S_IFDIR)  // S_ISDIR() doesn't exist on my windows
  {
    return true;
  }

  return false;
}

bool FileUtil::is_file_exist(const char *fileName) {
  std::ifstream infile(fileName);
  return infile.good();
}

void FileUtil::loadFile(std::string_view filePath, std::string &buffer) {
  if (FileUtil::is_file_exist(/*(char*)filePath.c_str())*/ filePath.data())) {
    std::ifstream t(filePath.data());
    std::stringstream sBuffer;
    sBuffer << t.rdbuf();

//    buffer.clear();
    buffer.assign(sBuffer.str());
  }
}

int FileUtil::remove(const char *filename) {
  if (!filename) return 0;
  return std::remove(filename);
}

void FileUtil::writeContent(const char *fileName, const std::string &content) {
  std::ofstream file(fileName);
  if (file.good()) {
    file << content;
    file.flush();
    file.close();
  } else {
    std::string err;
    err.append("Impossible to write the file: ");
    err.append(fileName);
    throw std::runtime_error(err);
  }
}

int FileUtil::copyTextFile(char *source, char *dest) {
  std::string line;
  std::ifstream fsource(source);
  std::ofstream fdest(dest);

  if (!fsource) {
    return 1;
  }

  if (!fdest) {
    return 2;
  }

  if (fsource.is_open()) {
    while (getline(fsource, line)) {
      fdest << line << '\n';
    }
  }

  fdest.close();
  fsource.close();

  return 0;
}

void FileUtil::serialize(std::ostream &out,
                         std::map<std::string, std::string> &map) {
  unsigned char S = 15;
  if (out) {
    out << map.size();
    for (auto &m : map) {
      out << S << m.first.size() << S << m.first;
      out << S << m.second.size() << S << m.second;
    }
  }
}

void FileUtil::serialize(std::ostream &out, std::vector<std::string> &vector) {
  unsigned char S = 15;
  if (out) {
    out << vector.size();
    for (auto &m : vector) {
      out << S << m.size() << S << m;
    }
  }
}

void FileUtil::deserialize(std::istream &in, std::vector<std::string> &vector) {
  vector.clear();
  int vectorLen = 0;
  int len = 0;
  char PIPE;
  if (in) {
    std::string key;
    in >> vectorLen;
    for (int i = 0; i < vectorLen; i++) {
      key.clear();
      in >> PIPE >> len >> PIPE;
      if (len) {
        std::vector<char> tmp(len);
        in.read(tmp.data(), len);
        key.assign(tmp.data(), len);
      }
      vector.push_back(key);
    }
  }
}

void FileUtil::deserialize(std::istream &in,
                           std::map<std::string, std::string> &map) {
  map.clear();
  int mappaLen = 0;
  int len = 0;
  char PIPE;
  if (in) {
    in >> mappaLen;
    if (mappaLen > 0) {
      std::string key;
      std::string value;
      for (int i = 0; i < mappaLen; i++) {
        key.clear();
        value.clear();
        in >> PIPE >> len >> PIPE;
        if (len) {
          std::vector<char> tmp(len);
          in.read(tmp.data(), len);
          key.assign(tmp.data(), len);
        }
        in >> PIPE >> len >> PIPE;
        if (len) {
          std::vector<char> tmp(len);
          in.read(tmp.data(), len);
          value.assign(tmp.data(), len);
        }
        map[key] = value;
      }
    }
  }
}

FileUtil::~FileUtil() {}

}