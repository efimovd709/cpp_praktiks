#include "initial_data.h"
#include <windows.h>
#include <fstream>
#include <string>

using namespace std;

// ==================== КЛАСС STUDENTSLIST ====================

class StudentsList
{
private:
    Node* first;
    Node* last;
    int countItem;

public:
    // Конструкторы и деструктор
    StudentsList()
    {
        first = nullptr;
        last = nullptr;
        countItem = 0;
    }

    // Конструктор копирования
    StudentsList(const StudentsList& other)
    {
        first = nullptr;
        last = nullptr;
        countItem = 0;

        Node* current = other.first;
        while (current)
        {
            Student* newStudent = new Student();
            *newStudent = *(current->item);
            addItemBack(newStudent);
            current = current->next;
        }
    }

    // Деструктор
    ~StudentsList()
    {
        Node* current = first;
        while (current)
        {
            Node* temp = current;
            current = current->next;
            delete temp->item;
            delete temp;
        }
        first = last = nullptr;
        countItem = 0;
    }

    // Перегрузка оператора присваивания
    StudentsList& operator=(const StudentsList& other)
    {
        if (this == &other) return *this;

        this->~StudentsList();

        first = nullptr;
        last = nullptr;
        countItem = 0;

        Node* current = other.first;
        while (current)
        {
            Student* newStudent = new Student();
            *newStudent = *(current->item);
            addItemBack(newStudent);
            current = current->next;
        }
        return *this;
    }

    // Перегрузка оператора вывода
    friend ostream& operator<<(ostream& os, const StudentsList& list)
    {
        Node* current = list.first;
        int index = 1;
        while (current)
        {
            os << "\n=== Студент " << index++ << " ===" << endl;
            os << "Номер билета: " << current->item->number << endl;
            os << "Фамилия: " << current->item->first_name << endl;
            os << "Дата рождения: " << current->item->birth_day << endl;
            os << "Группа: " << current->item->group << endl;
            os << "Средний балл: " << current->item->avg_mark << endl;
            os << "Оценки:" << endl;
            for (size_t i = 0; i < current->item->results.size(); i++)
            {
                os << "  - " << current->item->results[i].subject
                   << " | " << current->item->results[i].date
                   << " | " << current->item->results[i].mark << endl;
            }
            current = current->next;
        }
        return os;
    }

    // ========== ОПЕРАЦИИ СО СПИСКОМ (ВАРИАНТ 8) ==========
    
    // 1. Добавление узла по указанному индексу
    void addItemAtIndex(int index, Student* data)
    {
        if (index < 0 || index > countItem)
        {
            cout << "Ошибка: неверный индекс!" << endl;
            return;
        }

        Node* newItem = new Node();
        newItem->item = data;
        newItem->next = nullptr;

        if (index == 0)
        {
            // Вставка в начало
            newItem->next = first;
            first = newItem;
            if (countItem == 0) last = newItem;
        }
        else if (index == countItem)
        {
            // Вставка в конец
            if (last) last->next = newItem;
            last = newItem;
            if (countItem == 0) first = newItem;
        }
        else
        {
            // Вставка в середину
            Node* current = first;
            for (int i = 0; i < index - 1; i++)
                current = current->next;
            newItem->next = current->next;
            current->next = newItem;
        }
        countItem++;
        cout << "Студент добавлен на позицию " << index << endl;
    }

    // 2. Удаление узла в конце списка
    void deleteLastItem()
    {
        if (countItem == 0)
        {
            cout << "Список пуст, нечего удалять!" << endl;
            return;
        }

        if (countItem == 1)
        {
            delete first->item;
            delete first;
            first = nullptr;
            last = nullptr;
        }
        else
        {
            Node* current = first;
            while (current->next != last)
                current = current->next;
            
            delete last->item;
            delete last;
            last = current;
            last->next = nullptr;
        }
        countItem--;
        cout << "Последний студент удалён." << endl;
    }

    // ========== ПОИСКОВАЯ ОПЕРАЦИЯ (ВАРИАНТ 8) ==========
    // Поиск узлов по номеру группы (возвращает новый список)
    StudentsList* searchByGroup(const string& group)
    {
        StudentsList* result = new StudentsList();
        Node* current = first;

        while (current)
        {
            if (current->item->group == group)
            {
                Student* newStudent = new Student();
                *newStudent = *(current->item);
                result->addItemBack(newStudent);
            }
            current = current->next;
        }
        return result;
    }

    // ========== РАСЧЁТНАЯ ОПЕРАЦИЯ (ВАРИАНТ 8) ==========
    // Расчёт количества студентов, обучающихся на "хорошо" и "отлично" (оценки 4 и 5)
    int countGoodAndExcellentStudents()
    {
        int count = 0;
        Node* current = first;

        while (current)
        {
            bool isGoodOrExcellent = true;
            for (size_t i = 0; i < current->item->results.size(); i++)
            {
                if (current->item->results[i].mark < 4)
                {
                    isGoodOrExcellent = false;
                    break;
                }
            }
            if (isGoodOrExcellent && current->item->results.size() > 0)
                count++;
            current = current->next;
        }
        return count;
    }

