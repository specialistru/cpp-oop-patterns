## 📌 Паттерн 2: **Factory Method (Фабричный метод)**

### 🧠 Назначение:

Предоставляет интерфейс для создания объектов, позволяя подклассам решать, какой класс создавать. Это позволяет классу делегировать создание объектов подклассам.

---

### ✅ Преимущества:

* Избавляет от привязки к конкретным классам.
* Упрощает добавление новых продуктов (Open/Closed Principle).
* Централизует создание объектов.

---

### ❌ Недостатки:

* Увеличение количества классов.
* Усложнение кода — необходимо создание иерархий продуктов и создателей.
* Меньше контроля над созданием, если нужно тонко настроить.

---

### 🏗️ Структура классов

```
┌──────────────────┐
│    Creator       │<────────────┐
│ + factoryMethod()│             │
└──────┬───────────┘             │
       │                         │
       ▼                         ▼
┌────────────┐           ┌─────────────┐
│ Concrete   │           │ Concrete    │
│ Creator A  │           │ Creator B   │
└────┬───────┘           └────┬────────┘
     │ factoryMethod()        │ factoryMethod()
     ▼                        ▼
┌────────────┐        ┌────────────┐
│ Product A  │        │ Product B  │
└────────────┘        └────────────┘
```

---

### 💻 Пример кода на C++

```cpp
#include <iostream>
#include <memory>

// Абстрактный продукт
class Product {
public:
    virtual void use() = 0;
    virtual ~Product() = default;
};

// Конкретный продукт A
class ProductA : public Product {
public:
    void use() override {
        std::cout << "Используется ProductA\n";
    }
};

// Конкретный продукт B
class ProductB : public Product {
public:
    void use() override {
        std::cout << "Используется ProductB\n";
    }
};

// Абстрактный создатель
class Creator {
public:
    virtual std::unique_ptr<Product> factoryMethod() const = 0;

    void operation() const {
        auto product = factoryMethod();
        product->use();
    }

    virtual ~Creator() = default;
};

// Конкретный создатель A
class ConcreteCreatorA : public Creator {
public:
    std::unique_ptr<Product> factoryMethod() const override {
        return std::make_unique<ProductA>();
    }
};

// Конкретный создатель B
class ConcreteCreatorB : public Creator {
public:
    std::unique_ptr<Product> factoryMethod() const override {
        return std::make_unique<ProductB>();
    }
};

// Клиентский код
int main() {
    std::unique_ptr<Creator> creatorA = std::make_unique<ConcreteCreatorA>();
    creatorA->operation();  // Используется ProductA

    std::unique_ptr<Creator> creatorB = std::make_unique<ConcreteCreatorB>();
    creatorB->operation();  // Используется ProductB
}
```

---

### 🖼️ Иллюстративная схема:

```
main()
  │
  ├──> ConcreteCreatorA → ProductA
  │       └──> use()
  └──> ConcreteCreatorB → ProductB
          └──> use()
```

---

### ❓ Углубляющие вопросы:

1. В чём отличие паттерна Factory Method от Simple Factory?
2. Почему выгодно использовать абстрактный класс `Product`, а не конкретный?
3. Какие преимущества дает виртуальный метод `factoryMethod()`?
4. Что произойдет, если клиенту напрямую передавать `ProductA`, минуя фабрику?
5. Как расширить эту систему, чтобы она поддерживала ещё 10 разных продуктов?
6. Что можно использовать вместо `unique_ptr` в более низкоуровневой среде C++?

## 🏭 Паттерн 2: **Factory Method (Фабричный метод)**

### 🔍 Углубляющие вопросы и ответы

1. **В чем отличие от Abstract Factory?**

   * Factory Method позволяет создавать объекты одного типа, в то время как Abstract Factory предоставляет интерфейс для создания семейств взаимосвязанных объектов.

2. **Как обеспечить расширяемость?**

   * Используйте наследование и полиморфизм, позволяя подклассам изменять тип создаваемых объектов.

3. **Как избежать жесткой связи с конкретными классами?**

   * Работайте с абстракциями (интерфейсами), а не с конкретными реализациями.

4. **Когда использовать Factory Method?**

   * Когда создание объекта требует сложной логики или когда система должна быть независимой от способа создания объектов.

5. **Как интегрировать с другими паттернами?**

   * Factory Method может быть использован в сочетании с паттерном Abstract Factory для создания семейства объектов.

---

### 🧱 Расширенный пример на C++

```cpp
#include <iostream>

class Product {
public:
    virtual void use() = 0;
    virtual ~Product() = default;
};

class ConcreteProductA : public Product {
public:
    void use() override { std::cout << "Используется ConcreteProductA\n"; }
};

class ConcreteProductB : public Product {
public:
    void use() override { std::cout << "Используется ConcreteProductB\n"; }
};

class Creator {
public:
    virtual Product* factoryMethod() const = 0;
    void someOperation() {
        Product* product = factoryMethod();
        product->use();
        delete product;
    }
    virtual ~Creator() = default;
};

class ConcreteCreatorA : public Creator {
public:
    Product* factoryMethod() const override { return new ConcreteProductA(); }
};

class ConcreteCreatorB : public Creator {
public:
    Product* factoryMethod() const override { return new ConcreteProductB(); }
};

int main() {
    ConcreteCreatorA creatorA;
    creatorA.someOperation();

    ConcreteCreatorB creatorB;
    creatorB.someOperation();

    return 0;
}
```

---

### 🖼️ Схема

```
+---------------------+
|   Creator           |
|---------------------|
| + factoryMethod()   |
| + someOperation()   |
+---------------------+
        ^
        |
+---------------------+
| ConcreteCreatorA    |
|---------------------|
| + factoryMethod()   |
+---------------------+
        ^
        |
+---------------------+
| ConcreteProductA    |
|---------------------|
| + use()             |
+---------------------+
```
