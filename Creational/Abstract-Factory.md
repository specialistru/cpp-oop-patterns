## 📌 Паттерн 3: **Abstract Factory (Абстрактная фабрика)**

### 🧠 Назначение:

Предоставляет интерфейс для создания семейств взаимосвязанных объектов без указания их конкретных классов.

Этот паттерн особенно полезен, когда объекты из одного семейства должны работать вместе и вы хотите обеспечить совместимость.

---

### ✅ Преимущества:

* Гарантирует совместимость создаваемых объектов.
* Изолирует код создания объектов от бизнес-логики.
* Следует принципу инверсии зависимостей (DIP).
* Упрощает замену «семейств» объектов (например, разные темы GUI).

---

### ❌ Недостатки:

* Сложность кода из-за увеличения числа классов и иерархий.
* Труднее добавлять новые типы продуктов (нарушается Open/Closed при расширении продуктовой линейки).

---

### 🏗️ Структура классов

```
            ┌────────────────────────┐
            │   AbstractFactory      │
            │+createProductA()       │
            │+createProductB()       │
            └──────────┬─────────────┘
                       │
      ┌────────────────┴────────────┐
      ▼                             ▼
┌────────────┐           ┌────────────────┐
│FactoryA    │           │  FactoryB      │
│→ ProductA1 │           │→ ProductA2     │
│→ ProductB1 │           │→ ProductB2     │
└────────────┘           └────────────────┘

      ▲                           ▲
┌────────────┐           ┌────────────────┐
│ ProductA   │           │   ProductB     │
│ (Abstract) │           │  (Abstract)    │
└────────────┘           └────────────────┘
```

---

### 💻 Пример кода на C++

```cpp
#include <iostream>
#include <memory>

// Абстрактные продукты
class AbstractProductA {
public:
    virtual void doA() = 0;
    virtual ~AbstractProductA() = default;
};

class AbstractProductB {
public:
    virtual void doB() = 0;
    virtual ~AbstractProductB() = default;
};

// Конкретные продукты семейства A
class ProductA1 : public AbstractProductA {
public:
    void doA() override {
        std::cout << "ProductA1 работает\n";
    }
};

class ProductA2 : public AbstractProductA {
public:
    void doA() override {
        std::cout << "ProductA2 работает\n";
    }
};

// Конкретные продукты семейства B
class ProductB1 : public AbstractProductB {
public:
    void doB() override {
        std::cout << "ProductB1 работает\n";
    }
};

class ProductB2 : public AbstractProductB {
public:
    void doB() override {
        std::cout << "ProductB2 работает\n";
    }
};

// Абстрактная фабрика
class AbstractFactory {
public:
    virtual std::unique_ptr<AbstractProductA> createProductA() const = 0;
    virtual std::unique_ptr<AbstractProductB> createProductB() const = 0;
    virtual ~AbstractFactory() = default;
};

// Конкретные фабрики
class Factory1 : public AbstractFactory {
public:
    std::unique_ptr<AbstractProductA> createProductA() const override {
        return std::make_unique<ProductA1>();
    }
    std::unique_ptr<AbstractProductB> createProductB() const override {
        return std::make_unique<ProductB1>();
    }
};

class Factory2 : public AbstractFactory {
public:
    std::unique_ptr<AbstractProductA> createProductA() const override {
        return std::make_unique<ProductA2>();
    }
    std::unique_ptr<AbstractProductB> createProductB() const override {
        return std::make_unique<ProductB2>();
    }
};

// Клиентский код
void clientCode(const AbstractFactory& factory) {
    auto productA = factory.createProductA();
    auto productB = factory.createProductB();
    productA->doA();
    productB->doB();
}

int main() {
    Factory1 f1;
    Factory2 f2;

    std::cout << "Клиент с Factory1:\n";
    clientCode(f1);

    std::cout << "\nКлиент с Factory2:\n";
    clientCode(f2);
}
```

---

### 🖼️ Иллюстративная схема:

```
main()
  ├─> Factory1
  │     ├─> ProductA1
  │     └─> ProductB1
  └─> Factory2
        ├─> ProductA2
        └─> ProductB2
```

---

### ❓ Углубляющие вопросы:

1. В чем основное отличие Abstract Factory от Factory Method?
2. Какие типы зависимостей устраняет Abstract Factory?
3. Как абстрактная фабрика способствует соблюдению принципа инверсии зависимостей (DIP)?
4. Что потребуется изменить, чтобы добавить продукт **C** в каждую фабрику?
5. Какие проблемы могут возникнуть при добавлении новой фабрики, например, Factory3?
6. Как адаптировать этот паттерн для конфигурации GUI тем (тёмная/светлая тема)?
7. Как использовать Abstract Factory в проекте с dependency injection?