    // ========== ОСТАЛЬНЫЕ МЕТОДЫ (ВАШИ, СОХРАНЁННЫЕ) ==========

    void addItemBack(Student* data)
    {
        Node* newItem = new Node();
        newItem->item = data;
        newItem->next = nullptr;

        if (countItem == 0)
        {
            first = newItem;
            last = newItem;
        }
        else
        {
            last->next = newItem;
            last = newItem;
        }
        countItem++;
    }

    void addFromKeyboard()
    {
        Student* newStudent = new Student();
        Grade grade;

        cout << "\n=== Ввод данных студента ===" << endl;
        cout << "Номер студенческого билета: ";
        cin >> newStudent->number;
        cin.ignore();
        cout << "Фамилия: ";
        getline(cin, newStudent->first_name);
        cout << "Дата рождения (ДД/ММ/ГГГГ): ";
        getline(cin, newStudent->birth_day);
        cout << "Номер группы: ";
        getline(cin, newStudent->group);

        int gradeCount;
        cout << "Количество оценок: ";
        cin >> gradeCount;
        cin.ignore();

        for (int i = 0; i < gradeCount; i++)
        {
            cout << "\nОценка " << i + 1 << ":" << endl;
            cout << "  Дисциплина: ";
            getline(cin, grade.subject);
            cout << "  Дата (ДД/ММ/ГГГГ): ";
            getline(cin, grade.date);
            cout << "  Оценка (2-5): ";
            cin >> grade.mark;
            cin.ignore();
            newStudent->results.push_back(grade);
        }

        float sum = 0;
        for (size_t i = 0; i < newStudent->results.size(); i++)
            sum += newStudent->results[i].mark;
        newStudent->avg_mark = (newStudent->results.size() > 0) ? sum / newStudent->results.size() : 0;

        addItemBack(newStudent);
        cout << "\nСтудент успешно добавлен в КОНЕЦ списка!" << endl;
    }

    void loadData()
    {
        ifstream studTextFile("studTextFile.txt");
        ifstream indexStudTextFile("indexStudTextFile.txt");
        ifstream gradesTextFile("gradesTextFile.txt");

        if (!studTextFile.is_open() || !indexStudTextFile.is_open() || !gradesTextFile.is_open())
        {
            cerr << "Ошибка: не удалось открыть файлы данных!" << endl;
            return;
        }

        string line;
        while (getline(studTextFile, line))
        {
            Student* tmpSt = new Student();
            tmpSt->number = line;
            getline(studTextFile, line);
            tmpSt->first_name = line;
            getline(studTextFile, line);
            tmpSt->birth_day = line;
            getline(studTextFile, line);
            tmpSt->group = line;

            getline(indexStudTextFile, line);
            getline(indexStudTextFile, line);
            int countGrade = atoi(line.c_str());

            for (int i = 0; i < countGrade; i++)
            {
                Grade gr;
                getline(gradesTextFile, line);
                gr.subject = line;
                getline(gradesTextFile, line);
                gr.date = line;
                getline(gradesTextFile, line);
                gr.mark = atoi(line.c_str());
                tmpSt->results.push_back(gr);
            }

            float sum = 0;
            for (size_t i = 0; i < tmpSt->results.size(); i++)
                sum += tmpSt->results[i].mark;
            tmpSt->avg_mark = (tmpSt->results.size() > 0) ? sum / tmpSt->results.size() : 0;

            addItemBack(tmpSt);
        }

        studTextFile.close();
        indexStudTextFile.close();
        gradesTextFile.close();
        cout << "Загружено " << countItem << " студентов." << endl;
    }

    void saveData()
    {
        Node* current = first;
        int numStud = 0;

        FILE* studTextFile;
        fopen_s(&studTextFile, "studTextFile.txt", "w");
        FILE* indexStudTextFile;
        fopen_s(&indexStudTextFile, "indexStudTextFile.txt", "w");
        FILE* gradesTextFile;
        fopen_s(&gradesTextFile, "gradesTextFile.txt", "w");

        while (current)
        {
            fprintf(studTextFile, "%s\n%s\n%s\n%s\n",
                current->item->number.c_str(),
                current->item->first_name.c_str(),
                current->item->birth_day.c_str(),
                current->item->group.c_str());

            numStud++;
            int countGrade = current->item->results.size();
            fprintf(indexStudTextFile, "%d\n%d\n", numStud, countGrade);

            for (int i = 0; i < countGrade; i++)
            {
                fprintf(gradesTextFile, "%s\n%s\n%d\n",
                    current->item->results[i].subject.c_str(),
                    current->item->results[i].date.c_str(),
                    current->item->results[i].mark);
            }
            current = current->next;
        }

        fclose(studTextFile);
        fclose(indexStudTextFile);
        fclose(gradesTextFile);
        cout << "Список сохранён в файлы." << endl;
    }

