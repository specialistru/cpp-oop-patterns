## 📌 Паттерн 5: **Prototype (Прототип)**

### 🧠 Назначение:

Позволяет копировать существующие объекты, **не привязываясь к их конкретным классам**. Особенно полезен, когда создание объекта «с нуля» дорого по ресурсам или сложно.

---

### ✅ Преимущества:

* Позволяет клонировать объекты без знания их конкретных типов.
* Экономит ресурсы при клонировании тяжёлых объектов.
* Удобен для сохранения и восстановления состояния (копия, undo, snapshot).
* Легко расширяется новыми типами объектов.

---

### ❌ Недостатки:

* Требует реализации клонирования в каждом классе.
* Может быть сложно реализовать глубокое копирование.
* При неправильной реализации легко нарушить инварианты объекта.

---

### 🏗️ Структура классов

```
        ┌────────────────────┐
        │     Prototype      │◄─────┐
        │ +clone()           │      │
        └────────┬───────────┘      │
                 │                  │
        ┌────────▼────────┐         │
        │ ConcretePrototypeA │      │
        │ +clone()          │───────┘
        └──────────────────┘
```

---

### 💻 Пример кода на C++

```cpp
#include <iostream>
#include <memory>
#include <string>

// Прототип
class Prototype {
public:
    virtual std::unique_ptr<Prototype> clone() const = 0;
    virtual void use() const = 0;
    virtual ~Prototype() = default;
};

// Конкретный прототип A
class ConcretePrototypeA : public Prototype {
private:
    std::string data;

public:
    ConcretePrototypeA(const std::string& d) : data(d) {}
    
    std::unique_ptr<Prototype> clone() const override {
        return std::make_unique<ConcretePrototypeA>(*this);
    }

    void use() const override {
        std::cout << "Используется ConcretePrototypeA с данными: " << data << "\n";
    }
};

// Конкретный прототип B
class ConcretePrototypeB : public Prototype {
private:
    int value;

public:
    ConcretePrototypeB(int v) : value(v) {}
    
    std::unique_ptr<Prototype> clone() const override {
        return std::make_unique<ConcretePrototypeB>(*this);
    }

    void use() const override {
        std::cout << "Используется ConcretePrototypeB с значением: " << value << "\n";
    }
};

// Клиентский код
void clientCode(const Prototype& prototype) {
    auto clone = prototype.clone();
    clone->use();
}

int main() {
    ConcretePrototypeA originalA("Пример A");
    ConcretePrototypeB originalB(42);

    std::cout << "Клонируем A:\n";
    clientCode(originalA);

    std::cout << "\nКлонируем B:\n";
    clientCode(originalB);
}
```

---

### 🖼️ Иллюстративная схема:

```
OriginalA          OriginalB
   │                  │
   ▼                  ▼
clone()             clone()
   │                  │
   ▼                  ▼
CopyA              CopyB
   │                  │
 use()              use()
```

---

### ❓ Углубляющие вопросы:

1. Чем отличается поверхностное клонирование от глубокого (shallow vs deep copy)?
2. Когда лучше использовать Prototype вместо Factory Method?
3. Какие классы C++ по умолчанию поддерживают копирование?
4. Что может пойти не так при копировании объектов с указателями?
5. Как реализовать прототип, если объект зависит от внешнего ресурса (например, файл)?
6. Можно ли совместить паттерн Prototype с Builder или Decorator?

## 🧪 Паттерн 5: **Prototype (Прототип)**

### 🔍 Углубляющие вопросы и ответы

1. **Разница shallow copy vs deep copy?**

   * *Shallow copy* копирует указатели, *deep copy* копирует значения, находящиеся по этим указателям. Последнее безопаснее, но затратнее.

2. **Как реализовать глубокое копирование?**

   * Вручную или с помощью сериализации/десериализации.

3. **Что может пойти не так с указателями?**

   * Поверхностное копирование может привести к двойному удалению памяти (double free).

4. **Как прототип работает с внешними ресурсами?**

   * Необходимо передавать дескрипторы или использовать RAII-объекты (`fstream`, `unique_ptr`, и т.д.).

---

### 💻 Расширенный пример на C++ с глубоким клонированием

```cpp
#include <iostream>
#include <string>
#include <memory>

class Document {
private:
    std::string* content;

public:
    Document(const std::string& text) {
        content = new std::string(text);
    }

    // Глубокое копирование
    Document(const Document& other) {
        content = new std::string(*other.content);
    }

    ~Document() {
        delete content;
    }

    std::unique_ptr<Document> clone() const {
        return std::make_unique<Document>(*this);
    }

    void show() const {
        std::cout << "Document content: " << *content << "\n";
    }
};

int main() {
    Document original("Hello, Prototype!");
    auto copy = original.clone();

    original.show();
    copy->show();
}
```

---

### 🖼️ Схема Prototype (глубокая копия)

```
Original Document (content* -> "Hello")
         |
        clone()
         |
     Deep Copy
         ▼
Cloned Document (new content* -> "Hello")
```
