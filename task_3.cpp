/*Яндекс.Контест
Напечатайте строки в отсортированном по убыванию порядке. Для сравнения
строк друг с другом достаточно использовать стандартные операторы сравнения, определённые для std::string.
Для завершения программы: ctrl+z+enter*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    vector<string> lines;
    string line;
    while (getline(cin, line)) {
        lines.push_back(line);
    }
    sort(lines.rbegin(), lines.rend());
    for (size_t i = 0; i != lines.size(); ++i) {
        cout << lines[i] << "\n";
    }
}
