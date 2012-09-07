
#include "helper.h"

namespace note { namespace common {

// Copied from http://www.codeproject.com/Articles/10880/A-trim-implementation-for-std-string
// Has to be removed with boost::trim as soon as
// VC++ compiler bug is fixed occuring with boost::trim and C++11 lambdas
void Helper::trimString(std::string &text) {
	std::string::size_type pos = text.find_last_not_of(' ');
	if(pos != std::string::npos) {
		text.erase(pos + 1);
		pos = text.find_first_not_of(' ');
		if(pos != std::string::npos) text.erase(0, pos);
	} else text.erase(text.begin(), text.end());
}

}}