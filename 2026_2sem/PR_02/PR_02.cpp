#include <iostream>
#include <windows.h>
#include "DinoBaraVirtClass.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    
    cout << "Практическая работа 2" << endl;
    cout << "Вариант 8" << endl;
    
    DinoBaraVirtClass* ptr1;
    DinoBaraVirtClass* ptr2;
    DinoBaraVirtClass* ptr3;
    
    // Конструктор с параметром
    cout << "\n=== Создание A с параметром ===";
    A a1(10);
    a1.Author();
    a1.display();
    a1.calculate();
    
    // Конструктор по умолчанию
    cout << "\n=== Создание B по умолчанию ===";
    B b1;
    b1.display();
    b1.calculate();
    b1.display();
    
    // Конструктор копирования
    cout << "\n=== Создание C копированием ===";
    C c1(8);
    c1.display();
    C c2 = c1;
    c2.display();
    
    // Демонстрация приведения вверх (указатели на базовый класс)
    cout << "\n=== Демонстрация полиморфизма ===";
    
    ptr1 = &a1;
    ptr1->calculate();
    
    ptr2 = &b1;
    ptr2->calculate();
    
    ptr3 = &c1;
    // Для класса C нужно передать R
    cout << endl << "Введите R: ";
    int r;
    cin >> r;
    c1.calculate(r);
    c1.display();
    
    // Демонстрация оператора присваивания
    cout << "\n=== Демонстрация оператора присваивания ===";
    A a2;
    a2 = a1;
    a2.display();
    
    return 0;
}
