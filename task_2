/* Яндекс.Контест
Пароль от некоторого сервиса должен удовлетворять таким ограничениям:

+состоять из символов таблицы ASCII с кодами от 33 до 126;
+быть не короче 8 символов и не длиннее 14; 
+из 4 классов символов — большие буквы, маленькие буквы, цифры, прочие символы — в пароле должны присутствовать 
 не менее трёх любых.

Напишите программу, которая проверит, что введённый пароль подходит под эти ограничения.*/
#include <iostream>
#include <string>

using namespace std;

int main(){
    string password;
    bool flag = 1, uplet = 0, lowlet = 0, nums = 0, sym = 0;
    cin >> password;
    if (password.size()<8 || password.size()>14) flag = 0;
    for (size_t i = 0; i<password.size(); i++){
        char temp = password[i];
        if (temp<33 || temp>126){
            flag = 0;
            break;
        }
        else{
            if (temp>=65 && temp<=90) uplet = 1;
            if (temp>=48 && temp<=57) nums = 1;
            if (temp>=97 && temp<=122) lowlet = 1;
            if ((temp>=33 && temp<=47) || (temp>=58 && temp<=64) || (temp>=91 && temp<=96) || (temp>=123 && temp<=126)) sym = 1;
        }
    }
    int res = uplet+nums+lowlet+sym;
    if (flag && res>=3) cout << "YES";
    else cout << "NO";
}
