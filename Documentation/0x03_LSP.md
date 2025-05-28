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
