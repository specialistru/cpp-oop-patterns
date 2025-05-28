# 🔹 Шаг 1: SRP — Принцип единственной ответственности

**💡 Идея:** У каждого класса должна быть только **одна причина для изменения**.

### ✅ Пример (Нарушение SRP)

```cpp
class Invoice {
public:
    void calculateTotal() { /* ... */ }
    void saveToFile() { /* ... */ }
    void printInvoice() { /* ... */ }
};
```

**Проблема:** `Invoice` считает, сохраняет и печатает — 3 ответственности.

### ✅ Пример (Правильный подход)

```cpp
class Invoice {
public:
    void calculateTotal() { /* ... */ }
};

class InvoiceSaver {
public:
    void saveToFile(const Invoice& invoice) { /* ... */ }
};

class InvoicePrinter {
public:
    void print(const Invoice& invoice) { /* ... */ }
};
```

### ❓ Вопросы:

* Какая ответственность нарушена?
* Можно ли легко протестировать `InvoicePrinter` отдельно?
* Что произойдет, если изменится формат хранения счета?

---
