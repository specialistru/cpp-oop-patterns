## ✅ **1. Применение каждого принципа в маленькой задаче**

### 🔸 SRP — **Счёт-фактура**

**Задача:** Разделить ответственность за хранение, сохранение и печать.

```cpp
// invoice.h
class Invoice {
public:
    void calculateTotal();
};

class InvoiceSaver {
public:
    void save(const Invoice&);
};

class InvoicePrinter {
public:
    void print(const Invoice&);
};
```

---

### 🔸 OCP — **Подсчёт площади фигур**

**Задача:** Добавить новые фигуры без изменения существующего кода.

```cpp
// shape.h
class Shape {
public:
    virtual double area() const = 0;
};

class Circle : public Shape {
public:
    double area() const override { return 3.14 * r * r; }
private:
    double r = 3;
};

class Square : public Shape {
public:
    double area() const override { return side * side; }
private:
    double side = 4;
};
```

---

### 🔸 LSP — **Птицы**

**Задача:** Строить иерархии без логических ошибок.

```cpp
class Bird {
public:
    virtual void makeSound() = 0;
};

class FlyingBird : public Bird {
public:
    virtual void fly() = 0;
};

class Ostrich : public Bird {
    void makeSound() override { /* ... */ }
};

class Sparrow : public FlyingBird {
    void fly() override { /* ... */ }
    void makeSound() override { /* ... */ }
};
```

---

### 🔸 ISP — **Многофункциональное устройство**

```cpp
class IPrinter {
public:
    virtual void print() = 0;
};

class IScanner {
public:
    virtual void scan() = 0;
};

class BasicPrinter : public IPrinter {
public:
    void print() override { /* ... */ }
};
```

---

### 🔸 DIP — **Логгеры**

```cpp
class ILogger {
public:
    virtual void log(const std::string&) = 0;
};

class ConsoleLogger : public ILogger {
public:
    void log(const std::string& msg) override { std::cout << msg << std::endl; }
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

---

## ✅ **2. Использование шаблонов и абстракций (C++)**

### Шаблонный логгер:

```cpp
template <typename T>
class Logger {
public:
    void log(const T& value) {
        std::cout << "LOG: " << value << std::endl;
    }
};
```

Можно использовать для любых типов, внедряя через шаблоны.

---

## ✅ **3. Сравнение нарушений SOLID с корректным кодом**

📁 Создать структуру репозитория:

```
solid-cpp-examples/
├── SRP/
│   ├── bad.cpp
│   └── good.cpp
├── OCP/
│   ├── bad.cpp
│   └── good.cpp
...
```

Каждая папка содержит два файла:

* `bad.cpp`: нарушение принципа
* `good.cpp`: исправленная версия

Это даст отличный эффект сравнения.

---

## ✅ **4. Реализация GoF-паттернов, связанных с SOLID**

### 🎯 Примеры:

| Паттерн       | Принцип SOLID |
| ------------- | ------------- |
| **Factory**   | OCP, DIP      |
| **Strategy**  | OCP, SRP      |
| **Decorator** | OCP           |
| **Observer**  | DIP           |
| **Adapter**   | DIP, OCP      |

---

### 🔸 Пример: Strategy (алгоритм сортировки)

```cpp
class SortStrategy {
public:
    virtual void sort(std::vector<int>&) = 0;
};

class QuickSort : public SortStrategy {
public:
    void sort(std::vector<int>& data) override {
        // Реализация быстрой сортировки (упрощённо)
    }
};

class Context {
    SortStrategy* strategy;
public:
    void setStrategy(SortStrategy* s) { strategy = s; }
    void sort(std::vector<int>& data) {
        strategy->sort(data);
    }
};
```
