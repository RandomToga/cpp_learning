#include "HeaderBook.h"
#include <algorithm>
#include <iomanip>


void CatalogBook::addToCatalog(vector<CatalogBook>& catalog) const {
    catalog.push_back(*this);
}

void CatalogBook::printInfo() const {
    cout << "\nИнформация о книге:\n";
    cout << "ID: " << ID << "\n";
    cout << "Название: " << getTitle() << "\n";
    cout << "Aвторы: ";
    for (const auto& author : getAuthors()) {
        cout << author << ", ";
    }
    cout << "\nГод издания: " << getYear() << "\n";
    cout << "Издательство: " << getPublisher() << "\n";
    cout << "Количество страниц: " << getPages() << "\n";
    cout << "Количество экземпляров: " << Quantity << "\n";
    cout << "Доступно экземпляров: " << Instances << "\n";

    if (!Picked.empty()) {
        cout << "\nЧитатели, у которых есть книга:\n";
        for (const auto& reader : Picked) {
            cout << "- " << reader.name << " от " << reader.date << "\n";
        }
    }
}

void CatalogBook::giveToReader(const string& readerName) {
    if (Instances > 0) {
        Reader reader;
        reader.name = readerName;
        reader.date = "01.01.2023";//getCurrentDate();
        Picked.push_back(reader);
        Instances--;
        cout << "Книга выдана " << readerName << " в дату " << reader.date << "\n";
    }
    else {
        cout << "Нет доступных экземпляров.\n";
    }
}

void CatalogBook::returnFromReader(const string& readerName) {
    auto it = find_if(Picked.begin(), Picked.end(),
        [readerName](const Reader& r) { return r.name == readerName; });
    /*Это лямбда-выражение (анонимная функция), которое проверяет, совпадает ли имя читателя с искомым.
    [readerName] — захват переменной readerName из внешней области видимости.
    (const Reader& r) — параметр функции (элемент вектора Picked).
    { return r.name == readerName; } — тело функции: сравнение имён.*/

    if (it != Picked.end()) {
        Picked.erase(it);
        Instances++;
        cout << readerName << "вернул книгу\n";
    }
    else {
        cout << "У " << readerName << " нет этой книги.\n";
    }
}

void CatalogBook::removeFromCatalog(vector<CatalogBook>& catalog, unsigned int id) {
    auto it = find_if(catalog.begin(), catalog.end(),
        [id](const CatalogBook& book) { return book.getID() == id; });

    if (it != catalog.end()) {
        catalog.erase(it);
        cout << "Книга с ID " << id << " удалена из каталога.\n";
    }
}

void CatalogBook::searchInCatalog(const vector<CatalogBook>& catalog, const string& searchTerm) {
    bool found = false;
    for (const auto& book : catalog) {
        bool titleMatch = book.getTitle().find(searchTerm) != string::npos;
        bool authorMatch = false;

        for (const auto& author : book.getAuthors()) {
            if (author.find(searchTerm) != string::npos) {
                authorMatch = true;
                break;
            }
        }

        if (titleMatch || authorMatch) {
            book.printInfo();
            found = true;
        }
    }

    if (!found) {
        cout << "Книг не найдено.\n";
    }
}

void CatalogBook::printOverdueReaders(const vector<CatalogBook>& catalog) {
    cout << "\nЧитатели, не вернувшие книги спустя год:\n";
    bool found = false;

    for (const auto& book : catalog) {
        for (const auto& reader : book.getPicked()) {
            if (isDateOverYear(reader.date)) {
                cout << "- " << reader.name << " с книгой под ID " << book.getID()
                    << " (" << book.getTitle() << ") от " << reader.date << "\n";
                found = true;
            }
        }
    }

    if (!found) {
        cout << "Нет читателей с долгами.\n";
    }
}
// две вспомогательные функции для printOverdueReaders
string CatalogBook::getCurrentDate() {
    time_t now = time(0);
    tm t;
    localtime_s(&t, &now);
    char buffer[11];
    strftime(buffer, sizeof(buffer), "%d.%m.%Y", &t);
    return string(buffer);
}

bool CatalogBook::isDateOverYear(const string& date) {
    if (date.empty()) return false;

    time_t now = time(0);
    tm currentTm;
    localtime_s(&currentTm, &now);

    int currentDay = currentTm.tm_mday;
    int currentMonth = currentTm.tm_mon + 1;
    int currentYear = currentTm.tm_year + 1900;

    int day = stoi(date.substr(0, 2));
    int month = stoi(date.substr(3, 2));
    int year = stoi(date.substr(6, 4));

    if (currentYear > year + 1) return true;
    if (currentYear == year + 1) {
        if (currentMonth > month) return true;
        if (currentMonth == month && currentDay >= day) return true;
    }
    return false;
}
