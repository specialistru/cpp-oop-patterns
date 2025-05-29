#include "ThemeManager.h"

ThemeManager& ThemeManager::instance() {
    static ThemeManager instance;
    return instance;
}

ThemeManager::ThemeManager()
    : theme("Light") {}  // начальная тема

QString ThemeManager::currentTheme() const {
    return theme;
}

void ThemeManager::toggleTheme() {
    theme = (theme == "Light") ? "Dark" : "Light";
    emit themeChanged(theme);
}
