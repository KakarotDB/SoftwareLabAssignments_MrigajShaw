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
};
} // namespace bookManagementSystem
