//разбработать класс сотрудник с конструктором, деструктором, закрытыми информационными членамии статическими членами
#include <iostream>
#include <string>
#include <locale.h>
using namespace std;

class Employee {
    static int count;
    string organization;
    string position;
    double experience;
    string name;
    char gender;
    int age;
    double salary;
public:
    //конструктор по умолчанию
    Employee() : organization(""), position(""), experience(0), name(""), gender('M'), age(0), salary(0) {
        count++;
    }
    //консруктор с параментрами
    Employee(string org, string pos, double exp, string n, char g, int a, double sal)
        //список инициализации?
        : organization(org), position(pos), experience(exp), name(n), gender(g), age(a), salary(sal) {
        count++;
    }
    //деструктор
    ~Employee() {
        count--;
    }
    //методы класса
    void information() const {
        cout << "ФИО: " << name << "\n";
        cout << "Место работы: " << organization << "\n";
        cout << "Должность: " << position << "\n";
        cout << "Стаж работы: " << experience << "\n";
        cout << "Зарплата: " << salary << "\n";
    }
    void SetPosition(string position) {
        this->position = position;
    }

    void salplus(int sum) {
        salary += sum;
    }
    void information2() const {
        cout << "ФИО:" << name << "\n";
        cout << "Пол:" << gender << "\n";
        cout << "Возраст:" << age << "\n";
    }
    static int CountOut() {
        return count;
    }
};

int Employee::count = 0;
int main() {
    setlocale(LC_ALL, "ru");
   
    
    //статика
    Employee test[2] = { Employee("Организация", "Д234", 3.5, "Имя", 'M', 20, 2000.0), Employee("Организ456", "Д234", 3.5, "Имя", 'M', 20, 2000.0) };
    cout << Employee::CountOut() << "\n";
    for (int i = 0; i < 2; i++) test[i].information();
    
    //динамика
    int sizeofdynamic = 1;

    Employee* test2 = new Employee[sizeofdynamic]{ Employee("Организация", "Должность", 3.5, "Имя", 'M', 20, 2000.0) };
    cout << Employee::CountOut() << "\n";
    for (int i = 0; i < sizeofdynamic; i++) test2[i].information();
    delete[] test2;
    cout << Employee::CountOut();
}
