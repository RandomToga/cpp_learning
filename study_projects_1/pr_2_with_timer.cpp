#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>
#include <limits>
#include <cassert>
#include <chrono>
 
using namespace std;
using namespace chrono;
 
struct Fraction {
    int num;
    int den;
};
 
vector<int> divs(int&); //Маша
void is_supreme(int&); //Маша
int nod(int, int); //Алина
int nok(int&, int&); //Алина
void is_prime(int&); //Настя
void kind_of_numbers(map<pair <int, int>, pair <int, int>>&); //Алина+Маша
void calculator_of_fractions(map<string, Fraction>&); //Алина+Маша
void output(map<pair <int, int>, pair <int, int>>&, map<string, Fraction>&); //Алина+Маша
Fraction simplify(Fraction); //Маша
void add_fractions(Fraction, Fraction, map<string, Fraction>&); //Маша
void subtract_fractions(Fraction, Fraction, map<string, Fraction>&); //Маша

vector <vector <int>> set_for_nod =
{ {1345, 678, 1}, {729, 243, 243}, {1024, 256, 256}, {2147483647, 1073741824, 1} };
vector <vector <int>> set_for_nok =
{ {4, 6, 12}, {15, 20, 60}, {2147483647, 1 ,2147483647}, {4194304, 2097152, 4194304} };
 
void test_all_functions() {
    for (auto test_set : set_for_nod)
        assert(nod(test_set[0], test_set[1]) == (test_set[2]));
    for (auto test_set : set_for_nok)
        assert(nok(test_set[0], test_set[1]) == (test_set[2]));
 
    cout << "Тесты пройдены!" << "\n";
}
 
int main() {
    test_all_functions();
    char press;
    map<pair <int, int>, pair <int, int>> cache_nod_nok;
    map<string, Fraction> cache_op_fractions;
    output(cache_nod_nok, cache_op_fractions);
    while (press!= 'n'){
        if (press == 'y') output(cache_nod_nok, cache_op_fractions);
        cout << "Хотите продолжить? [y/n] ";
        cin >> press;
    }
}
 
vector<int> divs(int& n) {
    vector<int> divs;
    for (int i = 1; i <= (sqrt(n)); i++) {
        if (n % i == 0) {
            divs.push_back(i);
            if (i * i != n)
                divs.push_back(n / i);
        }
    }
    return divs;
}
 
void is_prime(int& number) {
    if (divs(number).size() == 2) cout << "Число " << number << " простое\n";
    else cout << "Число " << number << " НЕ простое\n";
}
 
void is_supreme(int& n) {
    vector<int> divisors = divs(n);
    int sum = 0;
    for (auto it = divisors.begin(); it != divisors.end(); ++it) {
        if (*it != n)
            sum += *it;
    }
    if (sum == n)
        cout << "Число " << n << " совершенное\n";
    else
        cout << "Число " << n << " НЕ совершенное\n";
}
 
int nod(int n1, int n2) {
    while (n2 != 0) {
        int temp = n2;
        n2 = n1 % n2;
        n1 = temp;
    }
    return n1;
}
 
int nok(int& n1, int& n2){
    int result = (n1 / nod(n1, n2)) * n2;
    return result;
}

void kind_of_numbers(map<pair<int, int>, pair<int, int>>& cache_nod_nok) {
    pair<int, int> analysis;
    cout << "===== Функция анализатора\n"
         << "Введите два числа: ";
    cin >> analysis.first >> analysis.second;
    is_prime(analysis.first);
    is_prime(analysis.second);
    is_supreme(analysis.first);
    is_supreme(analysis.second);

    static double avg_cache_time = 0.0;
    static double avg_no_cache_time = 0.0;
    static int cache_hits = 0;
    static int cache_misses = 0;

    auto start = system_clock::now();
    bool from_cache = (cache_nod_nok.find(analysis) != cache_nod_nok.end());

    if (!from_cache) {
        cache_nod_nok[analysis].first = nod(analysis.first, analysis.second);
        cache_nod_nok[analysis].second = nok(analysis.first, analysis.second);
    }

    auto end = system_clock::now();
    duration<double> sec = end - start;
    cout << "Наибольший общий делитель => " << cache_nod_nok[analysis].first << "\n";
    cout << "Наименьшее общее кратное => " << cache_nod_nok[analysis].second << "\n";
    if (from_cache) {
        avg_cache_time = (avg_cache_time * cache_hits + sec.count()) / (cache_hits + 1);
        cache_hits++;
        cout << "Результат из кэша. Время получения: " << sec.count() << " секунд\n";
    } else {
        avg_no_cache_time = (avg_no_cache_time * cache_misses + sec.count()) / (cache_misses + 1);
        cache_misses++;
        cout << "Время расчета: " << sec.count() << " секунд\n";
    }

    if (cache_hits > 0 && cache_misses > 0) {
        double acceleration = (avg_no_cache_time - avg_cache_time) / avg_no_cache_time * 100.0;
        cout << "Ускорение: " << acceleration << "%\n";
    }
}

 
Fraction simplify(Fraction f) {
    int common_factor = nod(f.num, f.den);
    f.num /= common_factor;
    f.den /= common_factor;
    return f;
}
 
