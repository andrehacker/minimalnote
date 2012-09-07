#ifndef TAGSMANAGER_H
#define TAGSMANAGER_H

#include <vector>
#include <string>
#include "tagtable.h"
#include "tagdto.h"

namespace note { namespace model {

class TagsManager
{
public:
    TagsManager(DatabaseConnection &db);

    bool createTable();

    std::vector<TagDto> getAll();

    bool add(TagDto &newTag);
    bool update(const TagDto &changedTag);
    bool remove(const TagDto &tag);

private:
    TagsManager& operator=(const TagsManager&);    // disallow copy assignment
    TagsManager(const TagsManager&);    // disallow copy

    TagTable tagTable_;
};

}}

#endif // TAGSMANAGER_H
