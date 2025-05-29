#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QScrollArea>
#include "WidgetPrototype.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void addProductCard();
    void addSettingsPanel();

private:
    QWidget* containerWidget;
    QVBoxLayout* layout;

    WidgetPrototype* productCardPrototype;
    WidgetPrototype* settingsPanelPrototype;
};

#endif // MAINWINDOW_H
