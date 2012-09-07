#include "tagsuimodel.h"

namespace note { namespace view {

TagsUiModel::TagsUiModel (const QStringList &strings)
	: QStringListModel(strings)
{}

void TagsUiModel::append (const QString &string) {
	insertRows(rowCount(), 1);
	setData(index(rowCount()-1), string);
}

note::common::TagDto TagsUiModel::getTag(const QModelIndex &index) {
    // TODO: Remove this dirty hack!
    // Make this class store the Tags (similar to NotesUiModel)
    return note::common::TagDto(-1, data(index, Qt::DisplayRole).toString().toStdString(), 0);
}

}}
