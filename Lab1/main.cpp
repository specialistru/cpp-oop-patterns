#include "ColorGOFactory.h"
#include "BWGOFactory.h"
#include "Scene.h"
#include <iostream>

void testColorFactory() {
    std::cout << "=== Testing Color Factory ===\n";
    ColorGOFactory colorFactory;
    
    // Создаем цветные объекты
    Point* p1 = colorFactory.createPoint();
    Circle* c1 = colorFactory.createCircle();
    
    // Модифицируем объекты
    p1->setX(10);
    p1->setY(20);
    p1->setColor("red");
    
    c1->setX(30);
    c1->setY(40);
    c1->setR(5);
    c1->setColor("blue");
    
    // Выводим сцену
    Scene::getInstance().draw();
    Scene::getInstance().clear();
}

void testBWFactory() {
    std::cout << "\n=== Testing BW Factory ===\n";
    BWGOFactory bwFactory;
    
    // Создаем черно-белые объекты
    BWPoint* p2 = bwFactory.createPoint();
    Circle* c2 = bwFactory.createCircle();
    
    // Модифицируем объекты
    p2->setX(50);
    p2->setY(60);
    
    c2->setX(70);
    c2->setY(80);
    c2->setR(10);
    
    // Выводим сцену
    Scene::getInstance().draw();
    Scene::getInstance().clear();
}

void testClone() {
    std::cout << "\n=== Testing Clone Functionality ===\n";
    
    // Создаем оригинальные объекты
    Point originalPoint(100, 200, "green");
    Circle originalCircle(300, 400, 15, "yellow");
    
    // Клонируем объекты
    Point* clonedPoint = originalPoint.clone();
    Circle* clonedCircle = originalCircle.clone();
    
    // Модифицируем клоны
    clonedPoint->setX(150);
    clonedCircle->setY(450);
    
    // Добавляем в сцену
    Scene::getInstance().add(clonedPoint);
    Scene::getInstance().add(clonedCircle);
    
    // Выводим сцену
    Scene::getInstance().draw();
    Scene::getInstance().clear();
}

void testSingleton() {
    std::cout << "\n=== Testing Singleton Pattern ===\n";
    
    // Получаем экземпляр сцены
    Scene& scene1 = Scene::getInstance();
    Scene& scene2 = Scene::getInstance();
    
    // Добавляем объект через одну ссылку
    scene1.add(new Point(500, 600, "purple"));
    
    // Проверяем через другую ссылку
    std::cout << "Scene objects count: " << scene2.draw() << "\n";
    scene2.clear();
}

int main() {
    // Тестируем цветную фабрику
    testColorFactory();
    
    // Тестируем черно-белую фабрику
    testBWFactory();
    
    // Тестируем функциональность клонирования
    testClone();
    
    // Тестируем паттерн Singleton
    testSingleton();
    
    return 0;
}
