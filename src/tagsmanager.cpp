#include "tagsmanager.h"

namespace note { namespace model {

TagsManager::TagsManager(DatabaseConnection &db) :
    tagTable_(db) {
    // Attention. Database is probably not yet opened in this constructor.
}

bool TagsManager::createTable() {
    return tagTable_.createTable();
}

std::vector<TagDto> TagsManager::getAll() {
    return tagTable_.getAll();
}

bool TagsManager::add(TagDto &newTag) {
    return tagTable_.add(newTag);
}

bool TagsManager::update(const TagDto &changedTag) {
    return tagTable_.update(changedTag);
}

bool TagsManager::remove(const TagDto &tag) {
    return tagTable_.remove(tag);
}

}}
