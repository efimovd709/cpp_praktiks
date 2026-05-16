#pragma once
#include <vector> 
#include <string> 
#include <iostream>

using namespace std;

struct Grade // структура "успеваемость"
{
    string subject;     // учебная дисциплина
    string date;        // дата получения оценки
    int mark;           // оценка
};

struct Student // структура "студент"
{
    string number;      // номер студ. билета
    string first_name;  // фамилия студента
    string birth_day;   // дата рождения студента
    string group;       // номер группы
    vector<Grade> results; // результаты успеваемости
    float avg_mark;
};

struct Node // структура "узел списка"
{
    Student* item;  // данные узла
    Node* next;     // указатель на следующий узел списка
};
