#include <logger/logger.hpp>
#include <terminal/terminal.hpp>
#include <thinlibcxx/cstring.hpp>

void log(String log) {
  term1->out(log);
  term1->out('\n');
}

void log(const char *log) {
  term1->out(log, thinlibcxx::strlen(log, 255));

  term1->out("\n\r");
}
