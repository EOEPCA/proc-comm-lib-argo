//
// Created by Roberto Di Rienzo on 21/12/16.
//

#ifndef CODELITHIC_SLOG_H
#define CODELITHIC_SLOG_H

#include <fstream>
#include <iostream>

#define DLOG 1

#ifdef DLOG

void LogTofile(std::string s) {
  std::ofstream outfile;
  outfile.open("/opt/ellip_sandbox/logs/log.txt", std::ios_base::app);
  outfile << s << std::endl;
  outfile.flush();
  outfile.close();
}

struct None {};

template <typename First, typename Second>
struct Pair {
  First first;
  Second second;
};

template <typename List>
struct LogData {
  List list;
};

template <typename Begin, typename Value>
LogData<Pair<Begin, const Value &>> operator<<(LogData<Begin> begin,
                                               const Value &value) {
  return {{begin.list, value}};
}

template <typename Begin, size_t n>
LogData<Pair<Begin, const char *>> operator<<(LogData<Begin> begin,
                                              const char (&value)[n]) {
  return {{begin.list, value}};
}

// inline void printList(std::ostream &os,None)
//{
//
//}

template <typename Begin, typename Last>
void printList(std::ostream &os, const Pair<Begin, Last> &data) {
  // printList(os,data.first);
  os << data.second;
}

template <typename List>
void log(const char *file, int line, std::string title,
         const LogData<List> &data) {
  if (title.compare("")) {
    std::cerr << file << " (" << line << "):";
  } else {
    std::cerr << file << " (" << line << ")[" << title << "]: ";
  }

  printList(std::cerr, data.list);
  std::cerr << "\n";
}

#define P(x) (std::cerr << "[" << __LINE__ << "]" << x << std::endl)
#define LOGT(title, x) (log(__FILE__, __LINE__, title, LogData<None>() << x))
#define LOG(x) (log(__FILE__, __LINE__, "", LogData<None>() << x))
#else

/*
void log(){
}
 */
#define LOGT(title, x)  //(log( ))
#define LOG(x)          //(log( ))
#endif

#endif  // CODELITHIC_SLOG_H