void add_fractions(Fraction f1, Fraction f2, map<string, Fraction>& cache_op_fractions) {
    string key = to_string(f1.num) + "/" + to_string(f1.den) + " + " + to_string(f2.num) + "/" + to_string(f2.den);
    system_clock::time_point start = system_clock::now();
    static double avg_cache_time = 0.0;
    static double avg_no_cache_time = 0.0;
    static int cache_hits = 0;
    static int cache_misses = 0;
    auto it = cache_op_fractions.find(key);
    if (it != cache_op_fractions.end()) {
        system_clock::time_point end = system_clock::now();
        duration<double> sec = end - start;
        avg_cache_time = (avg_cache_time * cache_hits + sec.count()) / (cache_hits + 1);
        cache_hits++;
        cout << "Результат из кэша: " << it->second.num << "/" << it->second.den << "\n";
        cout << "Время получения: " << sec.count() << " секунд\n";
    } else {
        Fraction result;
        result.den = (f1.den * f2.den) / nod(f1.den, f2.den);
        result.num = (f1.num) * (result.den / f1.den) + (f2.num) * (result.den / f2.den);
        result = simplify(result);
        cache_op_fractions[key] = result;
        system_clock::time_point end = system_clock::now();
        duration<double> sec = end - start;
        avg_no_cache_time = (avg_no_cache_time * cache_misses + sec.count()) / (cache_misses + 1);
        cache_misses++;
        cout << "Результат: " << result.num << "/" << result.den << "\n";
        cout << "Время расчета: " << sec.count() << " секунд\n";
    }

    if (cache_hits > 0 && cache_misses > 0) {
        cout << "Ускорение: " << ((avg_no_cache_time - avg_cache_time) / avg_no_cache_time) * 100.0 << "%\n";
    }
}

void subtract_fractions(Fraction f1, Fraction f2, map<string, Fraction>& cache_op_fractions) {
    string key = to_string(f1.num) + "/" + to_string(f1.den) + " - " + to_string(f2.num) + "/" + to_string(f2.den);
    system_clock::time_point start = system_clock::now();
    static double avg_cache_time = 0.0;
    static double avg_no_cache_time = 0.0;
    static int cache_hits = 0;
    static int cache_misses = 0;
    auto it = cache_op_fractions.find(key);
    if (it != cache_op_fractions.end()) {
        system_clock::time_point end = system_clock::now();
        duration<double> sec = end - start;
        avg_cache_time = (avg_cache_time * cache_hits + sec.count()) / (cache_hits + 1);
        cache_hits++;
        cout << "Результат из кэша: " << it->second.num << "/" << it->second.den << "\n";
        cout << "Время получения: " << sec.count() << " секунд\n";
    } else {
        Fraction result;
        result.den = (f1.den * f2.den) / nod(f1.den, f2.den);
        result.num = (f1.num) * (result.den / f1.den) - (f2.num) * (result.den / f2.den);
        result = simplify(result);
        cache_op_fractions[key] = result;
        system_clock::time_point end = system_clock::now();
        duration<double> sec = end - start;
        avg_no_cache_time = (avg_no_cache_time * cache_misses + sec.count()) / (cache_misses + 1);
        cache_misses++;
        cout << "Результат: " << result.num << "/" << result.den << "\n";
        cout << "Время расчета: " << sec.count() << " секунд\n";
    }

    if (cache_hits > 0 && cache_misses > 0) {
        cout << "Ускорение: " << ((avg_no_cache_time - avg_cache_time) / avg_no_cache_time) * 100.0 << "%\n";
    }
}


void calculator_of_fractions(map<string, Fraction>& cache_op_fractions){
    Fraction f1, f2, result;
    char op;
 
    cout << "Введите первую дробь (числитель и знаменатель через пробел): ";
    cin >> f1.num >> f1.den;
    cout << "Введите вторую дробь (числитель и знаменатель через пробел): ";
    cin >> f2.num >> f2.den;
 
    while (cin.fail() or  f1.den == 0  or f2.den == 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Знаменатель не может быть равен 0. Введите значения еще раз.\n";
        cout << "Введите первую дробь (числитель и знаменатель через пробел): ";
        cin >> f1.num >> f1.den;
        cout << "Введите вторую дробь (числитель и знаменатель через пробел): ";
        cin >> f2.num >> f2.den;
    }
 
    cout << "Введите операцию (+ или -): ";
    cin >> op;
 
    if (op == '+') {
        add_fractions(f1, f2, cache_op_fractions);
    } else if (op == '-') {
        subtract_fractions(f1, f2, cache_op_fractions);
    } else {
        cout << "Операция не поддерживается.\n";
    }
}
 
void output(map<pair <int, int>, pair <int, int>>& cache_nod_nok, map<string, Fraction>& cache_op_fractions){
    int choice;
 
    cout << "\nВыберите действие:\n"
         << "1. какое число\n"
         << "2. дроби\n"
         << "Введите номер действия: ";
    cin >> choice;
    switch (choice) {
        case 1:
            return kind_of_numbers(cache_nod_nok);
            break;
        case 2:
            return calculator_of_fractions(cache_op_fractions);
            break;
        default: cout << "Нет такого действия\n";
    }
}
