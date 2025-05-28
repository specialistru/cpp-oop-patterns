# 🔹 Шаг 4: ISP — Принцип разделения интерфейса

**💡 Идея:** **Не заставляй клиента зависеть от интерфейсов, которые он не использует.**

### ❌ Нарушение

```cpp
class IMachine {
public:
    virtual void print() = 0;
    virtual void scan() = 0;
    virtual void fax() = 0;
};

class OldPrinter : public IMachine {
public:
    void print() override { /* ok */ }
    void scan() override { throw std::logic_error("Not supported"); }
    void fax() override { throw std::logic_error("Not supported"); }
};
```

### ✅ Разделение интерфейса

```cpp
class IPrinter {
public:
    virtual void print() = 0;
};

class IScanner {
public:
    virtual void scan() = 0;
};

class Printer : public IPrinter {
public:
    void print() override { /* do print */ }
};
```

### ❓ Вопросы:

* Какие интерфейсы нужны `Printer`, а какие избыточны?
* Как ISP влияет на масштабируемость?
