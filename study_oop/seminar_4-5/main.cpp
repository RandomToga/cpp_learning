#include "Canvas.h"
#include <iostream>
#include <conio.h>
#include <vector>
#include <locale.h>

using namespace std;

// Функция для ввода точки
void inputPoint(const char* name, int& x, int& y) {
    cout << "Введите координаты " << name << " (x y): ";
    cin >> x >> y;
}

// Функция для ввода цвета
COLORREF inputColor(const char* name) {
    string col_name;
    int r=0, g=0, b=0;
    cout << "Введите цвет " << name << " (red/blue/pink): ";
    cin >> col_name;
    if (col_name == "red") {
        r = 250;
    }
    else if (col_name == "pink") {
        r = 255;
        g = 150;
        b = 150;
    }
    else if (col_name == "blue") {
        b = 255;
    }
    // не прдусмотрены неверные вводы, но мне очень лень
    return RGB(r, g, b);
}

int main() {
    setlocale(LC_ALL, "ru");
    HWND hwnd = GetConsoleWindow();
    HDC hdc = GetDC(hwnd);
    canvas c;

    while (true) {
        system("cls"); //очистка консоли
        cout << "1. Добавить точку\n";
        cout << "2. Добавить линию\n";
        cout << "3. Добавить прямоугольник\n";
        cout << "4. Добавить эллипс\n";
        cout << "5. Добавить многоугольник\n";
        cout << "6. Очистить холст\n";
        cout << "7. Показать все фигуры\n";
        cout << "0. Выход\n";
        cout << "Выберите действие: ";

        int choice;
        cin >> choice;

        if (choice == 0) break;

        switch (choice) {
        case 1: { // Точка
            int x, y;
            inputPoint("точки", x, y);
            COLORREF color = inputColor("точки");
            c.add(new point(x, y, color));
            break;
        }
        case 2: { // Линия
            int x1, y1, x2, y2;
            inputPoint("начала линии", x1, y1);
            inputPoint("конца линии", x2, y2);
            COLORREF color = inputColor("линии");
            c.add(new line(x1, y1, x2, y2, color));
            break;
        }
        case 3: { // Прямоугольник
            int x1, y1, x2, y2;
            inputPoint("верхнего левого угла", x1, y1);
            inputPoint("нижнего правого угла", x2, y2);
            COLORREF color = inputColor("контура");
            cout << "Закрасить? (1 - да, 0 - нет): ";
            bool filled;
            cin >> filled;
            COLORREF fillColor = filled ? inputColor("заливки") : 0;
            c.add(new rectangle(x1, y1, x2, y2, color, filled, fillColor));
            break;
        }
        case 4: { // Эллипс
            int x1, y1, x2, y2;
            inputPoint("верхнего левого угла рамки", x1, y1);
            inputPoint("нижнего правого угла рамки", x2, y2);
            COLORREF color = inputColor("контура");
            cout << "Закрасить? (1 - да, 0 - нет): ";
            bool filled;
            cin >> filled;
            COLORREF fillColor = filled ? inputColor("заливки") : 0;
            c.add(new ellipse(x1, y1, x2, y2, color, filled, fillColor));
            break;
        }
        case 5: { // Многоугольник
            vector<point> points;
            int n;
            cout << "Введите количество вершин: ";
            cin >> n;

            for (int i = 0; i < n; i++) {
                int x, y;
                cout << "Вершина " << i + 1 << ": ";
                cin >> x >> y;
                points.emplace_back(x, y);
            }

            COLORREF color = inputColor("контура");
            cout << "Закрасить? (1 - да, 0 - нет): ";
            bool filled;
            cin >> filled;
            COLORREF fillColor = filled ? inputColor("заливки") : 0;
            c.add(new polygon(points, color, filled, fillColor));
            break;
        }
        case 6: // Очистка
            c.clear();
            cout << "Холст очищен!";
            _getch();
            break;
        case 7: // Показать
            system("cls");
            c.show();
            cout << "Вот ваши фигурки";
            _getch();
            break;
        default:
            cout << "Неверный выбор!";
            _getch();
        }
    }

    ReleaseDC(hwnd, hdc);
    return 0;
}