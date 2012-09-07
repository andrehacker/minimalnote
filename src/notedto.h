#ifndef NOTEDTO_H
#define NOTEDTO_H

#include <vector>
#include <string>
#include <QMetaType>
#include "tagdto.h"

namespace note { namespace common {

class NoteDto
{
public:
    NoteDto();
    NoteDto(int id, const std::string &title, const std::string &content, const std::string &tags);
    int getId() const;
    std::string getTitle() const;
    std::string getContent() const;
    // std::vector<TagDto> getTags() const;
    std::string getTags() const;    // commaseparated version
    std::string getDateCreated() const;
    std::string getDateModified() const;
    void setId(int id);
    void setTitle(const std::string &title);
    void setContent(const std::string &content);
    void setTags(const std::string &tags);
    bool isDeleted();

private:
    int id_;
    std::string title_;
    std::string content_;
    //std::vector<TagDto> tags_;    // TODO
    std::string tags_;
    std::string dateCreated_;
    std::string dateModified_;
    bool isDeleted_;
};

}}

#endif // NOTEDTO_H
