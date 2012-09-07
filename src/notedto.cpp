#include "notedto.h"

namespace note { namespace common {

NoteDto::NoteDto() :
    id_(-1), title_(""), content_("") {
}

// TODO: Extend!
NoteDto::NoteDto(int id, const std::string &title, const std::string &content, const std::string &tags) :
    id_(id), title_(title), content_(content), tags_(tags) {
}

int NoteDto::getId() const {
    return id_;
}

std::string NoteDto::getTitle() const {
    return title_;
}

std::string NoteDto::getContent() const {
    return content_;
}

std::string NoteDto::getTags() const {
    return tags_;
}

void NoteDto::setId(int id) {
    id_ = id;
}

void NoteDto::setTitle(const std::string &title) {
    title_ = title;
}

void NoteDto::setContent(const std::string &content) {
    content_ = content;
}

void NoteDto::setTags(const std::string &tags) {
    tags_ = tags;
}

}}
