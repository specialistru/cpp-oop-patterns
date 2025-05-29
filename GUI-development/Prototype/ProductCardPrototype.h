#ifndef PRODUCTCARDPROTOTYPE_H
#define PRODUCTCARDPROTOTYPE_H

#include "WidgetPrototype.h"
#include <QGroupBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

class ProductCardPrototype : public WidgetPrototype {
public:
    ProductCardPrototype(const QString& name, const QString& price)
        : name(name), price(price) {}

    QWidget* clone(QWidget* parent = nullptr) const override {
        QGroupBox* box = new QGroupBox(name, parent);
        QVBoxLayout* layout = new QVBoxLayout(box);
        QLabel* priceLabel = new QLabel("Цена: " + price, box);
        QPushButton* buyBtn = new QPushButton("Купить", box);
        layout->addWidget(priceLabel);
        layout->addWidget(buyBtn);
        box->setLayout(layout);
        return box;
    }

private:
    QString name;
    QString price;
};

#endif // PRODUCTCARDPROTOTYPE_H
