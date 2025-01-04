/*Пользователь вводит свое имя, фамилию, дату рождения, получает свой знак зодиака, 
а его данные записываются в вектор данных*/
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <tuple> // Для std::tie

using namespace std;

struct Zodiacs {
    pair<int, int> start; //начало знака зодиака
    pair<int, int> end; //конец знака зодиака
    string zodiac; //сам знак
};

struct Person {
    string surname;
    string name;
    bool operator<(const Person& other) const {
        return tie(surname, name) < tie(other.surname, other.name);
    }
};

string determine_zodiac(const int& day, const int& month) {
    vector<Zodiacs> dates = {
        {{21, 3}, {20, 4}, "Овен"},
        {{21, 4}, {21, 5}, "Телец"},
        {{22, 5}, {21, 6}, "Близнецы"},
        {{22, 6}, {22, 7}, "Рак"},
        {{23, 7}, {23, 8}, "Лев"},
        {{24, 8}, {23, 9}, "Дева"},
        {{24, 9}, {23, 10}, "Весы"},
        {{24, 10}, {22, 11}, "Скорпион"},
        {{23, 11}, {21, 12}, "Стрелец"},
        {{22, 12}, {20, 1}, "Козерог"},
        {{21, 1}, {19, 2}, "Водолей"},
        {{20, 2}, {20, 3}, "Рыбы"}};
    for (const auto& zodiac : dates) {
        if ((month == zodiac.start.second && day >= zodiac.start.first) ||
            (month == zodiac.end.second && day <= zodiac.end.first) ||
            (zodiac.start.second < zodiac.end.second &&
             month > zodiac.start.second && month < zodiac.end.second)) {
            return zodiac.zodiac;
        }
    }
    return "Неизвестно";
}
map<Person, string> book;
void output() {
    string surname, name, bday;
    cout << "Введите фамилию: ";
    cin >> surname;
    cout << "Введите имя: ";
    cin >> name;
    cout << "Введите дату рождения (дд.мм): ";
    cin >> bday;
    int day, month;
    sscanf(bday.c_str(), "%d.%d", &day, &month);
    string zodiac = determine_zodiac(day, month);
    Person person = {surname, name};
    book[person] = bday;
    cout << "Ваш знак зодиака: " << zodiac << endl;
    
}
void stolen_data (){
    cout << "Данные пользователей:\n";
    for (const pair<Person, string>& item : book)
        cout << item.first.surname << " " << item.first.name << ": " << item.second << "\n";
}
int main() {
    setlocale(LC_ALL, "Russian");
    char press = 'y';
    cout << "Хотите узнать ваш знак зодиака?\n";
    while (press != 'n') {
        if (press == 'y') output();
        else if (press == 'i') stolen_data();
        cout << "Хотите продолжить? [y/n] ";
        cin >> press;
    }
    cout << "До свидания!";
}