## 🔷 Введение: Что такое SOLID?

**SOLID** — это акроним из пяти принципов объектно-ориентированного проектирования, предложенных Робертом Мартином (Uncle Bob), чтобы сделать код:

* устойчивым к изменениям,
* легко расширяемым,
* тестируемым и сопровождаемым.

**Принципы:**

1. **S** — Single Responsibility Principle (Принцип единственной ответственности)
2. **O** — Open/Closed Principle (Принцип открытости/закрытости)
3. **L** — Liskov Substitution Principle (Принцип подстановки Барбары Лисков)
4. **I** — Interface Segregation Principle (Принцип разделения интерфейса)
5. **D** — Dependency Inversion Principle (Принцип инверсии зависимостей)

---

# 🔹 Шаг 1: SRP — Принцип единственной ответственности

**💡 Идея:** У каждого класса должна быть только **одна причина для изменения**.

### ✅ Пример (Нарушение SRP)

```cpp
class Invoice {
public:
    void calculateTotal() { /* ... */ }
    void saveToFile() { /* ... */ }
    void printInvoice() { /* ... */ }
};
```

**Проблема:** `Invoice` считает, сохраняет и печатает — 3 ответственности.

### ✅ Пример (Правильный подход)

```cpp
class Invoice {
public:
    void calculateTotal() { /* ... */ }
};

class InvoiceSaver {
public:
    void saveToFile(const Invoice& invoice) { /* ... */ }
};

class InvoicePrinter {
public:
    void print(const Invoice& invoice) { /* ... */ }
};
```

### ❓ Вопросы:

* Какая ответственность нарушена?
* Можно ли легко протестировать `InvoicePrinter` отдельно?
* Что произойдет, если изменится формат хранения счета?

---

# 🔹 Шаг 2: OCP — Принцип открытости/закрытости

**💡 Идея:** Классы **открыты для расширения**, но **закрыты для изменения**.

### ❌ Нарушение

```cpp
class Shape {
public:
    virtual std::string type() const = 0;
};

class AreaCalculator {
public:
    double calculateArea(const Shape& shape) {
        if (shape.type() == "circle") {
            // ...
        } else if (shape.type() == "square") {
            // ...
        }
        return 0.0;
    }
};
```

**Проблема:** при добавлении новой фигуры нужно менять `AreaCalculator`.

### ✅ Правильно: использовать полиморфизм

```cpp
class Shape {
public:
    virtual double area() const = 0;
};

class Circle : public Shape {
public:
    double area() const override { return 3.14 * r * r; }
private:
    double r = 5;
};

class Square : public Shape {
public:
    double area() const override { return side * side; }
private:
    double side = 4;
};
```

### ❓ Вопросы:

* Можешь ли ты добавить `Triangle`, не трогая существующий код?
* Почему это важно для устойчивости к изменениям?

---

# 🔹 Шаг 3: LSP — Принцип подстановки Лисков

**💡 Идея:** Подтипы должны **заменять базовые типы** без нарушения логики.

### ❌ Нарушение

```cpp
class Bird {
public:
    virtual void fly() { std::cout << "Flying\n"; }
};

class Ostrich : public Bird {
public:
    void fly() override { throw std::logic_error("Can't fly"); }
};
```

### ✅ Решение: изменить иерархию

```cpp
class Bird {
public:
    virtual void makeSound() = 0;
};

class FlyingBird : public Bird {
public:
    virtual void fly() = 0;
};

class Sparrow : public FlyingBird {
    void fly() override { std::cout << "Sparrow flying\n"; }
    void makeSound() override { std::cout << "Chirp\n"; }
};

class Ostrich : public Bird {
    void makeSound() override { std::cout << "Boom boom\n"; }
};
```

### ❓ Вопросы:

* Почему `Ostrich` нарушает LSP?
* Как LSP связан с полиморфизмом?

---

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

---

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

