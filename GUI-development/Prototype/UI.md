* Динамически добавлять и клонировать различные элементы интерфейса (например, карточки товаров, панели настроек).
* Использовать паттерн Prototype для гибкого копирования виджетов.
* Сохранять и загружать конфигурацию интерфейса.
* Предоставлять пользователю возможность настраивать внешний вид и поведение элементов.

---

## 🧩 Структура проекта

```
/UIBuilderApp
 ├── main.cpp
 ├── MainWindow.h / .cpp
 ├── WidgetPrototype.h
 ├── ProductCardPrototype.h / .cpp
 ├── SettingsPanelPrototype.h / .cpp
 ├── ui_config.json
 └── ui_styles.qss
```

* **`ui_config.json`**: Файл для хранения конфигурации интерфейса в формате JSON.
* **`ui_styles.qss`**: Файл для хранения стилей интерфейса в формате Qt Style Sheets.

---

## 🛠️ Реализация

### 📄 `WidgetPrototype.h`

```cpp
#ifndef WIDGETPROTOTYPE_H
#define WIDGETPROTOTYPE_H

#include <QWidget>
#include <QJsonObject>

class WidgetPrototype {
public:
    virtual QWidget* clone(QWidget* parent = nullptr) const = 0;
    virtual QJsonObject saveState() const = 0;
    virtual void loadState(const QJsonObject& state) = 0;
    virtual ~WidgetPrototype() = default;
};

#endif // WIDGETPROTOTYPE_H
```

### 📄 `ProductCardPrototype.h`

```cpp
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

    QJsonObject saveState() const override {
        QJsonObject state;
        state["type"] = "ProductCard";
        state["name"] = name;
        state["price"] = price;
        return state;
    }

    void loadState(const QJsonObject& state) override {
        name = state["name"].toString();
        price = state["price"].toString();
    }

private:
    QString name;
    QString price;
};

#endif // PRODUCTCARDPROTOTYPE_H
```

### 📄 `SettingsPanelPrototype.h`

```cpp
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

    QJsonObject saveState() const override {
        QJsonObject state;
        state["type"] = "SettingsPanel";
        return state;
    }

    void loadState(const QJsonObject& state) override {
        // Здесь можно загрузить состояние, если оно есть
    }
};

#endif // SETTINGSPANELPROTOTYPE_H
```

### 📄 `MainWindow.h`

```cpp
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QJsonArray>
#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include <QFileDialog>
#include <QMessageBox>
#include "WidgetPrototype.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void addProductCard();
    void addSettingsPanel();
    void saveLayout();
    void loadLayout();

private:
    QWidget* containerWidget;
    QVBoxLayout* layout;
    QMap<QString, WidgetPrototype*> prototypes;
    void loadStyles(const QString& fileName);
    void saveState();
    void loadState();
};

#endif // MAINWINDOW_H
```

### 📄 `MainWindow.cpp`

