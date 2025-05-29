#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);

private slots:
    void updateTheme(const QString& newTheme);
    void onChangeThemeClicked();

private:
    QLabel* themeLabel;
    QPushButton* toggleButton;
};

#endif // MAINWINDOW_H
