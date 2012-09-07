#include "settingsui.h"

namespace note { namespace common {

int SettingsUi::minimizedInfoCount = 0;

bool SettingsUi::minimizedInfoAllowed() {
    ++minimizedInfoCount;
    return (minimizedInfoCount == 1);
}

}}
