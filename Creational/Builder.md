## 📌 Паттерн 4: **Builder (Строитель)**

### 🧠 Назначение:

Отделяет **конструирование сложного объекта** от его представления, так что один и тот же процесс создания может порождать разные представления.

Используется, когда объект имеет **много параметров**, особенно необязательных, и их сложно удобно передавать в конструкторе.

---

### ✅ Преимущества:

* Позволяет пошагово конструировать объекты.
* Упрощает создание объектов с множеством конфигураций.
* Обеспечивает чистый, читаемый и гибкий код.
* Хорошо работает с **иммутабельными объектами**.

---

### ❌ Недостатки:

* Может быть избыточен для простых объектов.
* Увеличивает количество классов.
* Некоторые реализации допускают нарушение инкапсуляции.

---

### 🏗️ Структура классов

```
Client → Director → Builder
                     ├─ ConcreteBuilderA
                     ├─ ConcreteBuilderB
                             │
                             ▼
                        Product
```

---

### 💻 Пример кода на C++

Допустим, мы строим **дом**, и у каждого дома есть стены, крыша и окна. Мы хотим использовать одного "строителя" для разных типов домов: деревянных и каменных.

```cpp
#include <iostream>
#include <string>
#include <memory>

// Продукт
class House {
public:
    void setWalls(const std::string& w) { walls = w; }
    void setRoof(const std::string& r) { roof = r; }
    void setWindows(const std::string& win) { windows = win; }

    void show() const {
        std::cout << "Дом с: " << walls << ", " << roof << ", " << windows << "\n";
    }

private:
    std::string walls;
    std::string roof;
    std::string windows;
};

// Интерфейс строителя
class HouseBuilder {
public:
    virtual void buildWalls() = 0;
    virtual void buildRoof() = 0;
    virtual void buildWindows() = 0;
    virtual std::unique_ptr<House> getHouse() = 0;
    virtual ~HouseBuilder() = default;
};

// Конкретный строитель: деревянный дом
class WoodenHouseBuilder : public HouseBuilder {
private:
    std::unique_ptr<House> house = std::make_unique<House>();

public:
    void buildWalls() override { house->setWalls("деревянные стены"); }
    void buildRoof() override { house->setRoof("черепичная крыша"); }
    void buildWindows() override { house->setWindows("стеклянные окна"); }
    std::unique_ptr<House> getHouse() override { return std::move(house); }
};

// Конкретный строитель: каменный дом
class StoneHouseBuilder : public HouseBuilder {
private:
    std::unique_ptr<House> house = std::make_unique<House>();

public:
    void buildWalls() override { house->setWalls("каменные стены"); }
    void buildRoof() override { house->setRoof("бетонная крыша"); }
    void buildWindows() override { house->setWindows("армированные окна"); }
    std::unique_ptr<House> getHouse() override { return std::move(house); }
};

// Директор
class Director {
private:
    HouseBuilder* builder;

public:
    void setBuilder(HouseBuilder* b) { builder = b; }

    void construct() {
        builder->buildWalls();
        builder->buildRoof();
        builder->buildWindows();
    }
};

// Клиент
int main() {
    Director director;

    WoodenHouseBuilder woodenBuilder;
    director.setBuilder(&woodenBuilder);
    director.construct();
    std::unique_ptr<House> woodenHouse = woodenBuilder.getHouse();
    woodenHouse->show();

    StoneHouseBuilder stoneBuilder;
    director.setBuilder(&stoneBuilder);
    director.construct();
    std::unique_ptr<House> stoneHouse = stoneBuilder.getHouse();
    stoneHouse->show();
}
```

---

### 🖼️ Иллюстративная схема:

```
main()
  │
  ▼
Director ──────────────┐
  │                    │
  ▼                    ▼
WoodenBuilder       StoneBuilder
  │                    │
  ▼                    ▼
Дом A                Дом B
```

---

### ❓ Углубляющие вопросы:

1. Зачем нужен класс `Director`, если клиент может вызывать методы билдера напрямую?
2. Как использовать паттерн Builder без `Director` (например, через Fluent-интерфейс)?
3. В чём разница между Builder и Abstract Factory?
4. Почему Builder хорошо сочетается с паттерном Composite или Decorator?
5. Какие проблемы могут возникнуть при попытке повторного использования `builder->getHouse()`?
6. Как бы вы реализовали Builder для сложной структуры данных, например, `JSON` или `SQL-запрос`?
