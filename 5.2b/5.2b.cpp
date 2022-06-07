#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

enum Speciality { COMPUTER_SCIENCE, IT, MATH_ECONOMICS, PHYSICS_IT, HANDICRAFT };
string specialityStr[] = { "����'�����i �����", "I����������", "�����. �� ������.", "�i���� �� i�����.", "�������  ��������" };

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

    cout << "������� ��� � ������: " << markPhys / i << endl;
    cout << "������� ��� � ����������: " << markMaths / i << endl;
    cout << "������� ��� � �������������: " << markIT / a << endl;
    cout << "������� ��� � ��������� ������: " << markNumb / b << endl;
    cout << "������� ��� � ���������: " << markPed / c << endl;
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
        cerr << "������� �������� ����� '" << fname << "'" << endl;
        return;
    }
    Student worker;
    char ch;
    do
    {
        cout << endl;
        cout << "�������: "; cin.sync();
        cin >> worker.surname;
        cout << "����: "; cin >> worker.course;
        cout << "����i����i��� (0 - ����'�����i �����, 1 -  I����������, 2 -  ���������� �� ������i��, 3 -  �i���� �� i����������, 4 - ������� ��������): ";
        cin >> sp;
        worker.speciality = static_cast<Speciality>(sp);
        cout << "��i��� � �i����: ";
        cin >> worker.physics;
        cout << "��i��� � ����������: ";
        cin >> worker.maths;
        if (worker.speciality == 0) {
            cout << "��i��� � �������������: ";
            cin >> worker.it;
        }
        else if (worker.speciality == 1) {
            cout << "��i��� � ��������� �����i�: ";
            cin >> worker.numb;
        }
        else {
            cout << "��i��� � �������i��: ";
            cin >> worker.ped;
        }
        if (!f.write((char*)&worker, sizeof(Student)))
        {
            cerr << "������� �������� �����." << endl;
        }
        cout << "����������? (Y/n) "; cin >> ch;
    } while (ch == 'Y' || ch == 'y');

}

void load_print(char* fname)
{
    int i = 0;
    ifstream f(fname, ios::binary);
    if (!f)
    {
        cerr << "������� �������� ����� '" << fname << "'" << endl;
        return;
    }

    cout << "=========================================================================================================================="
        << endl;
    cout << "| � |    ��i�����   | ���� |  ����i����i���   | �i���� | ���������� | ������������� | �������i ������ | �������i�� |"
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
        cout << "�������:" << endl;
        cout << "[1] - ������ ���;" << endl;
        cout << "[2] - ������� ���;" << endl;
        cout << "[3] - ���� ������� ������ 4 ��� 5 � ������;" << endl;
        cout << "[4] - ���� ���������� ���� � ������� ��������;" << endl;
        cout << "[0] - �����." << endl << endl;
        cout << "��� ����: "; cin >> ch;
        switch (ch)
        {
        case '0':
            break;
        case '1':
            cin.get();
            cin.sync();
            cout << "������ ����� �����: "; cin.getline(fname, sizeof(fname));
            enter_save(fname);
            break;
        case '2':
            cin.get();
            cin.sync();
            cout << "������ ����� �����: "; cin.getline(fname, sizeof(fname));
            load_print(fname);
            break;
        case '3':
            cout << "������ ����� �����: "; cin >> fname;
            cout << "ʳ������ ��������, �� �������� � ������ �5� ��� �4�: " << PhysicsFiveOrFour(fname) << endl;
            break;
        case '4':
            cout << endl;
            cout << "������ ����� �����: "; cin >> fname;
            ArithmeticMean(fname);
            break;
        default:
            cout << "������� ! ";
        }
    } while (ch != '0');
    return 0;
}
