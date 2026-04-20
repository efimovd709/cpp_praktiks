#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

class CapyStringHandle
{
private:
	string originalString;
	vector<string> words;
public:
	// Конструктор по умолчанию - создает объект с пустой строкой
	CapyStringHandle() {
		originalString = "";
		words.clear();
	}
	
	// Конструктор копирования
	CapyStringHandle(const CapyStringHandle& other) {
		originalString = other.originalString;
		words = other.words;
	}
	
	// Перегруженная операция присваивания
	CapyStringHandle& operator=(const CapyStringHandle& other) {
		if (this != &other) {
			originalString = other.originalString;
			words = other.words;
		}
		return *this;
	}
	
	// Чтение исходной строки из текстового файла
	void ReadFromFile(const char* filename) {
		ifstream inFile(filename);
		if (inFile.is_open()) {
			getline(inFile, originalString);
			inFile.close();
			cout << "Файл \"" << filename << "\" успешно прочитан." << endl;
		}
		else {
			cout << "ERROR: Не удалось открыть файл " << filename << endl;
		}
	}
	
	// Вывод исходной строки на экран
	void display() {
		cout << "Исходная строка: " << originalString << endl;
	}
	
	// Извлечение слов из строки (разделитель - один или несколько пробелов)
	void extractWords() {
		istringstream iss(originalString);
		string word;
		words.clear();
		while (iss >> word) {
			words.push_back(word);
		}
		cout << "Извлечено слов: " << words.size() << endl;
	}
	
	// Вывод количества слов
	void wordsCount() {
		cout << "Количество слов в массиве: " << words.size() << endl;
	}
	
	// Вывод массива слов на экран
	void displayWords() {
		cout << "Массив слов из исходной строки:" << endl;
		for (size_t i = 0; i < words.size(); i++) {
			cout << "  " << i + 1 << ". \"" << words[i] << "\" (длина: " << words[i].length() << ")" << endl;
		}
	}
	
	// ВАРИАНТ 8: Упорядочить слова по возрастанию их длины
	void sortWordsByLength() {
		// Сортировка пузырьком по длине слов (от самых коротких к самым длинным)
		for (size_t i = 0; i < words.size() - 1; i++) {
			for (size_t j = 0; j < words.size() - i - 1; j++) {
				if (words[j].length() > words[j + 1].length()) {
					swap(words[j], words[j + 1]);
				}
			}
		}
		cout << "Слова отсортированы по возрастанию длины." << endl;
	}
	
	// Вывод строки из отсортированных слов
	void displaySortedString() {
		cout << "Строка из слов, упорядоченных по возрастанию длины:" << endl;
		for (size_t i = 0; i < words.size(); i++) {
			cout << words[i];
			if (i < words.size() - 1) cout << " ";
		}
		cout << endl;
	}
	
	// Запись результатов в файл decision.txt
	void WriteToFile(const char* filename) {
		FILE* file;
		errno_t err;
		err = fopen_s(&file, filename, "w");
		if (file != nullptr) {
			// 1) Исходная строка
			fprintf(file, "1) Исходная строка:\n");
			fprintf(file, "%s\n\n", originalString.c_str());
			
			// 2) Массив слов, выделенных из исходной строки
			fprintf(file, "2) Массив слов, выделенных из исходной строки:\n");
			for (size_t i = 0; i < words.size(); i++) {
				fprintf(file, "   %d. \"%s\" (длина: %zu символов)\n", 
					i + 1, words[i].c_str(), words[i].length());
			}
			fprintf(file, "\n");
			
			// 3) Реализация варианта 8 - слова, упорядоченные по возрастанию длины
			fprintf(file, "3) Результат выполнения варианта 8:\n");
			fprintf(file, "   Слова, упорядоченные по возрастанию их длины:\n   ");
			for (size_t i = 0; i < words.size(); i++) {
				fprintf(file, "%s", words[i].c_str());
				if (i < words.size() - 1) fprintf(file, " ");
			}
			fprintf(file, "\n");
			
			fclose(file);
			printf("\nРезультаты успешно записаны в файл \"%s\"\n", filename);
		}
		else {
			printf("\nERROR: Не удалось открыть файл %s для записи\n", filename);
		}
	}
	
	// Перегруженная операция вывода в поток
	friend ostream& operator<<(ostream& out, const CapyStringHandle& sp) {
		out << "Исходная строка: " << sp.originalString;
		return out;
	}
};
