#pragma once
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <ctime>

using namespace std;

class DinoBaraVirtClass
{
protected:
	int* data;
	int size;
public:
	DinoBaraVirtClass() {
		size = 17;
		data = new int[size];
		srand(time(nullptr));
		for (int i = 0; i < size; i++) {
			data[i] = rand() % 201 - 100;
		}
	};
	DinoBaraVirtClass(int _size) {
		if (_size > 0) {
			size = _size;
			data = new int[size];
			srand(time(nullptr));
			for (int i = 0; i < size; i++) {
				data[i] = rand() % 201 - 100;
			}
		}
	};
	~DinoBaraVirtClass() {
		delete[] data;
	};
	void display() {
		cout << endl << "Display: ";
		for (int i = 0; i < size; i++) {
			cout << " " << data[i];
		}
		cout << endl;
	}
	void Author() {
		cout << "\nЕфимов Данила Владимирович, БИСО-02-25, Вариант 8\n";
	}
	DinoBaraVirtClass(const DinoBaraVirtClass& other) {
		cout << "DinoBaraVirtClass(const DinoBaraVirtClass & other) " << endl;
		size = other.size;
		data = new int[size];
		for (int i = 0; i < size; i++) {
			data[i] = other.data[i];
		}
	}
	DinoBaraVirtClass& operator=(const DinoBaraVirtClass& other) {
		cout << "operator= " << endl;
		if (this != &other) {
			delete[] data;
			size = other.size;
			data = new int[size];
			for (int i = 0; i < size; i++) {
				data[i] = other.data[i];
			}
		}
		return *this;
	}
	virtual void calculate() = 0;
	virtual void calculate(int r) {};
};

class A : public DinoBaraVirtClass
{
public:
	A() : DinoBaraVirtClass() {}
	A(int _size) : DinoBaraVirtClass(_size) {}
	A(const A& other) : DinoBaraVirtClass(other) {}
	~A() {}
	A& operator=(const A& other) {
		if (this != &other) {
			DinoBaraVirtClass::operator=(other);
		}
		return *this;
	}
	void calculate() override {
		cout << endl << "=== Задание 1: Количество отрицательных элементов ===";
		int count = 0;
		for (int i = 0; i < size; i++) {
			if (data[i] < 0) count++;
		}
		cout << endl << "Количество отрицательных элементов: " << count << endl;
	}
};

class B : public DinoBaraVirtClass
{
public:
	B() : DinoBaraVirtClass() {}
	B(int _size) : DinoBaraVirtClass(_size) {}
	B(const B& other) : DinoBaraVirtClass(other) {}
	~B() {}
	B& operator=(const B& other) {
		if (this != &other) {
			DinoBaraVirtClass::operator=(other);
		}
		return *this;
	}
	void calculate() override {
		cout << endl << "=== Задание 2: Сумма элементов после последнего отрицательного ===";
		int lastNegativeIndex = -1;
		for (int i = 0; i < size; i++) {
			if (data[i] < 0) lastNegativeIndex = i;
		}
		int sum = 0;
		if (lastNegativeIndex != -1) {
			for (int i = lastNegativeIndex + 1; i < size; i++) {
				sum += data[i];
			}
		}
		cout << endl << "Сумма элементов после последнего отрицательного: " << sum << endl;
	}
};

class C : public DinoBaraVirtClass
{
public:
	C() : DinoBaraVirtClass() {}
	C(int _size) : DinoBaraVirtClass(_size) {}
	C(const C& other) : DinoBaraVirtClass(other) {}
	~C() {}
	C& operator=(const C& other) {
		if (this != &other) {
			DinoBaraVirtClass::operator=(other);
		}
		return *this;
	}
	void calculate(int r) override {
		cout << endl << "=== Задание 3: Преобразование массива (не превышает R <= остальные) ===";
		cout << endl << "R = " << r;
		int* temp = new int[size];
		int index = 0;
		for (int i = 0; i < size; i++) {
			if (data[i] <= r) {
				temp[index++] = data[i];
			}
		}
		for (int i = 0; i < size; i++) {
			if (data[i] > r) {
				temp[index++] = data[i];
			}
		}
		for (int i = 0; i < size; i++) {
			data[i] = temp[i];
		}
		delete[] temp;
		cout << endl << "Массив преобразован" << endl;
	}
	void calculate() override {}
};
