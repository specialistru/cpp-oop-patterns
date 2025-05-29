#ifndef THEME_MANAGER_H
#define THEME_MANAGER_H

#include <QObject>
#include <QString>

class ThemeManager : public QObject {
    Q_OBJECT

public:
    static ThemeManager& instance();

    QString currentTheme() const;
    void toggleTheme();

signals:
    void themeChanged(const QString& newTheme);

private:
    ThemeManager();
    QString theme;

    Q_DISABLE_COPY(ThemeManager)
};

#endif // THEME_MANAGER_H
