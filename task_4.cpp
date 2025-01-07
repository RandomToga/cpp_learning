/*Яндекс.Контест
Вам требуется написать функцию со следующим заголовком:

std::vector<std::string> Split(const std::string& str, char delimiter);
Функция должна вернуть вектор строк, полученный разбиением строки str на части по указанному символу-разделителю delimiter. Если разделитель встретился в начале или в конце строки str, то в начале (соответственно, в конце) вектора с результатом должна быть пустая строка. Если два разделителя встретились рядом, то пустая строка между ними тоже должна попасть в ответ. Для пустой строки надо вернуть вектор, содержащий одну пустую строку.

Например, Split("What_is_your_name?", '_') должна вернуть вектор из строк What, is, your и name?.*/

#include <iostream>
#include <vector>
#include <string>
//в программах использую в основном size_t потому что яндекс придирается к int
using namespace std;
// Функция для разделения строки по разделителю
vector<string> Split(const string& str, char delimiter) {
    vector<string> result;
    size_t i = 0;
    for (size_t j = 0; j != str.size(); ++j) {
        if (str[j] == delimiter) {
            result.push_back(str.substr(i, j - i));
/*Функция substr() в C++ получает подстроку. Она принимает два параметра:
    -Индекс, с которого начинается подстрока.
    -Количество символов извлекаемой подстроки.
Ещё одна форма функции substr(),
которая принимает только начальный индекс, позволяет извлечь все символы начиная с определённого индекса.*/
            i = j + 1;
        }
    }
    result.push_back(str.substr(i));
    return result;
}
int main(){
    string sentence;
    char delimiter;
    getline(cin, sentence);
    cin >> delimiter;
    vector <string> splited = Split(sentence, delimiter);
    for (const auto& i : splited) cout << i << "\n";
}