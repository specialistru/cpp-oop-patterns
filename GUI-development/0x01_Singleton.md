## 🔷 1. Что такое Singleton

**Паттерн Singleton** — это порождающий шаблон проектирования, который гарантирует, что у класса есть **только один экземпляр**, и предоставляет к нему **глобальную точку доступа**.

Применяется, когда:

* Нужно централизованно управлять ресурсами (например, логами, конфигурацией, состоянием GUI).
* Требуется контролировать доступ к общему объекту.

---

## 🔧 2. Реализация Singleton на C++ (C++11 и выше)

**Современный, потокобезопасный Singleton**:

```cpp
class Singleton {
public:
    // Возвращает ссылку на единственный экземпляр
    static Singleton& getInstance() {
        static Singleton instance; // Гарантированно потокобезопасен с C++11
        return instance;
    }

    // Пример метода
    void doSomething() {
        // Логика
    }

private:
    // Конструктор, деструктор и операторы копирования закрыты
    Singleton() {}
    ~Singleton() {}
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};
```

---

## ✅ 3. Плюсы и минусы в GUI-контексте

### Плюсы:

* Централизованный доступ к данным (например, настройкам интерфейса).
* Упрощает доступ к объектам, которые должны быть уникальны (например, главное окно).

### Минусы:

* **Тестируемость страдает** (сложно подменить в тестах).
* Может привести к **жесткой связанности**.
* Часто **злоупотребляют** (используют вместо правильно спроектированных зависимостей).

---

## 🖼️ 4. Пример: Singleton для конфигурации в Qt

```cpp
// ConfigManager.h
class ConfigManager {
public:
    static ConfigManager& instance() {
        static ConfigManager inst;
        return inst;
    }

    void setTheme(const QString& theme) { this->theme = theme; }
    QString getTheme() const { return theme; }

private:
    ConfigManager() {}
    ~ConfigManager() {}
    ConfigManager(const ConfigManager&) = delete;
    ConfigManager& operator=(const ConfigManager&) = delete;

    QString theme = "Light";
};

// Использование в коде GUI:
QString theme = ConfigManager::instance().getTheme();
```

---

## 🧪 5. Как тестировать Singleton

Чтобы улучшить тестируемость:

* Используйте **абстракции (интерфейсы)**.
* Делайте Singleton **обёрткой над инъекцией зависимостей**.
* В тестах можно использовать **MockSingleton** или инъекцию через метод `setInstance()` (с осторожностью).

Пример (не классический Singleton, но тестируемый):

```cpp
class IConfig {
public:
    virtual QString getTheme() const = 0;
    virtual ~IConfig() {}
};

class ConfigManager : public IConfig {
    ...
};
```

---

## ❌ 6. Типичные ошибки

| Ошибка                             | Как избежать                                |
| ---------------------------------- | ------------------------------------------- |
| Несоблюдение потокобезопасности    | Используй `static local variable` (C++11+)  |
| Утечки памяти                      | Избегай `new` без необходимости             |
| Использование везде (анти-паттерн) | Применяй только при настоящей необходимости |
| Проблемы с порядком уничтожения    | Используй `static` локальную переменную     |

---

## 🚫 7. Когда **не стоит** использовать Singleton

* Когда объект может быть **инстанцирован несколько раз без проблем**.
* Когда лучше использовать **Dependency Injection**.
* Когда **многопоточность** сложна и Singleton создаёт точки конфликтов.
* При **юнит-тестировании**, если Singleton мешает изоляции тестов.

---

## 🛠️ 8. Практическое задание

🔸 **Задача:**
Создай простое GUI-приложение на **Qt**, в котором используется Singleton:

### Условия:

* Singleton `ThemeManager` управляет цветовой темой интерфейса (светлая/тёмная).
* Главное окно (`MainWindow`) отображает текущую тему и кнопку "Сменить тему".
* При нажатии тема переключается, и это отображается на UI.

### Подсказки:

* Реализуй класс `ThemeManager` как Singleton.
* Используй сигналы/слоты для уведомления `MainWindow` об изменении темы.
