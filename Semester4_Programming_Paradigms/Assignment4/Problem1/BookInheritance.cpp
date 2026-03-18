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
    EBook(double fileSizeMB = 0.0, const char *format = "N\\A")
        : m_fileSizeMB(fileSizeMB) {
        m_format = stringUtils::cloneString(format);
    }

    EBook(const EBook &other) : Book(other), m_fileSizeMB(other.m_fileSizeMB) {
        delete[] m_format;
        m_format = stringUtils::cloneString(other.m_format);
    }
};
} // namespace bookManagementSystem

int main() {
    using namespace bookManagementSystem;
    Book b1;
    b1.displayBookData();
    b1.readBookData();
    b1.displayBookData();

    EBook b2;
}
