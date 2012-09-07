#include <QDebug>
#include "notesuimodel.h"

namespace note { namespace view {

NotesUiModel::NotesUiModel(QObject *parent)
    : QAbstractListModel(parent) {}

int NotesUiModel::rowCount(const QModelIndex &parent) const {
    return notes_.size();
}

QVariant NotesUiModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();

    if (index.row() >= static_cast<int>(notes_.size()))
        return QVariant();

    if (role == Qt::DisplayRole) {
        // TODO: Test, whether this (access by row) works for a sorted list
        NoteDto note = notes_.at(index.row());
        return QString::fromStdString(note.getTitle());
    } else {
        return QVariant();
    }
}

NoteDto NotesUiModel::getNote(const QModelIndex &index) {
    if (!index.isValid())
        return NoteDto();

    if (index.row() >= static_cast<int>(notes_.size()))
        return NoteDto();

    return notes_.at(index.row());
}

Qt::ItemFlags NotesUiModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index); // | Qt::ItemIsEditable;
}

bool NotesUiModel::setData(const QModelIndex &index,
                              const QVariant &value, int role) {
    if (index.isValid() && role == Qt::EditRole) {
        notes_.at(index.row()) = value.value<NoteDto>();
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

bool NotesUiModel::insertRows(int position, int rows, const QModelIndex &index) {
    beginInsertRows(QModelIndex(), position, position+rows-1);

    NoteDto *emptyNote = new NoteDto;
    for (int row = 0; row < rows; ++row) {
        notes_.insert(notes_.begin()+position, rows, *emptyNote);
    }

    endInsertRows();
    return true;
}

bool NotesUiModel::removeRows(const int position, const int rows, const QModelIndex &index) {
    if  (rows > 0) {
        beginRemoveRows(QModelIndex(), position, position+rows-1);

        for (int row = 0; row < rows; ++row) {
            notes_.erase(notes_.begin()+position);
        }

        endRemoveRows();
    }
    return true;
}

void NotesUiModel::addNoteAt (const int position, const NoteDto &note) {
    insertRows(position, 1);
    setData(index(position), QVariant::fromValue(note));
}

void NotesUiModel::append (const NoteDto &note) {
    addNoteAt(rowCount(), note);
}

void NotesUiModel::updateNoteAt (const QModelIndex &noteIndex, const NoteDto &note) {
    if (noteIndex.isValid()) {
        setData(noteIndex, QVariant::fromValue(note));
    }
}

QModelIndex NotesUiModel::getIndexByNote(const NoteDto &note) {
    for (int row=0; row < rowCount(); ++row ) {
        if (getNote(index(row)).getId() == note.getId()) {
            return index(row);
        }
    }
    return QModelIndex();   // empty invalid index (isValid()=false)
}

}}
