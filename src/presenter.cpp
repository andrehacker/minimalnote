#include <vector>
#include <algorithm>
#include <QDebug>
#include "presenter.h"
#include "abstractview.h"
#include "mainwindow.h"


namespace note { namespace common {

using note::common::TagDto;
using note::common::NoteDto;

Presenter::Presenter() :
    db_(),
    notesManager_(db_),
    tagsManager_(db_) {

    // Init Database
    if (! db_.openExisting()) {
        // This is the first start. Create db file and tables
        db_.createDatabaseAndOpen();
        notesManager_.createTable();
        tagsManager_.createTable();
    }

    // Create View. Done here because we need to pass a pointer to presenter.
    // AbstractView's destructor is declared virtual, so derived object will be deleted
    view_ = std::unique_ptr<note::common::AbstractView>(new note::view::MainWindow(*this));
    view_->showWindow();

    // Populate GUI with initial data
    std::vector<NoteDto> notes = notesManager_.getNotes();
    view_->updateNotes(notes);

    std::vector<TagDto> tags = tagsManager_.getAll();
    view_->updateTags(tags);

    // TODO: Subscribe to model for changes (e.g. after sync). Update UI afterwards
}

Presenter::~Presenter() {
    qDebug() << "Presenter Destructor";
}

void Presenter::optionsClicked() {
    view_->showInfoMessageBox("Not yet implemented");
}

void Presenter::newNoteClicked() {
    // Remove search filter (if existing)
    view_->setSearchFilter("");

    // Add (empty) new note to model.
    // Passed note will be populated with new id
    NoteDto newNote(-1, "", "", "");
    notesManager_.add(newNote);

    // Update the UI-Mode (add new node at beginning and select)
    view_->addNewNote(newNote);
}

void Presenter::searchTextChanged(const std::string &text) {
    std::vector<NoteDto> notes = notesManager_.getNotes(text, view_->getSelectedTags());
    view_->updateNotes(notes);
}

void Presenter::titleEditingFinished(NoteDto &changedNote) {
    // Update Title in Model
    notesManager_.update(changedNote);

    // Update UI-Model (new title)
    view_->updateNote(changedNote);
}

void Presenter::tagsEditingFinished(NoteDto &changedNote) {
    // Update Tags in Model
    notesManager_.update(changedNote);

    // Update UI-Model
    view_->updateNote(changedNote);
}

void Presenter::contentEditingFinished(NoteDto &changedNote) {
    // Update Content in Model
    notesManager_.update(changedNote);

    // Update UI-Model (new content)
    view_->updateNote(changedNote);
}

void Presenter::deleteNote(const NoteDto &note) {
    // Mark as deleted in Model
    notesManager_.remove(note);

    // Update UI
    view_->deleteNote(note);
}

void Presenter::resultSelectionChanged() {
    // Handled in view
}

void Presenter::tagSelectionChanged() {
    // TODO
    std::vector<TagDto> selectedTags = view_->getSelectedTags();
    qDebug() << "Selected Tags: " << selectedTags.size();

    // Update search result according to selected tags and search filter
    std::vector<NoteDto> notes = notesManager_.getNotes(
                view_->getSearchFilter(),
                selectedTags);
    view_->updateNotes(notes);
}

}}

