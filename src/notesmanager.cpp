#include "notesmanager.h"

namespace note { namespace model {

NotesManager::NotesManager(DatabaseConnection &db) :
    noteTable_(db) {
    // Attention. Database is probably not yet opened in this constructor.
}

bool NotesManager::createTable() {
    return noteTable_.createTable();
}

std::vector<NoteDto> NotesManager::getNotes() {
    return noteTable_.getNotes();
}

std::vector<NoteDto> NotesManager::getNotes(const std::string searchText) {
    return noteTable_.getNotes(searchText);
}

std::vector<NoteDto> NotesManager::getNotes(const std::string &searchText, const std::vector<TagDto> &tagFilter) {
    return noteTable_.getNotes(searchText, tagFilter);
}

bool NotesManager::add(NoteDto &newNote) {
    return noteTable_.add(newNote);
}

bool NotesManager::update(NoteDto &changedNote) {
    return noteTable_.update(changedNote);
}

bool NotesManager::remove(const NoteDto &note) {
    return noteTable_.remove(note);
}

}}
