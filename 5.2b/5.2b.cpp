#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

enum Speciality { COMPUTER_SCIENCE, IT, MATH_ECONOMICS, PHYSICS_IT, HANDICRAFT };
string specialityStr[] = { "Комп'ютернi науки", "Iнформатика", "Матем. та економ.", "Фiзика та iнформ.", "Трудове  навчання" };

struct Student
{
    char surname[100];
    int course;
    Speciality speciality;
    int physics;
    int maths;
    union {
        int it;
        int numb;
        int ped;
    };
};

void ArithmeticMean(char* fname)
{
    ifstream f(fname, ios::binary & ios::beg);

    int a = 0, b = 0, c = 0;
    float markPhys = 0, markMaths = 0, markIT = 0, markNumb = 0, markPed = 0;
    int i = 0;
    Student worker;

    while (f.read((char*)&worker, sizeof(Student)))
    {
        markPhys += worker.physics;
        markMaths += worker.maths;

        if (worker.speciality == 0)
        {
            markIT += worker.it;
            a++;
        }
        else
            if (worker.speciality == 1)
            {
                markNumb += worker.numb;
                b++;
            }
            else
            {
                markPed += worker.ped;
                c++;
            }
        i++;
    }

    cout << "Середній бал з фізики: " << markPhys / i << endl;
    cout << "Середній бал з математики: " << markMaths / i << endl;
    cout << "Середній бал з програмування: " << markIT / a << endl;
    cout << "Середній бал з чисельних методів: " << markNumb / b << endl;
    cout << "Середній бал з педагогіки: " << markPed / c << endl;
}

int PhysicsFiveOrFour(char* fname)
{
    ifstream f(fname, ios::binary & ios::beg);

    int i = 0;
    Student worker;
    while (f.read((char*)&worker, sizeof(Student)))
    {
        if (worker.physics == 5 || worker.physics == 4)
            i++;
    }
    return i;
}

void enter_save(char* fname)
{
    int sp;
    ofstream f(fname, ios::binary);
    if (!f)
    {
        cerr << "Помилка відкриття файла '" << fname << "'" << endl;
        return;
    }
    Student worker;
    char ch;
    do
    {
        cout << endl;
        cout << "Прізвище: "; cin.sync();
        cin >> worker.surname;
        cout << "Курс: "; cin >> worker.course;
        cout << "Спецiальнiсть (0 - Комп'ютернi науки, 1 -  Iнформатика, 2 -  Математика та економiка, 3 -  Фiзика та iнформатика, 4 - Трудове навчання): ";
        cin >> sp;
        worker.speciality = static_cast<Speciality>(sp);
        cout << "Оцiнка з фiзики: ";
        cin >> worker.physics;
        cout << "Оцiнка з математики: ";
        cin >> worker.maths;
        if (worker.speciality == 0) {
            cout << "Оцiнка з програмування: ";
            cin >> worker.it;
        }
        else if (worker.speciality == 1) {
            cout << "Оцiнка з чисельних методiв: ";
            cin >> worker.numb;
        }
        else {
            cout << "Оцiнка з педагогiки: ";
            cin >> worker.ped;
        }
        if (!f.write((char*)&worker, sizeof(Student)))
        {
            cerr << "Помилка відкриття файлу." << endl;
        }
        cout << "Продовжити? (Y/n) "; cin >> ch;
    } while (ch == 'Y' || ch == 'y');

}

void load_print(char* fname)
{
    int i = 0;
    ifstream f(fname, ios::binary);
    if (!f)
    {
        cerr << "Помилка відкриття файлу '" << fname << "'" << endl;
        return;
    }

    cout << "=========================================================================================================================="
        << endl;
    cout << "| № |    Прiзвище   | Курс |  Спецiальнiсть   | Фiзика | Математика | Програмування | Чисельнi методи | Педагогiка |"
        << endl;
    cout << "--------------------------------------------------------------------------------------------------------------------------"
        << endl;

    Student worker;
    while (f.read((char*)&worker, sizeof(Student)))
    {
        cout << "| " << setw(2) << right << i + 1 << "";
        cout << "| " << setw(14) << left << worker.surname
            << "| " << setw(5) << right << worker.course
            << "| " << setw(23) << left << specialityStr[worker.speciality]
            << "| " << setw(7) << worker.physics
            << "| " << setw(11) << right << worker.maths;
        if (worker.speciality == 0) {
            cout << "| " << setw(14) << right << worker.it
                << "| " << setw(16) << right << " "
                << "| " << setw(11) << right << " " << "| ";
        }
        else if (worker.speciality == 1) {
            cout << "| " << setw(14) << right << " "
                << "| " << setw(16) << right << worker.numb
                << "| " << setw(11) << right << " " << "| ";
        }
        else {
            cout << "| " << setw(14) << right << " "
                << "| " << setw(16) << right << " "
                << "| " << setw(11) << right << worker.ped << "| ";
        }
        cout << endl;
        ++i;
    }
    cout << "--------------------------------------------------------------------------------------------------------------------------"
        << endl;
}
int main()
{
    char fname[100];
    char ch;
    do
    {
        cout << endl;
        cout << "Вибрати:" << endl;
        cout << "[1] - ввести дані;" << endl;
        cout << "[2] - вивести дані;" << endl;
        cout << "[3] - вивід кількості оцінок 4 або 5 з фізики;" << endl;
        cout << "[4] - вивід середнього балу з кожного предмету;" << endl;
        cout << "[0] - вийти." << endl << endl;
        cout << "Ваш вибір: "; cin >> ch;
        switch (ch)
        {
        case '0':
            break;
        case '1':
            cin.get();
            cin.sync();
            cout << "Введіть назву файлу: "; cin.getline(fname, sizeof(fname));
            enter_save(fname);
            break;
        case '2':
            cin.get();
            cin.sync();
            cout << "Введіть назву файлу: "; cin.getline(fname, sizeof(fname));
            load_print(fname);
            break;
        case '3':
            cout << "Введіть назву файлу: "; cin >> fname;
            cout << "Кількість студентів, які отримали з фізики “5” або “4”: " << PhysicsFiveOrFour(fname) << endl;
            break;
        case '4':
            cout << endl;
            cout << "Введіть назву файла: "; cin >> fname;
            ArithmeticMean(fname);
            break;
        default:
            cout << "Помилка ! ";
        }
    } while (ch != '0');
    return 0;
}
