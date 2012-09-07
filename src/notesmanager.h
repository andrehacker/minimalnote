#ifndef NOTESMANAGER_H
#define NOTESMANAGER_H
#include <vector>
#include <string>
#include "notetable.h"
#include "NoteDTO.h"

namespace note { namespace model {

/*
  Logic to access any Notes.
  Currently this is only a wrapper around the table.
  Later this could be loading all notes into memory and serve as a buffer
*/
class NotesManager
{
public:
    NotesManager(DatabaseConnection &db);

    bool createTable();

    std::vector<NoteDto> getNotes();
    std::vector<NoteDto> getNotes(const std::string searchText);
    std::vector<NoteDto> getNotes(const std::string &searchText, const std::vector<TagDto> &tagFilter);
    bool add(NoteDto &newNote);
    bool update(NoteDto &changedNote);
    bool remove(const NoteDto &note);

private:
    NotesManager& operator=(const NotesManager&);    // disallow copy assignment
    NotesManager(const NotesManager&);    // disallow copy

    NoteTable noteTable_;
};

}}

#endif // NOTESMANAGER_H
