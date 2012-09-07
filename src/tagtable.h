#ifndef TAGTABLE_H
#define TAGTABLE_H

#include <vector>
#include "tagdto.h"

namespace note { namespace model {
using note::common::TagDto;

class DatabaseConnection;   // forward decl.

class TagTable
{
public:
    TagTable(DatabaseConnection &);

    bool createTable();

    std::vector<TagDto> getAll();

    bool add(TagDto &newTag);
    bool update(const TagDto &changedTag);
    bool remove(const TagDto &tag);

private:
    TagTable& operator=(const TagTable&);    // disallow copy/assignment
    TagTable(const TagTable&);    // disallow copy

    DatabaseConnection &db_;    // this is a dependency, not in our ownership, and may never be null (because it is a reference)
};

}}

#endif // TAGTABLE_H
