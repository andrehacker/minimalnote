#ifndef TAGSUIMODEL_H
#define TAGSUIMODEL_H

#include <QStringListModel>
#include <QString>
#include "tagdto.h"

namespace note { namespace view {

class TagsUiModel : public QStringListModel
{
public:
    explicit TagsUiModel (const QStringList &strings);

    void append (const QString &string);
    note::common::TagDto getTag(const QModelIndex &index);

private:
    TagsUiModel(const TagsUiModel&);    // disallow copy
    TagsUiModel& operator=(const TagsUiModel&);    // disallow copy assignment
};

}}

#endif // TAGSUIMODEL_H
