## 🔷 1. Что такое Prototype

**Prototype** — порождающий паттерн проектирования, который позволяет создавать новые объекты **путём копирования уже существующих**, а не через `new` или фабрики.

📌 Основная идея:

> Вместо создания объекта с нуля — копируем "прототип".

Полезен в GUI, когда:

* Есть много похожих виджетов (например, кнопки, элементы меню, формы).
* Нужна динамическая генерация UI на основе шаблонов.

---

## 🔧 2. Базовая реализация на C++

### Абстрактный базовый класс:

```cpp
class WidgetPrototype {
public:
    virtual WidgetPrototype* clone() const = 0;
    virtual void draw() const = 0;
    virtual ~WidgetPrototype() = default;
};
```

### Конкретная реализация:

```cpp
class Button : public WidgetPrototype {
public:
    Button(const std::string& label) : label(label) {}

    WidgetPrototype* clone() const override {
        return new Button(*this); // поверхностное копирование
    }

    void draw() const override {
        std::cout << "Button: " << label << std::endl;
    }

private:
    std::string label;
};
```

---

## 🖼️ 3. Пример в GUI (Qt): Копирование кнопки

В Qt можно использовать паттерн Prototype для:

* Копирования `QPushButton` с сохранением стиля, надписей и т.д.
* Клонирования пользовательских виджетов.

(Полный пример Qt — смотри в конце 👇)

---

## 🧬 4. Поверхностное vs. глубокое копирование

### Поверхностное копирование:

* Копируются только значения полей.
* Указатели копируются как есть → **опасность shared state**.

### Глубокое копирование:

* Дублируются все вложенные объекты.
* Указатели копируются с созданием новых экземпляров.

#### Пример глубокого копирования:

```cpp
class Panel : public WidgetPrototype {
public:
    Panel(const QString& title, QWidget* child)
        : title(title), childWidget(new QWidget(*child)) {}

    WidgetPrototype* clone() const override {
        return new Panel(title, new QWidget(*childWidget));
    }

private:
    QString title;
    QWidget* childWidget;
};
```

---

## 🏗️ 5. Prototype + Абстрактная фабрика

Можно создать фабрику, которая хранит прототипы и клонирует их:

```cpp
class WidgetFactory {
public:
    void registerPrototype(const QString& key, WidgetPrototype* prototype) {
        prototypes[key] = prototype;
    }

    WidgetPrototype* create(const QString& key) {
        return prototypes[key]->clone();
    }

private:
    QMap<QString, WidgetPrototype*> prototypes;
};
```

---

## 🛠️ 6. Практический пример (GUI на Qt): клонирование виджетов

**Задача:** создать окно с одной кнопкой "Клонировать", которая создаёт копию кнопки-прототипа и размещает её в интерфейсе.

---

## ✅ Пример Qt-приложения с паттерном Prototype

### 📁 `WidgetPrototype.h`

```cpp
#ifndef WIDGETPROTOTYPE_H
#define WIDGETPROTOTYPE_H

#include <QPushButton>

class WidgetPrototype {
public:
    virtual QPushButton* clone(QWidget* parent = nullptr) const = 0;
    virtual ~WidgetPrototype() = default;
};

#endif // WIDGETPROTOTYPE_H
```

---

### 📁 `StyledButtonPrototype.h`

```cpp
#ifndef STYLEDBUTTONPROTOTYPE_H
#define STYLEDBUTTONPROTOTYPE_H

#include "WidgetPrototype.h"

class StyledButtonPrototype : public WidgetPrototype {
public:
    StyledButtonPrototype(const QString& label, const QString& style)
        : label(label), style(style) {}

    QPushButton* clone(QWidget* parent = nullptr) const override {
        QPushButton* btn = new QPushButton(label, parent);
        btn->setStyleSheet(style);
        return btn;
    }

private:
    QString label;
    QString style;
};

#endif // STYLEDBUTTONPROTOTYPE_H
```

---

### 📁 `MainWindow.h`

```cpp
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include "WidgetPrototype.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void cloneButton();

private:
    QVBoxLayout* layout;
    WidgetPrototype* prototype;
};

#endif // MAINWINDOW_H
```

---

### 📁 `MainWindow.cpp`

```cpp
#include "MainWindow.h"
#include "StyledButtonPrototype.h"
#include <QPushButton>
#include <QScrollArea>
#include <QWidget>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    QWidget* central = new QWidget(this);
    layout = new QVBoxLayout(central);

    // Прототип
    prototype = new StyledButtonPrototype("Клон", "background-color: lightblue;");

    QPushButton* cloneBtn = new QPushButton("Клонировать кнопку", this);
    connect(cloneBtn, &QPushButton::clicked, this, &MainWindow::cloneButton);

    layout->addWidget(cloneBtn);
    setCentralWidget(central);
}

void MainWindow::cloneButton() {
    QPushButton* newBtn = prototype->clone(this);
    layout->addWidget(newBtn);
}

MainWindow::~MainWindow() {
    delete prototype;
}
```

---

### 📁 `main.cpp`

```cpp
#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow w;
    w.setWindowTitle("Prototype GUI Example");
    w.resize(400, 300);
    w.show();

    return app.exec();
}
```

---

## 🚨 7. Потенциальные проблемы

| Проблема                        | Решение                                              |
| ------------------------------- | ---------------------------------------------------- |
| Утечки памяти                   | Используй `unique_ptr` / `delete`                    |
| Глубокое копирование сложно     | Разделяй данные и интерфейс                          |
| Qt не копирует QWidget напрямую | Используй **паттерн-прототип**, не `QWidget::copy()` |

---

## 🧪 8. Задание для самостоятельной работы

**Задача:**

> Реализуй приложение на Qt, в котором можно создавать шаблонные формы (например, карточки товаров, панели с настройками) и клонировать их в интерфейсе. Используй паттерн **Prototype**.

**Условия:**

* Используй абстрактный базовый класс.
* Реализуй минимум 2 типа прототипов.
* Добавь кнопку "Клонировать", которая добавляет копию в интерфейс.
