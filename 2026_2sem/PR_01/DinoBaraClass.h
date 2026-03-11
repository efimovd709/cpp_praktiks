#pragma once
#include <iostream>
#include <windows.h>
#include <stdio.h>

// Вариант 8
// Выполнил: Ефимов Данила
// Группа: БИСО-02-25
using namespace std;

struct node {
    int data;
    node* next;
};

class DinoBaraClass
{
private:
    node* head;
    int count;
public:
    DinoBaraClass() {
        head = nullptr;
        count = 0;
    };
    DinoBaraClass(int _size) {
        head = nullptr;
        count = 0;
        for (int i = 0; i < _size; i++)
            addElementFront(genNum());
    };
    DinoBaraClass(DinoBaraClass& _other)
    {
        head = nullptr;
        count = 0;
        for (int i = 0; i < _other.count; i++)
            addElementRear(_other.getElement(i));
    }
    ~DinoBaraClass() {
        node* current = head;
        node* prev = nullptr;
        while (current) {
            prev = current;
            current = current->next;
            delete prev;
        }
    };
    void author() {
        cout << endl << "Русаков А.М.";
    }
    int genNum() {
        int rangeMin = -101;
        int rangeMax = 101;
        double r = rand();
        int num = ((double)r / RAND_MAX) * (rangeMax - rangeMin) + rangeMin;
        return num;
    };
    void addElementFront(int data)
    {
        if (count == 0) {
            head = new node;
            head->data = data;
            head->next = nullptr;
        }
        else {
            node* tmpPoint = head;
            head = new node;
            head->next = tmpPoint;
            head->data = data;
        }
        count++;
    }
    void addElementRear(int _data) {
        if (count == 0) {
            head = new node;
            head->data = _data;
            head->next = nullptr;
        }
        else {
            node* current = head;
            node* prev = nullptr;
            while (current) {
                prev = current;
                current = current->next;
            }
            node* tmpNode = new node;
            tmpNode->next = nullptr;
            tmpNode->data = _data;
            prev->next = tmpNode;
        }
        count++;
    }
    void insertElement(int pos, int data) {
        if (count > 0)
            if ((pos >= 0) and (pos <= count))
            {
                if (pos == 0) {
                    addElementFront(data);
                }
                if ((pos > 0) and (pos < count)) {
                    int ind = 0;
                    node* current = head;
                    node* prev = nullptr;
                    while (current) {
                        if (ind == pos) {
                            node* tmpPoint = new node;
                            tmpPoint->next = current;
                            tmpPoint->data = data;
                            prev->next = tmpPoint;
                            break;
                        }
                        prev = current;
                        current = current->next;
                        ind++;
                    }
                    count++;
                }
                if (pos == count) {
                    addElementRear(data);
                }
            }
    }
    void setElement(int pos, int data) {
        if (count > 0)
            if ((pos >= 0) and (pos < count))
            {
                node* current = head;
                int ind = 0;
                while (current) {
                    if (ind == pos)
                        current->data = data;
                    current = current->next;
                    ind++;
                }
            }
    }
    int getElement(int _pos)
    {
        int element = -1;
        if (count > 0)
            if ((_pos >= 0) and (_pos < count))
            {
                node* current = head;
                int ind = 0;
                while (current) {
                    if (ind == _pos)
                    {
                        element = current->data;
                        break;
                    }
                    current = current->next;
                    ind++;
                }
            }
        return element;
    }
    void delElement(int _pos) {
        if (count > 0)
            if ((_pos >= 0) and (_pos < count))
            {
                int ind = 0;
                node* current = head;
                node* prev = nullptr;
                if (count > 1)
                    while (current) {
                        if (ind == _pos) {
                            node* tmpPoint = current;
                            prev->next = current->next;
                            delete tmpPoint;
                            break;
                        }
                        prev = current;
                        current = current->next;
                        ind++;
                    }
                else {
                    delete head;
                    head = nullptr;
                }
                count--;
            }
    }
    void display() {
        node* current = head;
        cout << endl << "__Display";
        while (current) {
            cout << endl << current->data;
            current = current->next;
        }
    }
    int getSize() {
        return count;
    }
    bool operator=(const DinoBaraClass& _other)
    {
        node* current = this->head;
        node* prev = nullptr;
        while (current) {
            prev = current;
            current = current->next;
            delete prev;
        }
        this->count = 0;
        current = _other.head;
        while (current) {
            this->addElementRear(current->data);
            current = current->next;
        }
        return true;
    }
    DinoBaraClass operator/(DinoBaraClass& _other) {
        cout << endl << "Компонентная операция: поэлементное деление четных элементов";
        node* current = this->head;
        int index = 0;
        while (current) {
            if (index % 2 == 0) {
                int tmp = _other.getElement(index);
                if (tmp != 0) {
                    current->data = current->data / tmp;
                }
                else {
                    cout << endl << "Ошибка: деление на ноль в позиции " << index;
                }
            }
            current = current->next;
            index++;
        }
        return *this;
    }
    friend bool operator>(DinoBaraClass& _other1, DinoBaraClass& _other2);
    friend void operator~(DinoBaraClass& _other);
};

bool operator>(DinoBaraClass& _other1, DinoBaraClass& _other2) {
    int max1 = -2147483648;
    node* current = _other1.head;
    while (current) {
        if (current->data > max1) {
            max1 = current->data;
        }
        current = current->next;
    }
    int max2 = -2147483648;
    current = _other2.head;
    while (current) {
        if (current->data > max2) {
            max2 = current->data;
        }
        current = current->next;
    }
    cout << endl << "Дружественная операция: сравнение по максимуму";
    cout << endl << "Max1 = " << max1 << ", Max2 = " << max2;
    return max1 > max2;
}

void operator~(DinoBaraClass& _other) {
    cout << endl << "Глобальная операция: сортировка по убыванию";
    int n = _other.getSize();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (_other.getElement(j) < _other.getElement(j + 1)) {
                int tmp = _other.getElement(j);
                _other.setElement(j, _other.getElement(j + 1));
                _other.setElement(j + 1, tmp);
            }
        }
    }
}
