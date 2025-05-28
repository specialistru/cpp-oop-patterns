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
