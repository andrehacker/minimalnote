#include <iostream>
#include <string>
#include <functional>
#include <windows.h>
#include <QMainWindow>
#include <QAbstractEventDispatcher>
#include <QtDebug>
#include "globalhotkey.h"
#include "mainwindow.h"

namespace note { namespace model {

// WINDOWS Hotkey API
const unsigned int kKeyF = 0x46;
const unsigned int kKeyG = 0x47;
// keeping item pressed (auto repeat) will not invoke multiple hotkey notifications
const unsigned int kMOD_NOREPEAT = 0x4000;

GlobalHotKey *GlobalHotKey::instance_ = 0;
QAbstractEventDispatcher::EventFilter GlobalHotKey::prevEventFilter_ = 0;

GlobalHotKey::GlobalHotKey() {
    instance_ = this;
}

// Inspired by http://code.google.com/p/shotscreens/source/browse/cppclient/core/globalshortcut.cpp?r=75670c87e304900afaf1fe0cff6981b2ad4ebbb5
// and https://github.com/sboli/twmn/blob/master/twmnd/shortcutgrabber.cpp
bool GlobalHotKey::registerHotkeys(WId handle) {

    bool ok;
    ok = RegisterHotKey(
        handle,   //hWnd, optional. If this parameter is NULL, WM_HOTKEY messages are posted to the message queue of the calling thread and must be processed in the message loop.
        1,
        MOD_ALT | MOD_SHIFT | kMOD_NOREPEAT,
        kKeyF);
    
    ok = ok && RegisterHotKey(
        handle,   //hWnd, optional. If this parameter is NULL, WM_HOTKEY messages are posted to the message queue of the calling thread and must be processed in the message loop.
        2,
        MOD_ALT | MOD_SHIFT | kMOD_NOREPEAT,
        kKeyG);

    // Create filter to receive Hotkey messages
    prevEventFilter_ = QAbstractEventDispatcher::instance()->setEventFilter(
        GlobalHotKey::eventFilter);

    return ok;
}

bool GlobalHotKey::eventFilter(void *message) {
    // The event filter function should return true if the message should be filtered, (i.e. stopped).
    // It should return false to allow processing the message to continue.
    
    MSG* msg = static_cast<MSG*>(message);
    if (msg->message == WM_HOTKEY)
    {
        //Ui::MainWindow::sui->textEditLog->appendPlainText("Received begin");
        if (instance_) {
            qDebug() << "Signaled HotKeyPressed. key: " << HIWORD(msg->lParam) << " mod: " << LOWORD(msg->lParam);
            emit instance_->hotKeyPressed(HIWORD(msg->lParam), LOWORD(msg->lParam));
        }
        //sui->textEditLog->appendPlainText("WM_HOTKEY message received");
        /*
        const quint32 keycode = HIWORD(msg->lParam);
        const quint32 modifiers = LOWORD(msg->lParam);
        activateShortcut(keycode, modifiers);
        */
        /*
        std::cout << "WM_HOTKEY received with lparam: " << msg.lParam << std::endl;
        //MessageBox(NULL, "You pressed the key!", "Key Press Alert", MB_OK);
        if ( static_cast<unsigned int>(msg.lParam>>16) == kKeyF) {
            std::cout << "pressed F" << std::endl;
        }
        if ( static_cast<unsigned int>(msg.lParam>>16) == kKeyG) {
            std::cout << "pressed G" << std::endl;
        }
        break;
        */
    }
    return false;

}

}}
