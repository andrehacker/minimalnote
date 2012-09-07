#include "tagdto.h"

namespace note { namespace common {

TagDto::TagDto() :
    id_(-1), name_(""), noteCount_(0) {
}

// TODO: Extend!
TagDto::TagDto(int id, const std::string &name, int noteCount) :
    id_(id), name_(name), noteCount_(noteCount) {
}

int TagDto::getId() const {
    return id_;
}

std::string TagDto::getName() const {
    return name_;
}

int TagDto::getNoteCount() const {
    return noteCount_;
}

void TagDto::setId(int id) {
    id_ = id;
}

}}