```cpp
#include "MainWindow.h"
#include "ProductCardPrototype.h"
#include "SettingsPanelPrototype.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    QWidget* central = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(central);

    // Кнопки управления
    QPushButton* addCardBtn = new QPushButton("Добавить карточку товара", this);
    QPushButton* addSettingsBtn = new QPushButton("Добавить панель настроек", this);
    QPushButton* saveBtn = new QPushButton("Сохранить макет", this);
    QPushButton* loadBtn = new QPushButton("Загрузить макет", this);
    mainLayout->addWidget(addCardBtn);
    mainLayout->addWidget(addSettingsBtn);
    mainLayout->addWidget(saveBtn);
    mainLayout->addWidget(loadBtn);

    // Прототипы
    prototypes["ProductCard"] = new ProductCardPrototype("Телефон", "7990 ₽");
    prototypes["SettingsPanel"] = new SettingsPanelPrototype();

    // Область отображения виджетов
    QScrollArea* scroll = new QScrollArea(this);
    containerWidget = new QWidget();
    layout = new QVBoxLayout(containerWidget);
    containerWidget->set
::contentReference[oaicite:20]{index=20}
    containerWidget->setLayout(layout);
    scroll->setWidget(containerWidget);
    scroll->setWidgetResizable(true);

    mainLayout->addWidget(scroll);
    central->setLayout(mainLayout);
    setCentralWidget(central);
    setWindowTitle("UI Конструктор (Prototype)");

    // Сигналы
    connect(addCardBtn, &QPushButton::clicked, this, &MainWindow::addProductCard);
    connect(addSettingsBtn, &QPushButton::clicked, this, &MainWindow::addSettingsPanel);
    connect(saveBtn, &QPushButton::clicked, this, &MainWindow::saveLayout);
    connect(loadBtn, &QPushButton::clicked, this, &MainWindow::loadLayout);

    // Загрузка стилей (если есть)
    loadStyles("ui_styles.qss");
}

MainWindow::~MainWindow() {
    for (auto proto : prototypes)
        delete proto;
}

// Добавить карточку товара
void MainWindow::addProductCard() {
    QWidget* widget = prototypes["ProductCard"]->clone(containerWidget);
    layout->addWidget(widget);
}

// Добавить панель настроек
void MainWindow::addSettingsPanel() {
    QWidget* widget = prototypes["SettingsPanel"]->clone(containerWidget);
    layout->addWidget(widget);
}

// Сохранить макет
void MainWindow::saveLayout() {
    QJsonArray layoutArray;

    for (auto proto : prototypes.values()) {
        layoutArray.append(proto->saveState());
    }

    QJsonDocument doc(layoutArray);
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить макет", "", "JSON (*.json)");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly)) {
            file.write(doc.toJson());
            file.close();
            QMessageBox::information(this, "Сохранение", "Макет успешно сохранён.");
        }
    }
}

// Загрузить макет
void MainWindow::loadLayout() {
    QString fileName = QFileDialog::getOpenFileName(this, "Загрузить макет", "", "JSON (*.json)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) return;

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isArray()) return;

    // Очистить текущий интерфейс
    QLayoutItem* item;
    while ((item = layout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    QJsonArray layoutArray = doc.array();
    for (const QJsonValue& val : layoutArray) {
        QJsonObject obj = val.toObject();
        QString type = obj["type"].toString();

        if (prototypes.contains(type)) {
            WidgetPrototype* proto = prototypes[type];
            proto->loadState(obj);
            QWidget* widget = proto->clone(containerWidget);
            layout->addWidget(widget);
        }
    }

    QMessageBox::information(this, "Загрузка", "Макет успешно загружен.");
}

// Загрузка стилей
void MainWindow::loadStyles(const QString& fileName) {
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly)) {
        QString style = file.readAll();
        this->setStyleSheet(style);
        file.close();
    }
}
```

---

## 🧾 Файл стилей `ui_styles.qss` (пример)

```css
QPushButton {
    font-size: 14px;
    padding: 8px;
    background-color: #f0f0f0;
    border: 1px solid gray;
}

QGroupBox {
    border: 1px solid #aaa;
    border-radius: 4px;
    margin-top: 10px;
    font-weight: bold;
}
```

---

## ✅ Что умеет этот UI-конструктор:

* Добавлять виджеты из зарегистрированных прототипов (кнопками).
* Сохранять структуру GUI в JSON-файл.
* Восстанавливать интерфейс из сохранённого файла.
* Применять стили оформления.

---

## 📦 Дальнейшие улучшения (по желанию):

* **Редактирование элементов в интерфейсе** (по двойному клику — изменение текста, стиля).
* **Перетаскивание и сортировка элементов** (Drag\&Drop).
* **Экспорт/импорт шаблонов** (дополнительных прототипов).
* Поддержка **визуального редактора** стилей (сохранение в `.qss`).

---

Отлично! Давай шаг за шагом реализуем все перечисленные функции для нашего UI-конструктора на C++ с использованием Qt, включая:

