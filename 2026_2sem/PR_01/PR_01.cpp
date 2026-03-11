#include <iostream>
#include <windows.h>
#include <stdio.h>
#include "DinoBaraClass.h"

using namespace std;

void write2file(DinoBaraClass* dMas) {
    FILE* textFile;
    fopen_s(&textFile, "tetFile.txt", "w+");
    if (textFile) {
        int size = dMas->getSize();
        for (int i = 0; i < size; i++)
            fprintf(textFile, "%d %\n", dMas->getElement(i));
        fclose(textFile);
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    
    DinoBaraClass array1(6);
    DinoBaraClass array2(6);
    
    array1.setElement(0, 20);
    array1.setElement(1, 15);
    array1.setElement(2, 30);
    array1.setElement(3, 25);
    array1.setElement(4, 40);
    array1.setElement(5, 35);
    
    array2.setElement(0, 5);
    array2.setElement(1, 3);
    array2.setElement(2, 6);
    array2.setElement(3, 5);
    array2.setElement(4, 8);
    array2.setElement(5, 7);
    
    array1.display();
    array2.display();
    
    DinoBaraClass array3 = array1;
    array3 / array2;
    array3.display();
    
    DinoBaraClass compArray1(4);
    DinoBaraClass compArray2(4);
    
    compArray1.setElement(0, 10);
    compArray1.setElement(1, 50);
    compArray1.setElement(2, 30);
    compArray1.setElement(3, 20);
    
    compArray2.setElement(0, 45);
    compArray2.setElement(1, 25);
    compArray2.setElement(2, 35);
    compArray2.setElement(3, 15);
    
    compArray1.display();
    compArray2.display();
    
    bool result1 = compArray1 > compArray2;
    
    DinoBaraClass compArray3(4);
    DinoBaraClass compArray4(4);
    
    compArray3.setElement(0, 15);
    compArray3.setElement(1, 25);
    compArray3.setElement(2, 75);
    compArray3.setElement(3, 35);
    
    compArray4.setElement(0, 80);
    compArray4.setElement(1, 20);
    compArray4.setElement(2, 40);
    compArray4.setElement(3, 60);
    
    compArray3.display();
    compArray4.display();
    
    bool result2 = compArray3 > compArray4;
    
    DinoBaraClass sortArray(8);
    sortArray.setElement(0, 45);
    sortArray.setElement(1, 12);
    sortArray.setElement(2, 78);
    sortArray.setElement(3, 23);
    sortArray.setElement(4, 56);
    sortArray.setElement(5, 89);
    sortArray.setElement(6, 34);
    sortArray.setElement(7, 67);
    
    sortArray.display();
    ~sortArray;
    sortArray.display();
    
    write2file(&sortArray);
    
    DinoBaraClass copyArray = sortArray;
    copyArray.display();
    
    DinoBaraClass assignArray;
    assignArray = sortArray;
    assignArray.display();
    
    return 0;
}
```
