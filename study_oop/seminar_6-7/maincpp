#include "HeaderBook.h"
#include <iostream>
#include <vector>
#include <clocale>
using namespace std;
void displayMenu() {
    cout << "\nКаталог библиотеки\n";
    cout << "1. Добавить книгу в каталог\n";
    cout << "2. Удалить книгу из каталога\n";
    cout << "3. Посмотреть информацию о книге\n";
    cout << "4. Найти книгу по названию или автору\n";
    cout << "5. Выдать книгу\n";
    cout << "6. Вернуть книгу\n";
    cout << "7. Читатели, просрочившие срок сдачи книг\n";
    cout << "8. Выход\n";
    cout << "Введите: ";
}

int main() {
    setlocale(LC_ALL, "Russian");
    vector<CatalogBook> catalog;
    int choice = 0;

    while (choice != 8) {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1: {
            string title, publisher;
            vector<string> authors;
            unsigned int year, pages, id, quantity;

            cout << "Введите название книги: ";
            cin.ignore();
            getline(cin, title);

            cout << "Введите авторов (через запятую): ";
            string authorsInput;
            getline(cin, authorsInput);
            size_t pos = 0;
            while ((pos = authorsInput.find(',')) != string::npos) {
                string author = authorsInput.substr(0, pos);
                authors.push_back(author);
                authorsInput.erase(0, pos + 1);
            }
            authors.push_back(authorsInput);

            cout << "Введите год публикации: ";
            cin >> year;

            cout << "Издательство: ";
            cin.ignore();
            getline(cin, publisher);

            cout << "Количество страниц: ";
            cin >> pages;

            cout << "ID: ";
            cin >> id;

            cout << "Количество экземпляров: ";
            cin >> quantity;

            CatalogBook newBook(title, authors, year, publisher, pages, id, quantity, quantity, {});
            newBook.addToCatalog(catalog);
            break;
        }
        case 2: {
            unsigned int id;
            cout << "Введите ID книги для удаления: ";
            cin >> id;
            CatalogBook::removeFromCatalog(catalog, id);
            break;
        }
        case 3: {
            unsigned int id;
            cout << "Введите ID книги для просмотра: ";
            cin >> id;
            auto it = find_if(catalog.begin(), catalog.end(),
                [id](const CatalogBook& book) { return book.getID() == id; });

            if (it != catalog.end()) {
                it->printInfo();
            }
            else {
                cout << "Книга с ID " << id << " не найдена.\n";
            }
            break;
        }
        case 4: {
            string searchTerm;
            cout << "Введите название или автора книги: ";
            cin.ignore();
            getline(cin, searchTerm);
            CatalogBook::searchInCatalog(catalog, searchTerm);
            break;
        }
        case 5: {
            unsigned int id;
            string readerName;
            cout << "Введите ID книги: ";
            cin >> id;
            cout << "Введите имя читателя: ";
            cin.ignore();
            getline(cin, readerName);

            auto it = find_if(catalog.begin(), catalog.end(),
                [id](const CatalogBook& book) { return book.getID() == id; });

            if (it != catalog.end()) {
                it->giveToReader(readerName);
            }
            else {
                cout << "Книга с ID " << id << " не найдена.\n";
            }
            break;
        }
        case 6: {
            unsigned int id;
            string readerName;
            cout << "Введите ID книги: ";
            cin >> id;
            cout << "Введите имя читателя: ";
            cin.ignore();
            getline(cin, readerName);

            auto it = find_if(catalog.begin(), catalog.end(),
                [id](const CatalogBook& book) { return book.getID() == id; });

            if (it != catalog.end()) {
                it->returnFromReader(readerName);
            }
            else {
                cout << "Книга с ID " << id << " не найдена.\n";
            }
            break;
        }
        case 7: {
            CatalogBook::printOverdueReaders(catalog);
            break;
        }
        case 8: {
            break;
        }
        default: {
            std::cout << "Неверный выбор.\n";
            break;
        }
        }
    } 

    return 0;
}
