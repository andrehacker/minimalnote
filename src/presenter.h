#ifndef PRESENTER_H
#define PRESENTER_H

#include <memory>
#include "databaseconnection.h"
#include "notesmanager.h"
#include "tagsmanager.h"

namespace note {
namespace common {
    class AbstractView; // forward declaration
}}

namespace note { namespace common {

class Presenter
{
public:
    Presenter();
    ~Presenter();

    void optionsClicked();
    void newNoteClicked();

    void searchTextChanged(const std::string &text);

    void titleEditingFinished(note::common::NoteDto &changedNote);
    void tagsEditingFinished(note::common::NoteDto &changedNote);
    void contentEditingFinished(note::common::NoteDto &changedNote);

    void deleteNote(const note::common::NoteDto &note);

    void resultSelectionChanged();
    void tagSelectionChanged();

private:
    Presenter& operator=(const Presenter&);    // disallow copy/assignment
    Presenter(const Presenter&);    // disallow copy

    std::unique_ptr<note::common::AbstractView> view_;
    note::model::DatabaseConnection db_;
    note::model::NotesManager notesManager_;
    note::model::TagsManager tagsManager_;
};

}}

#endif // PRESENTER_H
