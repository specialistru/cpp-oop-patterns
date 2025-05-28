### 🟩 **S — Single Responsibility Principle (SRP)**

**Принцип единственной ответственности**

| Характеристика   | Описание                                                     |
| ---------------- | ------------------------------------------------------------ |
| **Преимущество** | Упрощает поддержку и тестирование, повышает читаемость.      |
| **Недостаток**   | Разбиение на множество мелких классов усложняет архитектуру. |
| **Важность**     | 10/10                                                        |

**🔴 Нарушение:**

```cpp
class Report {
public:
    void generate() { /* логика генерации отчета */ }
    void saveToFile(const std::string& path) { /* логика записи в файл */ }
};
```

📌 *Описание: Класс выполняет сразу две задачи — генерацию и сохранение отчета.*

**✅ Правильно:**

```cpp
class Report {
public:
    void generate() { /* логика генерации */ }
};

class ReportSaver {
public:
    void saveToFile(const Report& report, const std::string& path) { /* сохранение */ }
};
```

📌 *Описание: Каждая сущность отвечает за одну задачу. Легко тестировать, изменять по отдельности.*

---

### 🟩 **O — Open/Closed Principle (OCP)**

**Принцип открытости/закрытости**

| Характеристика   | Описание                                                        |
| ---------------- | --------------------------------------------------------------- |
| **Преимущество** | Добавление нового функционала без изменения существующего кода. |
| **Недостаток**   | Необходимость абстракций может привести к усложнению.           |
| **Важность**     | 9/10                                                            |

**🔴 Нарушение:**

```cpp
class Shape {
public:
    enum Type { CIRCLE, RECTANGLE } type;
};

class Renderer {
public:
    void render(Shape& shape) {
        if (shape.type == Shape::CIRCLE) { /* рисуем круг */ }
        else if (shape.type == Shape::RECTANGLE) { /* рисуем прямоугольник */ }
    }
};
```

📌 *Описание: Чтобы добавить новый тип, нужно менять `Renderer`.*

**✅ Правильно:**

```cpp
class Shape {
public:
    virtual void render() = 0;
};

class Circle : public Shape {
public:
    void render() override { /* рисуем круг */ }
};

class Rectangle : public Shape {
public:
    void render() override { /* рисуем прямоугольник */ }
};
```

📌 *Описание: Новый тип фигуры добавляется без изменения существующих классов.*

---

### 🟩 **L — Liskov Substitution Principle (LSP)**

**Принцип подстановки Лисков**

| Характеристика   | Описание                                               |
| ---------------- | ------------------------------------------------------ |
| **Преимущество** | Позволяет использовать подклассы без нарушения логики. |
| **Недостаток**   | Требует строго соблюдения логики базового класса.      |
| **Важность**     | 8/10                                                   |

**🔴 Нарушение:**

```cpp
class Bird {
public:
    virtual void fly() = 0;
};

class Ostrich : public Bird {
public:
    void fly() override {
        throw std::runtime_error("Ostriches can't fly!");
    }
};
```

📌 *Описание: Ostrich нарушает контракт Bird.*

**✅ Правильно:**

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
public:
    void fly() override { /* летает */ }
    void makeSound() override { /* чирикает */ }
};

class Ostrich : public Bird {
public:
    void makeSound() override { /* издает звук */ }
};
```

📌 *Описание: Разделив поведение, избежали логических ошибок.*

---

### 🟩 **I — Interface Segregation Principle (ISP)**

**Принцип разделения интерфейса**

| Характеристика   | Описание                                                                 |
| ---------------- | ------------------------------------------------------------------------ |
| **Преимущество** | Избегание "толстых" интерфейсов, клиент использует только нужные методы. |
| **Недостаток**   | Много мелких интерфейсов = больше кода и зависимости.                    |
| **Важность**     | 7/10                                                                     |

**🔴 Нарушение:**

```cpp
class IMachine {
public:
    virtual void print() = 0;
    virtual void scan() = 0;
    virtual void fax() = 0;
};

class OldPrinter : public IMachine {
public:
    void print() override { /* ок */ }
    void scan() override { throw std::runtime_error("Not supported"); }
    void fax() override { throw std::runtime_error("Not supported"); }
};
```

📌 *Описание: Класс вынужден реализовывать ненужные методы.*

**✅ Правильно:**

```cpp
class IPrinter {
public:
    virtual void print() = 0;
};

class IScanner {
public:
    virtual void scan() = 0;
};

class OldPrinter : public IPrinter {
public:
    void print() override { /* печатает */ }
};
```

📌 *Описание: Класс реализует только нужный интерфейс.*

---

### 🟩 **D — Dependency Inversion Principle (DIP)**

**Принцип инверсии зависимостей**

| Характеристика   | Описание                                               |
| ---------------- | ------------------------------------------------------ |
| **Преимущество** | Повышает гибкость, облегчает тестирование.             |
| **Недостаток**   | В C++ требует усилий — указатели, шаблоны, абстракции. |
| **Важность**     | 9/10                                                   |

**🔴 Нарушение:**

```cpp
class MySQLDatabase {
public:
    void connect() { /* ... */ }
};

class UserRepository {
    MySQLDatabase db;
public:
    void getUser() { db.connect(); }
};
```

📌 *Описание: Жесткая зависимость от реализации.*

**✅ Правильно:**

```cpp
class IDatabase {
public:
    virtual void connect() = 0;
};

class MySQLDatabase : public IDatabase {
public:
    void connect() override { /* ... */ }
};

class UserRepository {
    IDatabase& db;
public:
    UserRepository(IDatabase& database) : db(database) {}
    void getUser() { db.connect(); }
};
```

📌 *Описание: Можно подставить любую реализацию (например, для тестов — мок).*
