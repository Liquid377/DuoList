/*
Вариант 3
1.) Составить программу, которая содержит текущую информацию об
успеваемости студентов.
Сведения о студентах включают:
• фамилия и инициалы;
• номер группы;
• успеваемость (массив из пяти элементов).
2.) Программа должна обеспечивать:
• хранение сведений обо всех студентах в виде двусвязного списка, записи
должны быть упорядочены по алфавиту;
• добавление данных о новых студентах;
• удаление данных о студенте, фамилия которого введена с клавиатуры;
• вывод сведений обо всех студентах;
• по запросу выводятся сведения о студентах, которые имеют хотя бы одну
оценку 2.
3.) Программа должна обеспечивать диалог с помощью меню.
*/

#include <iostream>
#include <string>
#include <vector>
#include "students.h"
#include "Windows.h"
#include <fstream>

#define pause system("pause")
#define clr system("cls")


using namespace std;

int Menu() {
    int i;
    cout << "1. Добавление нового студента." << endl;
    cout << "2. Вывод информации о всех студентах." << endl;
    cout << "3. Удаление данных о студенте, фамилия которого введена с клавиатуры." << endl;
    cout << "4. Вывод информации о студентах, имеющих хотя бы одну двойку." << endl;
    cout << "5. Сортировка по алфавиту по фамилии." << endl;
    cout << "6. Чтение из файла." << endl;
    cout << "7. Запись в файл" << endl;
    cout << "8. Справка." << endl;
    cout << "9. О программе." << endl;
    cout << "0. Выход." << endl;
    cout << "Введите пункт меню: ";
    cin >> i;
    return i;
}

Students _Students;

void ReadFromFile() {
    string name, group, grade; vector<int> grades;
    string grad;
    ifstream f("input.txt");
    if (f) {
        while (!f.eof()) {
            grad = "";
            getline(f, name);
            getline(f, group);
            getline(f, grade);
            grad += grade;
            grades.push_back(stoi(grade));
            getline(f, grade);
            grad += grade;
            grades.push_back(stoi(grade));
            getline(f, grade);
            grad += grade;
            grades.push_back(stoi(grade));
            getline(f, grade);
            grad += grade;
            grades.push_back(stoi(grade));
            getline(f, grade);
            grad += grade;
            grades.push_back(stoi(grade));
            _Students.Add(name, group, grades);
            cout << "Ученик добавлен в список." << endl;
            grades.clear();
        }
    }
    else {
        cout << "Файла не существует или файл пуст." << endl;
    }
    f.close();
}

void WriteToFile() {
    ofstream f("output.txt");
    if (f) {
        string grad;
        Student* OutputStudent = _Students.GetFirst();
        f << "Ученики: " << endl << endl;
        for (int i = 0; i <= _Students.GetCount() - 1; i++) {
            grad = "";
            string name; string group; vector<int> grades; double mdgrade;
            _Students.Get(OutputStudent, name, group, grades, mdgrade);
            for (int i = 0; i < grades.size(); i++) {
                grad = grad + " " + to_string(grades[i]);
            }
            f << "ФИО: " << name << endl << "Группа: " << group << endl << "Средний балл: " << mdgrade << endl << "Оценки: " << grad << endl << endl;
            OutputStudent = _Students.GoNext(OutputStudent);
        }
    }
    else {
        cout << "Файла не существует или файл пуст." << endl;
    }
    cout << "Результаты записаны в файл" << endl;
    f.close();
}

void Delete() {
    string name;
    bool del;
    cout << "Введите фамилию и инициалы ученика, которого желаете удалить: ";
    cin.get(); getline(cin, name);
    del = _Students.Del(name);
    if (del == true) {
        cout << "Ученик удален." << endl;
    }
}

void FindGrades2() {
    string grad;
    Student* OutputStudent = _Students.GetFirst();
    for (int i = 0; i <= _Students.GetCount() - 1; i++) {
        grad = "";
        string name; string group; vector<int> grades; double mdgrade;
        _Students.Get(OutputStudent, name, group, grades, mdgrade);
        for (int i = 0; i < grades.size(); i++) {
            grad = grad + " " + to_string(grades[i]);
        }
        if (grad.find("2") != std::string::npos)
        {
            cout << "ФИО: " << name << endl << "Группа: " << group << endl << "Средний балл: " << mdgrade << endl << "Оценки: " << grad << endl << endl;
        }
        OutputStudent = _Students.GoNext(OutputStudent);
    }
}

