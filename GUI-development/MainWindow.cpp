#include "MainWindow.h"
#include "ThemeManager.h"
#include <QVBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    QWidget* central = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(central);

    themeLabel = new QLabel(this);
    themeLabel->setText("Current Theme: " + ThemeManager::instance().currentTheme());

    toggleButton = new QPushButton("Сменить тему", this);
    connect(toggleButton, &QPushButton::clicked, this, &MainWindow::onChangeThemeClicked);

    layout->addWidget(themeLabel);
    layout->addWidget(toggleButton);
    setCentralWidget(central);

    // Подписка на сигнал изменения темы
    connect(&ThemeManager::instance(), &ThemeManager::themeChanged,
            this, &MainWindow::updateTheme);
}

void MainWindow::updateTheme(const QString& newTheme) {
    themeLabel->setText("Current Theme: " + newTheme);
}

void MainWindow::onChangeThemeClicked() {
    ThemeManager::instance().toggleTheme();
}
