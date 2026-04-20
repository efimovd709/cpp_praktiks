#include <iostream>
#include <windows.h>
#include "CapyStringHandle.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    
    cout << "========================================" << endl;
    cout << "Практическая работа 3 - Вариант 8" << endl;
    cout << "========================================" << endl << endl;
    
    // 1. Демонстрация конструктора по умолчанию
    cout << "1. Демонстрация конструктора по умолчанию:" << endl;
    CapyStringHandle sh1;
    cout << sh1 << endl << endl;
    
    // 2. Чтение исходной строки из файла
    cout << "2. Чтение исходной строки из файла 'data.txt':" << endl;
    sh1.ReadFromFile("data.txt");
    
    // 3. Вывод исходной строки
    sh1.display();
    cout << endl;
    
    // 4. Извлечение слов из строки
    cout << "3. Извлечение слов из исходной строки:" << endl;
    sh1.extractWords();
    sh1.wordsCount();
    cout << endl;
    
    // 5. Демонстрация конструктора копирования
    cout << "4. Демонстрация конструктора копирования:" << endl;
    CapyStringHandle sh2(sh1);
    cout << "Копия объекта: " << sh2 << endl << endl;
    
    // 6. Демонстрация операции присваивания
    cout << "5. Демонстрация операции присваивания:" << endl;
    CapyStringHandle sh3;
    sh3 = sh1;
    cout << "Присвоенный объект: " << sh3 << endl << endl;
    
    // 7. ВАРИАНТ 8: Сортировка слов по возрастанию длины
    cout << "6. ВАРИАНТ 8: Упорядочивание слов по возрастанию их длины" << endl;
    sh1.sortWordsByLength();
    sh1.displaySortedString();
    cout << endl;
    
    // 8. Запись результатов в файл decision.txt
    cout << "7. Запись результатов в файл 'decision.txt':" << endl;
    sh1.WriteToFile("decision.txt");
    
    // 9. Демонстрация перегруженной операции вывода
    cout << "\n8. Демонстрация перегруженной операции вывода:" << endl;
    cout << "Содержимое объекта sh1: " << sh1 << endl;
    
    cout << "\n========================================" << endl;
    cout << "Программа завершена успешно!" << endl;
    cout << "========================================" << endl;
    
    return 0;
}
