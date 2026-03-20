#include <cstring>
#include <iostream>

namespace stringUtils {
static char *cloneString(const char *src) {
    if (!src)
        return nullptr;

    char *dest = new char[strlen(src) + 1];
    std::strcpy(dest, src);
    return dest;
}
} // namespace stringUtils

namespace bookManagementSystem {
class Book {
    char *m_title;
    int m_pages;

  public:
    Book(const char *title = ("Untitled"), int pages = 0) : m_pages(pages) {
        m_title = stringUtils::cloneString(title);
    }

    Book(const Book &other) : m_pages(other.m_pages) {
        m_title = stringUtils::cloneString(other.m_title);
    }

    const Book &operator=(const Book &other) {
        if (this == &other)
            return *this;

        delete[] m_title;
        m_title = stringUtils::cloneString(other.m_title);
        m_pages = other.m_pages;

        return *this;
    }

    virtual ~Book() {
        delete[] m_title;
        m_title = nullptr;
    }

    virtual void readBookData() {
        char buffer[256];
        std::cout << "Enter title of book: ";
        std::cin.getline(buffer, 256);

        delete[] m_title;
        m_title = stringUtils::cloneString(buffer);

        std::cout << "Enter number of pages of book: ";
        std::cin >> m_pages;
        std::cin.ignore();
    }

    virtual void displayBookData() {
        std::cout << "Title: " << m_title << std::endl;
        std::cout << "Pages: " << m_pages << std::endl;
    }
};

class EBook : public Book {
    double m_fileSizeMB;
    char *m_format;

  public:
    EBook(double fileSizeMB = 0.0, const char *format = "N/A")
        : m_fileSizeMB(fileSizeMB) {
        m_format = stringUtils::cloneString(format);
    }

    EBook(const EBook &other) : Book(other), m_fileSizeMB(other.m_fileSizeMB) {
        m_format = stringUtils::cloneString(other.m_format);
    }

    const EBook &operator=(const EBook &other) {
        if (this == &other)
            return *this;

        Book::operator=(other);

        m_fileSizeMB = other.m_fileSizeMB;
        delete[] m_format;
        m_format = stringUtils::cloneString(other.m_format);

        return *this;
    }

    ~EBook() override {
        delete[] m_format;
        m_format = nullptr;
    }

    void readBookData() override {
        Book::readBookData();

        std::cout << "Enter file size (MB): ";
        std::cin >> m_fileSizeMB;
        std::cin.ignore();

        char buffer[256];

        std::cout << "Enter file format (PDF/EPUB etc): ";
        std::cin >> buffer;
        std::cin.ignore();

        delete[] m_format;
        m_format = stringUtils::cloneString(buffer);
    }

    void displayBookData() override {
        Book::displayBookData();

        std::cout << "File size: " << m_fileSizeMB << " MB" << std::endl;
        std::cout << "File format: " << m_format << std::endl;
    }
};
} // namespace bookManagementSystem

int main() {
    using namespace bookManagementSystem;
    using namespace std;

    cout << "Testing out book class" << endl;
    Book b1;
    b1.readBookData();
    b1.displayBookData();

    Book b2(b1);
    cout << "Copy constructor of book: " << endl;
    b2.displayBookData();

    Book b3;
    b3 = b2;
    cout << "Assignment operator: " << endl;
    b3.displayBookData();

    cout << "----------------------------" << endl;

    cout << "Testing out EBook class: " << endl;

    EBook e1;
    e1.readBookData();
    e1.displayBookData();

    cout << "Copy constructor of EBook: " << endl;
    EBook e2 = e1;
    e1.displayBookData();

    cout << "Assignment operator of EBook: " << endl;
    EBook e3;
    e3 = e1;
    e3.displayBookData();

    cout << "Testing polymorphism via pointers (Book* -> EBook): " << endl;

    Book *ptr = new EBook();

    ptr->readBookData();
    ptr->displayBookData();
    delete ptr;

    return 0;
}
