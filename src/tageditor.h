#ifndef TAGEDITOR_H
#define TAGEDITOR_H

#include <QCompleter>
#include <QLineEdit>
#include <QSortFilterProxyModel>
#include <QStringListModel>

namespace note { namespace view {

class TagEditor : public QLineEdit
{
	
    Q_OBJECT

public:
    explicit TagEditor (QStringListModel &tagModel);

    // Overwritten from QWidget. See impl why this is required
    virtual void keyPressEvent(QKeyEvent *event);   
    
private slots:
    void textChanged(const QString &text);
    void completerActivated(const QString &text);

private:
    TagEditor(const TagEditor&);    // disallow copy
    TagEditor& operator=(const TagEditor&);    // disallow copy assignment
    
    QCompleter completer_;
    //QStringListModel &tagModel_; // dependency, not our ownership
    QSortFilterProxyModel tagProxyModel_;
};

}}

#endif // TAGEDITOR_H
