# 🔹 Шаг 5: DIP — Принцип инверсии зависимостей

**💡 Идея:** Модули верхнего уровня **не должны зависеть от модулей нижнего уровня** — оба зависят от **абстракций**.

### ❌ Нарушение

```cpp
class FileLogger {
public:
    void log(const std::string& msg) { /* ... */ }
};

class OrderProcessor {
    FileLogger logger;
public:
    void process() {
        logger.log("Processing order...");
    }
};
```

**Проблема:** `OrderProcessor` зависит от конкретной реализации логгера.

### ✅ Решение

```cpp
class ILogger {
public:
    virtual void log(const std::string& msg) = 0;
};

class FileLogger : public ILogger {
public:
    void log(const std::string& msg) override { /* ... */ }
};

class OrderProcessor {
    ILogger& logger;
public:
    OrderProcessor(ILogger& l) : logger(l) {}

    void process() {
        logger.log("Processing order...");
    }
};
```

### ❓ Вопросы:

* Почему абстракция важнее реализации?
* Как DIP помогает при написании модульных тестов?
