#ifndef NOTESUIMODEL_H
#define NOTESUIMODEL_H
#include <vector>
#include <QAbstractListModel>
#include "NoteDTO.h"

// Required to store NoteDTO in QVariant
Q_DECLARE_METATYPE(note::common::NoteDto)
	
namespace note { namespace view {

using note::common::NoteDto;

/*
  UI Model holding a list of NoteDto objects.
  Views are attached to this model and show the content.

  TODO: Remove the additional notes_ vector and replace with the built in!
  Otherwise sorting probably won't work
*/
class NotesUiModel : public QAbstractListModel
{
public:
    NotesUiModel(QObject *parent = 0);

    // overwritten
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());

    // custom methods
    void updateNoteAt (const QModelIndex &noteIndex, const NoteDto &note);
    void addNoteAt (const int position, const NoteDto &note);
    void append (const NoteDto &note);
    NoteDto getNote(const QModelIndex &index);
    QModelIndex getIndexByNote(const NoteDto &note);

private:
    std::vector<NoteDto> notes_;
};

}}

#endif // NOTESUIMODEL_H
