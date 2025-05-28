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

## 🔍 Дополнительно: Паттерны STL/Boost/C++-идоматические

| Паттерн / Приём                                   | Описание / Где используется                         |
| ------------------------------------------------- | --------------------------------------------------- |
| **RAII (Resource Acquisition Is Initialization)** | Управление ресурсами через конструкторы/деструкторы |
| **Type Erasure**                                  | Boost.Any / std::function                           |
| **Pimpl (Pointer to Implementation)**             | Сокрытие деталей реализации                         |
| **CRTP (Curiously Recurring Template Pattern)**   | Шаблонная реализация static polymorphism            |
| **Smart Pointer Idioms**                          | std::unique\_ptr, std::shared\_ptr                  |
| **Policy-based Design**                           | Шаблонные классы со стратегиями                     |

---

## 🛠 Применение в C++

| Особенность C++            | Использование в паттернах   |
| -------------------------- | --------------------------- |
| Шаблоны (Templates)        | Strategy, Adapter, Factory  |
| Множественное наследование | Mixins, Observer            |
| Умные указатели            | Composite, Proxy, Flyweight |
| Move-семантика             | Builder, Prototype          |
| STL-контейнеры и итераторы | Iterator, Composite         |
