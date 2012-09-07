#ifndef HELPER_H
#define HELPER_H

#include <string>

namespace note { namespace common {

class Helper
{
public:
	static void trimString(std::string &text);

private:
    Helper();
    Helper& operator=(const Helper&);    // disallow copy/assignment
    Helper(const Helper&);    // disallow copy
};

}}

#endif // HELPER_H