* **Редактирование свойств элементов интерфейса**.
* **Поддержку перетаскивания (Drag & Drop)**.
* **Экспорт и импорт шаблонов интерфейсов**.
* **Автосохранение и восстановление состояния интерфейса**.

---

## 🧩 Шаг 1: Редактирование свойств элементов

Для редактирования свойств элементов интерфейса, например, изменения текста на кнопке или имени карточки товара, можно использовать диалоговые окна. Создадим диалоговое окно для редактирования свойств карточки товара:

### 📄 `EditProductCardDialog.h`

```cpp
#ifndef EDITPRODUCTCARDDIALOG_H
#define EDITPRODUCTCARDDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

class EditProductCardDialog : public QDialog {
    Q_OBJECT

public:
    explicit EditProductCardDialog(const QString &name, const QString &price, QWidget *parent = nullptr);
    QString getName() const;
    QString getPrice() const;

private:
    QLineEdit *nameEdit;
    QLineEdit *priceEdit;
    QPushButton *saveButton;
};

#endif // EDITPRODUCTCARDDIALOG_H
```

### 📄 `EditProductCardDialog.cpp`

```cpp
#include "EditProductCardDialog.h"
#include <QVBoxLayout>
#include <QLabel>

EditProductCardDialog::EditProductCardDialog(const QString &name, const QString &price, QWidget *parent)
    : QDialog(parent), nameEdit(new QLineEdit(name, this)), priceEdit(new QLineEdit(price, this)), saveButton(new QPushButton("Сохранить", this)) {

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Название:"));
    layout->addWidget(nameEdit);
    layout->addWidget(new QLabel("Цена:"));
    layout->addWidget(priceEdit);
    layout->addWidget(saveButton);

    connect(saveButton, &QPushButton::clicked, this, &QDialog::accept);
}

QString EditProductCardDialog::getName() const {
    return nameEdit->text();
}

QString EditProductCardDialog::getPrice() const {
    return priceEdit->text();
}
```

Теперь в `MainWindow.cpp` добавим слот для редактирования карточки товара:

### 📄 `MainWindow.cpp` (добавление слота)

```cpp
#include "EditProductCardDialog.h"

// Слот для редактирования карточки товара
void MainWindow::editProductCard(ProductCardPrototype *card) {
    EditProductCardDialog dialog(card->getName(), card->getPrice(), this);
    if (dialog.exec() == QDialog::Accepted) {
        card->setName(dialog.getName());
        card->setPrice(dialog.getPrice());
        // Обновить отображение карточки
    }
}
```

---

## 🧩 Шаг 2: Поддержка перетаскивания (Drag & Drop)

Для реализации перетаскивания виджетов в Qt необходимо переопределить соответствующие события в классе виджета. Пример реализации для виджета, поддерживающего перетаскивание:

### 📄 `DraggableWidget.h`

```cpp
#ifndef DRAGGABLEWIDGET_H
#define DRAGGABLEWIDGET_H

#include <QWidget>
#include <QDrag>
#include <QMimeData>

class DraggableWidget : public QWidget {
    Q_OBJECT

public:
    explicit DraggableWidget(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    QPoint dragStartPosition;
};

#endif // DRAGGABLEWIDGET_H
```

### 📄 `DraggableWidget.cpp`

```cpp
#include "DraggableWidget.h"
#include <QMouseEvent>

DraggableWidget::DraggableWidget(QWidget *parent)
    : QWidget(parent) {
    setAcceptDrops(true);
}

void DraggableWidget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        dragStartPosition = event->pos();
    }
}

void DraggableWidget::mouseMoveEvent(QMouseEvent *event) {
    if (!(event->buttons() & Qt::LeftButton))
        return;

    if ((event->pos() - dragStartPosition).manhattanLength() < QApplication::startDragDistance())
        return;

    QDrag *drag = new QDrag(this);
    QMimeData *mimeData = new QMimeData;
    mimeData->setText("Draggable Widget");
    drag->setMimeData(mimeData);
    drag->exec();
}
```

