#ifndef SETTINGSUI_H
#define SETTINGSUI_H

namespace note { namespace common {

class SettingsUi
{
public:

    static bool minimizedInfoAllowed();


private:
    SettingsUi();
    SettingsUi& operator=(const SettingsUi&);
    SettingsUi(const SettingsUi&);

    static int minimizedInfoCount;

};

}}

#endif // SETTINGSUI_H
