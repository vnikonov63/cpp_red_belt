#include "test_runner.h"
#include <sstream>
#include <string>
using namespace std;

class Logger {
public:
  explicit Logger(ostream& output_stream) : os(output_stream) {
  }

  void SetLogLine(bool value) { log_line = value; }
  void SetLogFile(bool value) { log_file= value; }
    
    void setFileName(const string& fileNameValue) {
        fileName = fileNameValue;
    }
    
    void setLineNumber(int lineNumberValue) {
        lineNumber = lineNumberValue;
    }

  void Log(const string& message);

private:
  ostream& os;
  bool log_line = false;
  bool log_file = false;
  string fileName = "";
  int lineNumber;
};

void Logger::Log(const string& message) {
    if (log_line && log_file) {
        os << fileName << ":" << lineNumber << " ";
    }
    else if (log_file) {
        os << fileName << " ";
    } else if (log_line) {
        os << "Line " << lineNumber << " ";
    }
    os << message << "\n";
}

#define LOG(logger, message)         \
       logger.setFileName(__FILE__); \
     logger.setLineNumber(__LINE__); \
        logger.Log(message)
         

void TestLog() {
/* Ð”Ð»Ñ Ð½Ð°Ð¿Ð¸ÑÐ°Ð½Ð¸Ñ ÑŽÐ½Ð¸Ñ‚-Ñ‚ÐµÑÑ‚Ð¾Ð² Ð² ÑÑ‚Ð¾Ð¹ Ð·Ð°Ð´Ð°Ñ‡Ðµ Ð½Ð°Ð¼ Ð½ÑƒÐ¶Ð½Ð¾ Ñ„Ð¸ÐºÑÐ¸Ñ€Ð¾Ð²Ð°Ñ‚ÑŒ ÐºÐ¾Ð½ÐºÑ€ÐµÑ‚Ð½Ñ‹Ðµ
 * Ð½Ð¾Ð¼ÐµÑ€Ð° ÑÑ‚Ñ€Ð¾Ðº Ð² Ð¾Ð¶Ð¸Ð´Ð°ÐµÐ¼Ð¾Ð¼ Ð·Ð½Ð°Ñ‡ÐµÐ½Ð¸Ð¸ (ÑÐ¼. Ð¿ÐµÑ€ÐµÐ¼ÐµÐ½Ð½ÑƒÑŽ expected Ð½Ð¸Ð¶Ðµ). Ð•ÑÐ»Ð¸
 * Ð¼Ñ‹ Ð´Ð¾Ð±Ð°Ð²Ð»ÑÐµÐ¼ ÐºÐ°ÐºÐ¾Ð¹-Ñ‚Ð¾ ÐºÐ¾Ð´ Ð²Ñ‹ÑˆÐµ Ñ„ÑƒÐ½ÐºÑ†Ð¸Ð¸ TestLog, Ñ‚Ð¾ ÑÑ‚Ð¸ Ð½Ð¾Ð¼ÐµÑ€Ð° ÑÑ‚Ñ€Ð¾Ðº Ð¼ÐµÐ½ÑÑŽÑ‚ÑÑ,
 * Ð¸ Ð½Ð°Ñˆ Ñ‚ÐµÑÑ‚ Ð½Ð°Ñ‡Ð¸Ð½Ð°ÐµÑ‚ Ð¿Ð°Ð´Ð°Ñ‚ÑŒ. Ð­Ñ‚Ð¾ Ð½ÐµÑƒÐ´Ð¾Ð±Ð½Ð¾.
 *
 * Ð§Ñ‚Ð¾Ð±Ñ‹ ÑÑ‚Ð¾Ð³Ð¾ Ð¸Ð·Ð±ÐµÐ¶Ð°Ñ‚ÑŒ, Ð¼Ñ‹ Ð¸ÑÐ¿Ð¾Ð»ÑŒÐ·ÑƒÐµÐ¼ ÑÐ¿ÐµÑ†Ð¸Ð°Ð»ÑŒÐ½Ñ‹Ð¹ Ð¼Ð°ÐºÑ€Ð¾Ñ #line
 * (http://en.cppreference.com/w/cpp/preprocessor/line), ÐºÐ¾Ñ‚Ð¾Ñ€Ñ‹Ð¹ Ð¿Ð¾Ð·Ð²Ð¾Ð»ÑÐµÑ‚
 * Ð¿ÐµÑ€ÐµÐ¾Ð¿Ñ€ÐµÐ´ÐµÐ»Ð¸Ñ‚ÑŒ Ð½Ð¾Ð¼ÐµÑ€ ÑÑ‚Ñ€Ð¾ÐºÐ¸, Ð° Ñ‚Ð°ÐºÐ¶Ðµ Ð¸Ð¼Ñ Ñ„Ð°Ð¹Ð»Ð°. Ð‘Ð»Ð°Ð³Ð¾Ð´Ð°Ñ€Ñ ÐµÐ¼Ñƒ, Ð½Ð¾Ð¼ÐµÑ€Ð°
 * ÑÑ‚Ñ€Ð¾Ðº Ð²Ð½ÑƒÑ‚Ñ€Ð¸ Ñ„ÑƒÐ½ÐºÑ†Ð¸Ð¸ TestLog Ð±ÑƒÐ´ÑƒÑ‚ Ñ„Ð¸ÐºÑÐ¸Ñ€Ð¾Ð²Ð°Ð½Ñ‹ Ð½ÐµÐ·Ð°Ð²Ð¸ÑÐ¸Ð¼Ð¾ Ð¾Ñ‚ Ñ‚Ð¾Ð³Ð¾, ÐºÐ°ÐºÐ¾Ð¹
 * ÐºÐ¾Ð´ Ð¼Ñ‹ Ð´Ð¾Ð±Ð°Ð²Ð»ÑÐµÐ¼ Ð¿ÐµÑ€ÐµÐ´ Ð½ÐµÐ¹*/
#line 1 "logger.cpp"

  ostringstream logs;
  Logger l(logs);
  LOG(l, "hello");

  l.SetLogFile(true);
  LOG(l, "hello");

  l.SetLogLine(true);
  LOG(l, "hello");

  l.SetLogFile(false);
  LOG(l, "hello");

  string expected = "hello\n";
  expected += "logger.cpp hello\n";
  expected += "logger.cpp:10 hello\n";
  expected += "Line 13 hello\n";
  ASSERT_EQUAL(logs.str(), expected);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestLog);
}
