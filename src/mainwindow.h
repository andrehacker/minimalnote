#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <QSystemTrayIcon>
#include <QCompleter>
#include <memory>
#include "tagsuimodel.h"
#include "globalhotkey.h"
#include "NoteDTO.h"
#include "abstractview.h"
#include "notesuimodel.h"
#include "tageditor.h"

namespace note { namespace common {
    class Presenter;        // forward declaration
}}

namespace Ui {
    class MainWindow;   // forward declaration. See ui_mainwindow.h
}

namespace note { namespace view {

using note::common::NoteDto;
using note::common::TagDto;

class MainWindow : public QMainWindow, public note::common::AbstractView
{
    Q_OBJECT

public:
    explicit MainWindow(note::common::Presenter &presenter);
    ~MainWindow();

    virtual void showEvent(QShowEvent *event);  // overwritten
    virtual void closeEvent(QCloseEvent *event);
    static Ui::MainWindow *sui; // static version of ui, for globalhotkey

    // Event filter to detect FocusEvents for content
    // TODO: Can this be replaces by overwriting the event in the parent widget? Will events be bubbled up?
    bool eventFilter(QObject* object, QEvent* event);

    // Virtual methods from AbstractView
    virtual void addNewNote(NoteDto &newNote);
    virtual void updateNotes(const std::vector<NoteDto> &notes);
    virtual void updateTags(const std::vector<TagDto> &tags);
    virtual void updateNote(const NoteDto &note);
    virtual void deleteNote(const NoteDto &note);
    virtual std::string getSearchFilter();
    virtual std::vector<TagDto> getSelectedTags();
    virtual void setSearchFilter(const std::string &text);
    virtual void showWindow();
    virtual void showInfoMessageBox(std::string info);

private slots:
	void buttonNewClicked();
    void buttonOptionsClicked();
    void resultCurrentChanged();
    void resultSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void tagsSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void titleEditingFinished();
    void tagsEditingFinished();
    void lineSearchTextChanged(const QString &text);
    void hotKeyPressed(uint keyId, uint modifiers);
    // Tray Icon slots
    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);
    
private:
    // Helper methods
    void restoreWindowFromTray();
    void initTrayIcon();
    void selectNoteByRow(int row);
    void focusNoteText();
    NoteDto getSelectedNote();
    void selectNextNote(bool directionDown);

    ::Ui::MainWindow *ui_;    // null at beginning, will be initialized in constructor

    QSystemTrayIcon trayIcon;
    std::unique_ptr<QMenu> trayIconMenu;
    std::unique_ptr<QAction> restoreAction;
    std::unique_ptr<QAction> quitAction;
    note::model::GlobalHotKey globalHotKey_;
    QStringList tagsStringList_;
    TagsUiModel tagsUiModel_;
    TagEditor tagEditor_;
    NotesUiModel notesUiModel_;
    QCompleter tagsCompleter_;
};

}}

#endif // MAINWINDOW_H
