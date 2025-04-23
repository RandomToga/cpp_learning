#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <ctime>

/*минутка английского:
Quantity - общее количество
Instances - экземпляры в наличии*/


using namespace std;
struct Reader {
    string name;
    string date;
};

class Book {
protected:
    string Title;
    vector<string> Authors;
    unsigned int Year;
    string Publisher;
    unsigned int Pages;
public:
    // Конструктор со списком инициализации
    Book(const string& title, const vector<string>& authors,
    unsigned int year, const string& publisher, unsigned int pages) :
    Title(title), Authors(authors), Year(year), Publisher(publisher), Pages(pages) {}
    // Геттеры для доступа к полям класса (все возвращают константные значения)
    string getTitle() const { return Title; }
    vector<string> getAuthors() const { return Authors; }
    unsigned int getYear() const { return Year; }
    string getPublisher() const { return Publisher; }
    unsigned int getPages() const { return Pages; }
};

class CatalogBook : public Book {
private:
    unsigned int ID;
    unsigned int Quantity;
    unsigned int Instances;
    vector<Reader> Picked;
public:
    // Конструктор со списком инициализации
    CatalogBook(const string& title, const vector<string>& authors,
        unsigned int year, const string& publisher, unsigned int pages,
        unsigned int id, unsigned int quantity, unsigned int instances,
        const vector<Reader>& picked) :
        Book(title, authors, year, publisher, pages), ID(id), Quantity(quantity),
        Instances(instances), Picked(picked) {
    }

    // Геттеры - получение данных из закрытых переменных
    unsigned int getID() const { return ID; }
    unsigned int getQuantity() const { return Quantity; }
    unsigned int getInstances() const { return Instances; }
    vector<Reader> getPicked() const { return Picked; }

    // Сеттеры - изменение данных в закрытых переменных
    void setInstances(unsigned int instances) { Instances = instances; }
    void setPicked(const vector<Reader>& picked) { Picked = picked; }

    // Методы работы с книгами
    void addToCatalog(vector<CatalogBook>& catalog) const;
    void printInfo() const;
    void giveToReader(const string& readerName);
    void returnFromReader(const string& readerName);

    // Статические методы
    static void removeFromCatalog(vector<CatalogBook>& catalog, unsigned int id);
    static void searchInCatalog(const vector<CatalogBook>& catalog, const string& searchTerm);
    static void printOverdueReaders(const vector<CatalogBook>& catalog);
    static string getCurrentDate();
    static bool isDateOverYear(const string& date);
};
