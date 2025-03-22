/*Требуется написать программу, которая по заданной температуре в комнате troom,
установленным на кондиционере желаемой температуре tcond и режиму работы определяет температуру, 
которая установится в комнате через час.*/
#include <iostream>
#include <string>
using namespace std;

int main() {
	int troom, tcond;
	string mod;
	cin >> troom >> tcond >> mod;
	if (mod == "heat") {
		if (troom > tcond) cout << troom;
		else cout << tcond;
	}
	else if (mod == "freeze") {
		if (troom > tcond) cout << tcond;
		else cout << troom;
	}
	else if (mod == "fan") {
		cout << troom;
	}
	else if (mod == "auto") {
		cout << tcond;
	}
}