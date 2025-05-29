#ifndef SETTINGSPANELPROTOTYPE_H
#define SETTINGSPANELPROTOTYPE_H

#include "WidgetPrototype.h"
#include <QGroupBox>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QComboBox>

class SettingsPanelPrototype : public WidgetPrototype {
public:
    QWidget* clone(QWidget* parent = nullptr) const override {
        QGroupBox* box = new QGroupBox("Настройки", parent);
        QVBoxLayout* layout = new QVBoxLayout(box);
        QCheckBox* check = new QCheckBox("Включить уведомления", box);
        QComboBox* themeSelect = new QComboBox(box);
        themeSelect->addItems({"Светлая", "Тёмная"});
        layout->addWidget(check);
        layout->addWidget(themeSelect);
        box->setLayout(layout);
        return box;
    }
};

#endif // SETTINGSPANELPROTOTYPE_H