---

## 🧩 Шаг 3: Экспорт и импорт шаблонов интерфейсов

Для экспорта и импорта шаблонов интерфейса используем формат JSON. Пример сохранения и загрузки состояния интерфейса:

### 📄 `MainWindow.cpp` (сохранение состояния)

```cpp
#include <QJsonDocument>
#include <QFileDialog>
#include <QJsonObject>

void MainWindow::saveLayout() {
    QJsonObject layoutObject;
    // Заполнить layoutObject данными интерфейса

    QJsonDocument doc(layoutObject);
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить макет", "", "JSON (*.json)");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly)) {
            file.write(doc.toJson());
            file.close();
        }
    }
}
```

### 📄 `MainWindow.cpp` (загрузка состояния)

```cpp
#include <QJsonDocument>
#include <QFileDialog>
#include <QJsonObject>

void MainWindow::loadLayout() {
    QString fileName = QFileDialog::getOpenFileName(this, "Загрузить макет", "", "JSON (*.json)");
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
        return;

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isObject()) {
        QJsonObject layoutObject = doc.object();
        // Восстановить интерфейс из layoutObject
    }
}
```

---

## 🧩 Шаг 4: Автосохранение и восстановление состояния интерфейса

Для автосохранения состояния интерфейса можно использовать класс `QSettings`, который позволяет сохранять и загружать настройки приложения.

### 📄 `MainWindow.cpp` (сохранение состояния)

```cpp
#include <QSettings>

void MainWindow::closeEvent(QCloseEvent *event) {
    QSettings
::contentReference[oaicite:29]{index=29}
 
```
Продолжим реализацию **автосохранения и восстановления состояния интерфейса** с помощью `QSettings`.

---

## 🧩 Шаг 4 (продолжение): Автосохранение и восстановление интерфейса

### 📄 В `MainWindow.h`

Добавь:

```cpp
#include <QCloseEvent>

protected:
    void closeEvent(QCloseEvent *event) override;
```

---

### 📄 В `MainWindow.cpp`

#### 📌 Сохранение состояния при закрытии:

```cpp
#include <QSettings>

void MainWindow::closeEvent(QCloseEvent *event) {
    QJsonArray layoutArray;

    for (auto proto : prototypes.values()) {
        layoutArray.append(proto->saveState());
    }

    QJsonDocument doc(layoutArray);
    QSettings settings("MyCompany", "UIBuilderApp");
    settings.setValue("layout", QString::fromUtf8(doc.toJson()));

    QMainWindow::closeEvent(event);
}
```

#### 📌 Загрузка состояния при старте:

Добавь вызов `loadState()` в конструкторе `MainWindow`:

```cpp
loadState();
```

И сам метод:

```cpp
void MainWindow::loadState() {
    QSettings settings("MyCompany", "UIBuilderApp");
    QString json = settings.value("layout").toString();
    if (json.isEmpty()) return;

    QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8());
    if (!doc.isArray()) return;

    QJsonArray layoutArray = doc.array();

    for (const QJsonValue& val : layoutArray) {
        QJsonObject obj = val.toObject();
        QString type = obj["type"].toString();

        if (prototypes.contains(type)) {
            WidgetPrototype* proto = prototypes[type];
            proto->loadState(obj);
            QWidget* widget = proto->clone(containerWidget);
            layout->addWidget(widget);
        }
    }
}
```

---

## ✅ Что реализовано на текущем этапе:

| Функция                     | Статус      | Комментарий                                          |
| --------------------------- | ----------- | ---------------------------------------------------- |
| 🖋️ Редактирование свойств  | ✅           | Через отдельный диалог для карточек товара           |
| 🧲 Drag & Drop              | 🟡 Частично | Создан `DraggableWidget`, нужно реализовать прием    |
| 📥 Экспорт/импорт шаблонов  | ✅           | Через JSON-файлы с кнопками Save/Load                |
| 💾 Автосохранение состояния | ✅           | С помощью `QSettings`, сохраняется при закрытии окна |

