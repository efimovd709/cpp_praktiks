#pragma once
#include "initial_data.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class StudentsList
{
private:
    Node* first;
    Node* last;
    int countItem;

public:
    // Конструкторы и деструктор
    StudentsList();
    StudentsList(const StudentsList& other);
    ~StudentsList();

    // Перегрузки операторов
    StudentsList& operator=(const StudentsList& other);
    friend ostream& operator<<(ostream& os, const StudentsList& list);

    // Работа с файлами (существующие форматы)
    void loadData();
    void saveData();

    // Операции со списком
    void addItemBack(Student* data);
    void addFromKeyboard();
    void display();
    int getCount() const { return countItem; }

    // Операции варианта 8
    StudentsList* searchByDate(const string& date);
    int countStudentsInGroup(const string& group);

    // Существующие методы
    void deleteItem(int index);
    void deleteItemAfterInd(int index);
    void deleteItemBeforeInd(int index);
    void insertItem(int index, Student* data);
    void editItem(int index, Student* data);
    void calcAvgMark();
};
