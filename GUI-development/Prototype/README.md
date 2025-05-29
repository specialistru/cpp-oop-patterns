## 🔧 **Функциональность**

* Главное окно содержит две кнопки:

  * "Добавить карточку товара"
  * "Добавить панель настроек"
* Каждая кнопка клонирует соответствующий GUI-прототип и добавляет в интерфейс.
* Используется паттерн **Prototype** для гибкого копирования элементов.

---

## 📁 Структура проекта

```
/PrototypeGuiApp
 ├── main.cpp
 ├── MainWindow.h / .cpp
 ├── WidgetPrototype.h
 ├── ProductCardPrototype.h / .cpp
 ├── SettingsPanelPrototype.h / .cpp
 └── form.ui (опционально)
```

---

## ✅ Сборка (через `.pro` файл)

```pro
QT += core gui widgets

SOURCES += \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    MainWindow.h \
    WidgetPrototype.h \
    ProductCardPrototype.h \
    SettingsPanelPrototype.h
```

---

## 🧪 Результат:

* По нажатию на кнопки создаются **копии GUI-элементов** на основе прототипов.
* Элементы независимы друг от друга.
* Реализован **паттерн Prototype** с возможностью расширения.
