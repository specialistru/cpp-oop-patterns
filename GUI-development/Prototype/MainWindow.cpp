#include "MainWindow.h"
#include "ProductCardPrototype.h"
#include "SettingsPanelPrototype.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    QWidget* central = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(central);

    // Кнопки управления
    QPushButton* addCardBtn = new QPushButton("Добавить карточку товара", this);
    QPushButton* addSettingsBtn = new QPushButton("Добавить панель настроек", this);
    mainLayout->addWidget(addCardBtn);
    mainLayout->addWidget(addSettingsBtn);

    // Прототипы
    productCardPrototype = new ProductCardPrototype("Телефон", "7990 ₽");
    settingsPanelPrototype = new SettingsPanelPrototype();

    // Область отображения виджетов
    QScrollArea* scroll = new QScrollArea(this);
    containerWidget = new QWidget();
    layout = new QVBoxLayout(containerWidget);
    containerWidget->setLayout(layout);
    scroll->setWidget(containerWidget);
    scroll->setWidgetResizable(true);

    mainLayout->addWidget(scroll);
    central->setLayout(mainLayout);
    setCentralWidget(central);

    // Сигналы
    connect(addCardBtn, &QPushButton::clicked, this, &MainWindow::addProductCard);
    connect(addSettingsBtn, &QPushButton::clicked, this, &MainWindow::addSettingsPanel);
}

MainWindow::~MainWindow() {
    delete productCardPrototype;
    delete settingsPanelPrototype;
}

void MainWindow::addProductCard() {
    QWidget* clone = productCardPrototype->clone(containerWidget);
    layout->addWidget(clone);
}

void MainWindow::addSettingsPanel() {
    QWidget* clone = settingsPanelPrototype->clone(containerWidget);
    layout->addWidget(clone);
}
