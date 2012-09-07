#include "textfilelogger.h"
#include <fstream>
#include <QtGlobal>

namespace note { namespace model {

std::ofstream TextFileLogger::logfile;

TextFileLogger::TextFileLogger(const std::string &filename) {
    logfile.open(filename.c_str(), std::ios::out | std::ios::app);
}

TextFileLogger::~TextFileLogger() {
    logfile << "Closing Debug Logfile" << std::endl;
	logfile.close();
}

void TextFileLogger::fileMessageHandler(QtMsgType type, const char *msg) {
	logfile << msg << std::endl;
	logfile.flush();
}

}}