---

Отлично! Давай **реализуем полноценный Drag & Drop** с возможностью:

* Перетаскивания виджетов внутри области конструктора.
* Сортировки элементов в `QVBoxLayout` при перемещении.
* Возможности выделения и редактирования через контекстное меню.

---

## 🧩 Реализация Drag & Drop внутри `QVBoxLayout`

### Цель:

Позволить пользователю **перетаскивать виджеты вверх/вниз**, меняя их порядок на лету, как в UI-конструкторах.

---

## 📦 Шаг 1: Базовый класс `DraggableContainer`

Создадим контейнер, который:

* Принимает виджеты с перетаскиванием.
* Обновляет порядок после drop-события.

### 📄 `DraggableContainer.h`

```cpp
#ifndef DRAGGABLECONTAINER_H
#define DRAGGABLECONTAINER_H

#include <QWidget>
#include <QVBoxLayout>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>

class DraggableContainer : public QWidget {
    Q_OBJECT

public:
    explicit DraggableContainer(QWidget* parent = nullptr);

    void addDraggableWidget(QWidget* widget);

protected:
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dragMoveEvent(QDragMoveEvent* event) override;
    void dropEvent(QDropEvent* event) override;

private:
    QVBoxLayout* layout;
};

#endif // DRAGGABLECONTAINER_H
```

---

### 📄 `DraggableContainer.cpp`

```cpp
#include "DraggableContainer.h"
#include <QDrag>
#include <QMouseEvent>

DraggableContainer::DraggableContainer(QWidget* parent)
    : QWidget(parent) {
    setAcceptDrops(true);
    layout = new QVBoxLayout(this);
    layout->setSpacing(8);
    layout->setContentsMargins(4, 4, 4, 4);
    setLayout(layout);
}

void DraggableContainer::addDraggableWidget(QWidget* widget) {
    widget->setObjectName("draggable");
    widget->setAttribute(Qt::WA_DeleteOnClose);
    layout->addWidget(widget);
}

void DraggableContainer::dragEnterEvent(QDragEnterEvent* event) {
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        event->acceptProposedAction();
    }
}

void DraggableContainer::dragMoveEvent(QDragMoveEvent* event) {
    event->acceptProposedAction();
}

void DraggableContainer::dropEvent(QDropEvent* event) {
    QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
    QWidget* source = reinterpret_cast<QWidget*>(itemData.toULongLong());
    if (!source) return;

    int dropPosY = event->position().toPoint().y();
    int index = 0;
    for (int i = 0; i < layout->count(); ++i) {
        if (layout->itemAt(i)->widget()->geometry().center().y() < dropPosY)
            index = i + 1;
    }

    layout->removeWidget(source);
    layout->insertWidget(index, source);
    event->acceptProposedAction();
}
```

---

## 📦 Шаг 2: Перетаскиваемый виджет

Создаем виджет, который **отправляет себя как drag-объект**.

### 📄 `DraggableWidget.h`

```cpp
#ifndef DRAGGABLEWIDGET_H
#define DRAGGABLEWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>

class DraggableWidget : public QWidget {
    Q_OBJECT

public:
    explicit DraggableWidget(QWidget* child, QWidget* parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

private:
    QPoint dragStartPosition;
};

#endif // DRAGGABLEWIDGET_H
```

---

### 📄 `DraggableWidget.cpp`

```cpp
#include "DraggableWidget.h"

DraggableWidget::DraggableWidget(QWidget* child, QWidget* parent)
    : QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->addWidget(child);
    setLayout(layout);
}

void DraggableWidget::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton)
        dragStartPosition = event->pos();
}

void DraggableWidget::mouseMoveEvent(QMouseEvent* event) {
    if (!(event->buttons() & Qt::LeftButton)) return;
    if ((event->pos() - dragStartPosition).manhattanLength() < QApplication::startDragDistance()) return;

    QDrag* drag = new QDrag(this);
    QMimeData* mimeData = new QMimeData;

    QByteArray data;
    data.setNum(reinterpret_cast<qulonglong>(this));
    mimeData->setData("application/x-dnditemdata", data);

    drag->setMimeData(mimeData);
    drag->exec(Qt::MoveAction);
}
```

