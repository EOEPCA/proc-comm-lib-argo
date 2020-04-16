#ifndef BEEBLEBROX_COMMON_PATH_Path_HPP
#define BEEBLEBROX_COMMON_PATH_Path_HPP

#include <ostream>
#include <string>

#include "httpresponse.hpp"

#include "beeblebrox/Sha1.hpp"
#include "beeblebrox/Uuid.hpp"

namespace Beeblebrox {

class HttpResponseFile : public HttpResponse {
 public:
  HttpResponseFile() = default;
  explicit HttpResponseFile(std::string path) { (*this) = path; }

  int init() override { return 0; }
  int start() override {
    this->mFileStream = fopen(this->mPath.c_str(), "wb");

    return (this->mFileStream ? 0 : 1);
  }
  size_t header_data(void* ptr, size_t size, size_t nmemb) override {
    mHeaders.append((char*)ptr, size * nmemb);

    return size * nmemb;
  }
  size_t write_data(void* ptr, size_t size, size_t nmemb) override {
    return fwrite(ptr, size, nmemb, this->mFileStream);
  }

  void end() override {
    if (this->mFileStream) {
      fflush(this->mFileStream);
      fclose(this->mFileStream);

      this->mFileStream = nullptr;
    }
  }

  const std::string& GetPath() const { return mPath; }

  const std::string& GetSha1Name() const { return mSha1Name; }

  const std::string& GetSha1File() { return mSha1File; }

  const std::string& GetUuid() const { return mUuid; }

  const std::string& getHeaders() const { return mHeaders; }

  HttpResponseFile& operator=(std::string path) noexcept(false) {
    reset();

    mPath = std::move(path);
    mUuid = Uuid::getTimeSafe();
    mSha1Name = sha1::parseString(mPath);

    return *this;
  }

  int parseSha1() {
    if (mSha1File.empty() && !mPath.empty()) {
      Beeblebrox::sha1 s(mPath);

      return s.parseFile(mSha1File);
    }

    return 1;
  }

  ~HttpResponseFile() { end(); }

 private:
  std::string mPath{""};
  std::string mSha1Name{""};
  std::string mSha1File{""};
  std::string mUuid{""};
  FILE* mFileStream{nullptr};
  std::string mHeaders{""};

  void reset() {
    mPath = "";
    mSha1Name = "";
    mSha1File = "";
    mUuid = "";
  }

 public:
  HttpResponseFile(const HttpResponseFile& other) {
    if (mFileStream != nullptr) {
      start();
    }
  }
  HttpResponseFile(HttpResponseFile&& other) noexcept(false) {
    mFileStream = other.mFileStream;
    other.mFileStream = nullptr;
  }
  HttpResponseFile& operator=(const HttpResponseFile& other) {
    if (this == &other) return *this;

    this->mPath = other.mPath;
    this->mSha1Name = other.mSha1Name;
    this->mSha1File = other.mSha1File;
    this->mUuid = other.mUuid;
    this->mHeaders = other.mHeaders;
    if (mFileStream != nullptr) {
      start();
    }

    return *this;
  }
  HttpResponseFile& operator=(HttpResponseFile&& other) noexcept(false) {
    if (this == &other) return *this;

    this->mPath = std::move(other.mPath);
    this->mSha1Name = std::move(other.mSha1Name);
    this->mSha1File = std::move(other.mSha1File);
    this->mUuid = std::move(other.mUuid);
    this->mHeaders = std::move(other.mHeaders);

    mFileStream = other.mFileStream;
    other.mFileStream = nullptr;

    return *this;
  }

  friend std::ostream& operator<<(std::ostream& os,
                                  const HttpResponseFile& type) {
    os << type.mPath << " " << type.mSha1Name << " >" << type.mSha1File << "< "
       << type.mUuid;

    return os;
  }
};

}  // namespace Beeblebrox

#endif  // BEEBLEBROX_COMMON_PATH_Path_HPP