    void display()
    {
        if (countItem == 0)
        {
            cout << "\nСписок пуст!" << endl;
            return;
        }

        Node* current = first;
        int index = 1;
        while (current)
        {
            cout << "\n=== Студент " << index++ << " ===" << endl;
            cout << "Номер билета: " << current->item->number << endl;
            cout << "Фамилия: " << current->item->first_name << endl;
            cout << "Дата рождения: " << current->item->birth_day << endl;
            cout << "Группа: " << current->item->group << endl;
            cout << "Средний балл: " << current->item->avg_mark << endl;
            cout << "Оценки:" << endl;
            for (size_t i = 0; i < current->item->results.size(); i++)
            {
                cout << "  - " << current->item->results[i].subject
                    << " | " << current->item->results[i].date
                    << " | " << current->item->results[i].mark << endl;
            }
            current = current->next;
        }
        cout << "\nВсего студентов: " << countItem << endl;
    }

    void deleteItem(int index)
    {
        if (index < 0 || index >= countItem || countItem == 0) return;

        Node* toDelete = nullptr;

        if (index == 0)
        {
            toDelete = first;
            first = first->next;
            if (countItem == 1) last = nullptr;
        }
        else
        {
            Node* current = first;
            for (int i = 0; i < index - 1; i++)
                current = current->next;
            toDelete = current->next;
            current->next = toDelete->next;
            if (toDelete == last) last = current;
        }

        delete toDelete->item;
        delete toDelete;
        countItem--;
    }

    void calcAvgMark()
    {
        Node* current = first;
        while (current)
        {
            float sum = 0;
            for (size_t i = 0; i < current->item->results.size(); i++)
                sum += current->item->results[i].mark;
            current->item->avg_mark = (current->item->results.size() > 0) ? sum / current->item->results.size() : 0;
            current = current->next;
        }
    }

    int getCount() const { return countItem; }
};

// ==================== MAIN ====================

int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "========================================" << endl;
    cout << "Практическая работа №4" << endl;
    cout << "Вариант 8" << endl;
    cout << "Студент: Русаков Алексей БИСО-01-25" << endl;
    cout << "========================================" << endl;

    StudentsList list;

    // 1. Загрузка данных из файлов
    cout << "\n--- Загрузка данных из файлов ---" << endl;
    list.loadData();
    list.calcAvgMark();
    list.display();

    // 2. Демонстрация конструктора копирования
    cout << "\n--- Демонстрация конструктора копирования ---" << endl;
    StudentsList copiedList(list);
    copiedList.display();

    // 3. Демонстрация оператора присваивания
    cout << "\n--- Демонстрация оператора присваивания ---" << endl;
    StudentsList assignedList;
    assignedList = list;
    assignedList.display();

    // 4. Добавление узла с клавиатуры
    cout << "\n--- Добавление студента с клавиатуры ---" << endl;
    list.addFromKeyboard();
    list.display();

    // 5. Операция 1: добавление узла по указанному индексу
    cout << "\n--- Добавление узла по указанному индексу ---" << endl;
    Student* newStudent = new Student();
    newStudent->number = "0999";
    newStudent->first_name = "Тестовый Студент";
    newStudent->birth_day = "01/01/2000";
    newStudent->group = "ТЕСТ-00-00";
    newStudent->avg_mark = 5.0;
    int index;
    cout << "Введите индекс для вставки (0-" << list.getCount() << "): ";
    cin >> index;
    list.addItemAtIndex(index, newStudent);
    list.display();

    // 6. Операция 2: удаление узла в конце списка
    cout << "\n--- Удаление узла в конце списка ---" << endl;
    list.deleteLastItem();
    list.display();

    // 7. Поисковая операция: поиск по номеру группы
    cout << "\n--- Поисковая операция (поиск по номеру группы) ---" << endl;
    string searchGroup;
    cout << "Введите номер группы для поиска: ";
    cin.ignore();
    getline(cin, searchGroup);
    StudentsList* searchResult = list.searchByGroup(searchGroup);
    cout << "\nСтуденты из группы \"" << searchGroup << "\":" << endl;
    searchResult->display();
    cout << "Найдено студентов: " << searchResult->getCount() << endl;

    // 8. Расчётная операция: количество студентов на "хорошо" и "отлично"
    cout << "\n--- Расчётная операция (студенты на 'хорошо' и 'отлично') ---" << endl;
    int goodCount = list.countGoodAndExcellentStudents();
    cout << "Количество студентов, обучающихся на 'хорошо' и 'отлично' (все оценки 4 или 5): " << goodCount << endl;

    // 9. Сохранение данных
    cout << "\n--- Сохранение данных ---" << endl;
    list.saveData();

    // 10. Вывод через перегруженный оператор <<
    cout << "\n--- Вывод через перегруженный оператор << ---" << endl;
    cout << list;

    delete searchResult;

    cout << "\nПрограмма завершена!" << endl;
    system("pause");
    return 0;
}