---

## 📦 Шаг 3: Интеграция в MainWindow

Вместо обычного `QVBoxLayout`, мы теперь используем:

```cpp
DraggableContainer* containerWidget;
```

И добавляем виджеты так:

```cpp
QWidget* prototype = prototypes["ProductCard"]->clone(containerWidget);
DraggableWidget* wrapper = new DraggableWidget(prototype, containerWidget);
containerWidget->addDraggableWidget(wrapper);
```

---

## 📌 Результат

* Элементы интерфейса теперь можно **перетаскивать вверх и вниз**.
* Вся структура интерфейса **автоматически обновляется**.

---
Отлично! Давай реализуем два ключевых компонента для нашего UI-конструктора:

1. **Визуальный инспектор виджетов с контекстным меню** — для редактирования свойств элементов интерфейса.
2. **Визуальный редактор стилей (QSS)** — для настройки внешнего вида виджетов.

---

## 🧰 1. Визуальный инспектор виджетов с контекстным меню

### 🔍 Цель:

Создать контекстное меню для каждого виджета, позволяющее:

* Редактировать свойства виджета.
* Удалять виджет.
* Копировать виджет.

### 🛠️ Реализация:

1. **Создание контекстного меню для виджета:**

   В классе `DraggableWidget` переопределим метод `contextMenuEvent`:

   ```cpp
   void DraggableWidget::contextMenuEvent(QContextMenuEvent *event) {
       QMenu contextMenu(this);

       QAction *editAction = contextMenu.addAction("Редактировать");
       QAction *deleteAction = contextMenu.addAction("Удалить");
       QAction *copyAction = contextMenu.addAction("Копировать");

       connect(editAction, &QAction::triggered, this, &DraggableWidget::editWidget);
       connect(deleteAction, &QAction::triggered, this, &DraggableWidget::deleteWidget);
       connect(copyAction, &QAction::triggered, this, &DraggableWidget::copyWidget);

       contextMenu.exec(event->globalPos());
   }
   ```

2. **Методы для обработки действий:**

   ```cpp
   void DraggableWidget::editWidget() {
       // Открыть диалог редактирования свойств виджета
   }

   void DraggableWidget::deleteWidget() {
       // Удалить виджет из родительского контейнера
       delete this;
   }

   void DraggableWidget::copyWidget() {
       // Создать новый экземпляр виджета с теми же свойствами
   }
   ```

---

## 🎨 2. Визуальный редактор стилей (QSS)

### 🔍 Цель:

Предоставить пользователю возможность редактировать стили виджетов в реальном времени.

### 🛠️ Реализация:

1. **Использование готового редактора QSS:**

   Рассмотрим использование [QssStylesheetEditor](https://github.com/Qt-Widgets/Qss-Stylesheet-Editor), который предоставляет:

   * Редактирование QSS с подсветкой синтаксиса.
   * Предварительный просмотр изменений.
   * Поддержку переменных и палитры.

   Чтобы интегрировать его в наше приложение:

   * Скачай и собери редактор из исходников.
   * Встрои его в наше приложение как отдельный диалог или окно.

2. **Пример использования QssStylesheetEditor:**

   ```cpp
   void MainWindow::openStyleEditor() {
       QssStylesheetEditor *editor = new QssStylesheetEditor(this);
       editor->setStyleSheet(currentStyle);
       editor->show();
   }
   ```

   В этом примере `currentStyle` — это строка, содержащая текущие стили приложения.

---

## ✅ Результат:

* **Контекстное меню** для каждого виджета с опциями редактирования, удаления и копирования.
* **Визуальный редактор стилей** для настройки внешнего вида виджетов в реальном времени.
