#ifndef TEXTFILELOGGER_H
#define TEXTFILELOGGER_H

#include<fstream>
#include <QtGlobal>
#include <string>

namespace note { namespace model {

// Inspired by http://www.developer.nokia.com/Community/Wiki/File_based_logging_in_Qt_for_debugging
// and http://qt-project.org/doc/qt-4.8/debug.html
class TextFileLogger {
public:
    explicit TextFileLogger(const std::string &filename);
	~TextFileLogger();

    static void fileMessageHandler(QtMsgType type, const char *msg);

private:
	static std::ofstream logfile;
};

}}

#endif // TEXTFILELOGGER_H
