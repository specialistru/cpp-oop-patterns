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
