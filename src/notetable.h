#ifndef NOTETABLE_H
#define NOTETABLE_H

#include <vector>
#include <string>
#include "NoteDTO.h"

namespace note { namespace model {
using note::common::TagDto;
using note::common::NoteDto;

class DatabaseConnection;   // forward declaration

class NoteTable
{
public:
    NoteTable(DatabaseConnection &);

    bool createTable();

    std::vector<NoteDto> getNotes();
    std::vector<NoteDto> getNotes(const std::string &searchText);
    std::vector<NoteDto> getNotes(const std::string &searchText, const std::vector<TagDto> &tagFilter);

    bool add(NoteDto &newNote);
    bool update(NoteDto &changedNote);
    bool remove(const NoteDto &note);

    bool removeTagFromNotes(const std::string &tagName);

private:
    NoteTable& operator=(const NoteTable&);    // disallow copy/assignment
    NoteTable(const NoteTable&);    // disallow copy

	std::string normalizeTagsForUi(std::string tags);
	std::string normalizeTagsForDB(std::string tags);

    DatabaseConnection &db_;    // this is a dependency, not in our ownership, and may never be null (because it is a reference)
};

}}

#endif // NOTETABLE_H
