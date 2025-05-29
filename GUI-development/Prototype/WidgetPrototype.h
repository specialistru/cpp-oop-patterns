#ifndef WIDGETPROTOTYPE_H
#define WIDGETPROTOTYPE_H

#include <QWidget>

class WidgetPrototype {
public:
    virtual QWidget* clone(QWidget* parent = nullptr) const = 0;
    virtual ~WidgetPrototype() = default;
};

#endif // WIDGETPROTOTYPE_H
