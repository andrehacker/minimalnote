#ifndef ABSTRACTVIEW_H
#define ABSTRACTVIEW_H

#include <vector>
#include <memory>
#include "NoteDTO.h"

namespace note { namespace common {

/*
Abstract class allowing the View to be accessed from the Presenter
*/
class AbstractView
{
public:
    // virtual destructor is required because AbstractView is used
    // as a interface class (base class)
    virtual ~AbstractView() {}
    virtual void showWindow() = 0;
    virtual void setSearchFilter(const std::string &text) = 0;
    virtual std::string getSearchFilter() = 0;
    virtual std::vector<note::common::TagDto> getSelectedTags() = 0;
    virtual void updateNotes(const std::vector<note::common::NoteDto> &notes) = 0;
    virtual void updateTags(const std::vector<note::common::TagDto> &tags) = 0;
    virtual void updateNote(const note::common::NoteDto &note) = 0;
    virtual void deleteNote(const note::common::NoteDto &note) = 0;
    virtual void addNewNote(note::common::NoteDto &newNote) = 0;
    virtual void showInfoMessageBox(std::string info) = 0;
};

}}

#endif // ABSTRACTVIEW_H
