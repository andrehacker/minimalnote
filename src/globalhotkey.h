#ifndef _HOTKEY_H_
#define _HOTKEY_H_

#include <QMainWindow>
#include <QAbstractEventDispatcher>

namespace note { namespace model {

class GlobalHotKey : public QObject {
	
	Q_OBJECT

public:
	explicit GlobalHotKey();
    bool registerHotkeys(WId handle);
    static bool eventFilter(void *message);

signals:
    void hotKeyPressed(uint keyId, uint modifiers);

private:
    GlobalHotKey& operator=(const GlobalHotKey&);    // disallow copy assignment
    GlobalHotKey(const GlobalHotKey&);    // disallow copy

    static QAbstractEventDispatcher::EventFilter prevEventFilter_;	// what is this good for?
    static GlobalHotKey *instance_;

};

}}

#endif
