#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

struct Student {
    string surname;
    string name;
    map<string, vector<int>> marks;
};

int main() {
    string group, subject;
    Student student;
    vector<Student> students = {
        {"Савичева", "Ирина", {{"Высшая математика", {5, 4, 4}}, {"Программирование", {5, 5, 5}}, {"ОБЖ", {4, 3, 5}}}},
        {"Супов", "Андрей", {{"Высшая математика", {3, 4, 3}}, {"Программирование", {4, 5, 4}}, {"ОБЖ", {5, 5, 5}}}},
        {"Широкова", "Алина", {{"Высшая математика", {4, 5, 4}}, {"Программирование", {5, 4, 5}}, {"ОБЖ", {5, 4, 4}}}},
        {"Тодороки", "Шото", {{"Высшая математика", {5, 5, 5}}, {"Программирование", {4, 5, 4}}, {"ОБЖ", {4, 4, 4}}}}
    };

    map<string, vector<Student*>> groups;
    groups["ПИ01"] = {&students[0], &students[1]};
    groups["ПИ02"] = {&students[2], &students[3]};

    cout << "Введите группу: ";
    getline(cin, group);
/*Для поиска внутри map по ключу в C++ можно использовать функцию map::find. 
Она принимает ключ в качестве аргумента и возвращает итератор к элементу, если ключ найден. 
Если ключ не найден, функция возвращает итератор к концу map.
Также можно использовать функцию contains. Она принимает ссылку на ключ и возвращает логическое значение true, 
если ключ найден.

Ещё один вариант — использовать функцию count. Она находит и возвращает количество элементов в карте с заданным 
ключом. Поскольку карта содержит элементы только с уникальным ключом, функция вернёт 1,
если ключ существует, иначе 0.*/
    if (groups.find(group) == groups.end()) {
        cout << "Группа не найдена." << endl;
        return 0;
    }

    cout << "Введите фамилию и имя студента: ";
    cin >> student.surname >> student.name;
    cin.ignore(); // Очистка буфера после cin

    cout << "Введите предмет, по которому нужно узнать оценки: ";
    getline(cin, subject);

    bool flag = 0;
    for (Student* s : groups[group]) {
        if (s->surname == student.surname && s->name == student.name) {
            /*std::cout << (*ptr).x << "\n";  // обращение через * и . требует скобок
              std::cout << ptr->x << "\n";  // то же самое, но чуть короче*/
            flag = 1;
            if (s->marks.find(subject) != s->marks.end()) {
                cout << "Оценки по предмету \"" << subject << "\": ";
                for (int mark : s->marks[subject]) {
                    cout << mark << " ";
                }
                cout << endl;
            } else {
                cout << "Предмет \"" << subject << "\" не найден у студента." << endl;
            }
            break;
        }
    }

    if (!flag) {
        cout << "Студент не найден в указанной группе.";
    }
    return 0;
}
