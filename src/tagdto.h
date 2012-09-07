#ifndef TAGDTO_H
#define TAGDTO_H

#include <string>

namespace note { namespace common {

class TagDto
{
public:
    TagDto();
    TagDto(int id, const std::string &name, int noteCount);
    int getId() const;
    std::string getName() const;
    int getNoteCount() const;
    std::string getDateCreated() const;
    std::string getDateUpdated() const;
    void setId(int id);

private:
    int id_;
    std::string name_;
    int noteCount_;
    std::string dateCreated_;
    std::string dateUpdated_;
};

}}

#endif // TAGDTO_H
