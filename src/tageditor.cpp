#include <Qdebug>
#include <QKeyEvent>
#include <QSortFilterProxyModel>
#include <QStringListModel>
#include <QStringList>
#include "tageditor.h"

namespace note { namespace view {

TagEditor::TagEditor (QStringListModel &tagModel) :
    tagProxyModel_(this),
    completer_()
{
    completer_.setParent(this);
    completer_.setWidget(this);

    // set model. Use proxy to filter already added tags
    tagProxyModel_.setSourceModel(&tagModel);
    completer_.setModel(&tagProxyModel_);

    completer_.setCaseSensitivity(Qt::CaseInsensitive);
    // Those won't work: QCompleter::InlineCompletion, QCompleter::UnfilteredPopupCompletion
    completer_.setCompletionMode(QCompleter::PopupCompletion);
    //this->setCompleter(&completer_);  // would work only for one tag

    connect(this, SIGNAL(textChanged(const QString &)),
            this, SLOT(textChanged(const QString &)));
    connect(&completer_, SIGNAL(activated(const QString &)),
            this, SLOT(completerActivated(const QString &)));
}

// Required to catch Enter/Return Events that will be thrown whenever 
// a user selects a completion. This should not result in finishedEditing
void TagEditor::keyPressEvent(QKeyEvent *keyEvent) {
    if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter) {
        if (completer_.popup()->isVisible()) {
            // User selected a completion from completer
            // Ignore keypress to avoid call of finishedEditing
            // However, activated signal will not be thrown then, so we have to do this manually
            completerActivated(completer_.currentCompletion());
            completer_.popup()->hide();
            qDebug() << "Completer will be selected, IGNORE enter/return";
            return;
        }
        qDebug() << "Don't ignore this Enter!";
    }
    // Call base class implementation if we did not handle it
    QLineEdit::keyPressEvent(keyEvent);
}

void TagEditor::textChanged(const QString &text) {
    //qDebug() << "Tag Text changed: " << text;
    QStringList tags = text.split(",");
    QString last = tags.at(tags.size()-1);
    last = last.trimmed();

    if (last.size() != 0) {
        // Set model filter to hide the tags that are already attached to the note (except current prefix)
        // The filter "(?!DEV|Personal)" would exclude tags DEV and Personal
        tags.removeLast();
        if (!tags.isEmpty()) {
        
        }
        QString filter("");
        for(auto it = tags.begin(); it != tags.end(); ++it) {
            if (filter != "") filter.append("|");
            filter.append(it->trimmed());
        }
        if (filter != "")
            filter = "^(?!" + filter + ")";
        tagProxyModel_.setFilterRegExp(filter);

        // displays the popup displaying with current completions
        completer_.setCompletionPrefix(last);
        completer_.complete();
    } else {
        completer_.popup()->hide();
    }
}

void TagEditor::completerActivated(const QString &text) {
    //qDebug() << "Completer activated for text: " << text;
    QStringList tags = this->text().split(",");
    tags.removeLast();  // remove the prefix the user was typing
    tags.append(text);  // add the selected tag
    QString newTags;
    for(auto it = tags.begin(); it != tags.end(); ++it) {
        newTags.append(it->trimmed());
        newTags.append(", ");
    }
    // TODO: BUG: When user presses "Enter" to select a completion, the editingFinished will be thrown!
    // This will store the current prefix in db. Afterwards, this method is executed.
    this->setText(newTags);	// this will set modified to false
	this->setModified(true);
}

}}