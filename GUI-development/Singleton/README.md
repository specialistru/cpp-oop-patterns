## 🎯 Задача

Создать приложение с окном, в котором:

* Есть кнопка "Сменить тему".
* Отображается текущая тема (`Light` или `Dark`).
* При нажатии тема переключается.
* Singleton `ThemeManager` хранит и управляет текущей темой.

---

## 🧱 Структура проекта

```
/ThemeApp
 ├── main.cpp
 ├── ThemeManager.h
 ├── ThemeManager.cpp
 ├── MainWindow.h
 └── MainWindow.cpp
```

## ✅ Как собрать

1. Создай `.pro` файл для Qt (если используешь qmake):

```pro
QT += core gui widgets
SOURCES += main.cpp ThemeManager.cpp MainWindow.cpp
HEADERS += ThemeManager.h MainWindow.h
```

2. Собери через Qt Creator или `qmake && make`.

---

## 📌 Результат:

* При запуске отображается: `Current Theme: Light`.
* Кнопка "Сменить тему" переключает её на `Dark` и обратно.
* Всё управление — через Singleton `ThemeManager`.