void Input() {
    string name, group; vector<int> grades;
    int grade;
    cout << "Введите фамилию и инициалы ученика: ";
    cin.get(); getline(cin, name);
    cout << "Введите номер группы ученика: ";
    getline(cin, group);
    for (int i = 0; i < 5; i++) {
        cout << "Введите успеваемость по предмету номер " << i + 1 << ": ";
        cin >> grade;
        grades.push_back(grade);
    }
    _Students.Add(name, group, grades);

}

void Output() {
    string grad, chooseorder;
    cout << "Введите в каком порядке вывести(1-Прямой/2-Обратный): ";
    cin.get(); getline(cin, chooseorder);
    if (chooseorder == "1")
    {
        Student* OutputStudent = _Students.GetFirst();
        for (int i = 0; i <= _Students.GetCount() - 1; i++) {
            grad = "";
            string name; string group; vector<int> grades; double mdgrade;
            _Students.Get(OutputStudent, name, group, grades, mdgrade);
            for (int i = 0; i < grades.size(); i++) {
                grad = grad + " " + to_string(grades[i]);
            }
            cout << "ФИО: " << name << endl << "Группа: " << group << endl << "Средний балл: " << mdgrade << endl << "Оценки: " << grad << endl << endl;
            OutputStudent = _Students.GoNext(OutputStudent);
        }
    }
    else {
        Student* OutputStudent = _Students.GetFirst();
        for (int i = 0; i < _Students.GetCount() - 1; i++)
            OutputStudent = _Students.GoNext(OutputStudent);
        for (int i = 0; i <= _Students.GetCount() - 1; i++) {
            grad = "";
            string name; string group; vector<int> grades; double mdgrade;
            _Students.Get(OutputStudent, name, group, grades, mdgrade);
            for (int i = 0; i < grades.size(); i++) {
                grad = grad + " " + to_string(grades[i]);
            }
            cout << "ФИО: " << name << endl << "Группа: " << group << endl << "Средний балл: " << mdgrade << endl << "Оценки: " << grad << endl << endl;
            OutputStudent = _Students.GoPrev(OutputStudent);
        }
    }
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Student* _Student;
    int iM;
    do {
        clr;
        iM = Menu();
        switch (iM)
        {
            case 1:
                clr;
                Input();
                break;
            case 2:
                clr;
                Output();
                pause;
                break;
            case 3:
                clr;
                Delete();
                pause;
                break;
            case 4:
                clr;
                FindGrades2();
                pause;
                break;
            case 5: 
                clr;
                _Students.Sort();
                pause;
                break;
            case 6:
                clr;
                ReadFromFile();
                pause;
                break;
            case 7:
                clr;
                WriteToFile();
                pause;
                break;
            case 8:
                clr;
                cout << "Вариант 3" << endl;
                cout << "1.) Составить программу, которая содержит текущую информацию об" << endl
                << "успеваемости студентов." << endl
                << "Сведения о студентах включают :" << endl
                << "• фамилия и инициалы;" << endl
                << "• номер группы;" << endl
                << "• успеваемость(массив из пяти элементов)." << endl
                << "2.) Программа должна обеспечивать :" << endl
                << "• хранение сведений обо всех студентах в виде двусвязного списка, записи" << endl
                << "должны быть упорядочены по алфавиту;"
                << "• добавление данных о новых студентах;" << endl
                << " • удаление данных о студенте, фамилия которого введена с клавиатуры; " << endl
                << "• вывод сведений обо всех студентах;" << endl
                << "• по запросу выводятся сведения о студентах, которые имеют хотя бы одну" << endl
                << " оценку 2." << endl
                << "3.) Программа должна обеспечивать диалог с помощью меню." << endl;
                pause;
                break;
            case 9:
                clr;
                cout << "Программа: Двусвязный список" << endl
                    << "Версия : 1.0" << endl
                    << "Год : 2023" << endl
                    << "Разработчик : Орлова Е.И." << endl
                    << "Группа : ИНБб - 1301" << endl;
                pause;
                break;
            case 0:
                _Students.clear();
        }
    } while (iM != 0);
}



