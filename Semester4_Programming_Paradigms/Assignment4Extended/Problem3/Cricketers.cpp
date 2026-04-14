#include <iostream>

namespace CricketersManagementSystem {
class Cricketer {
  protected:
    int m_matchesPlayed;
    std::string m_name;
    std::string *m_opponents;

  public:
    Cricketer(int matchesPlayed = 0, std::string name = "N/A",
              const std::string *opponents = nullptr)
        : m_matchesPlayed(matchesPlayed), m_name(name) {
        if (m_matchesPlayed > 0 && opponents != nullptr) {
            m_opponents = new std::string[m_matchesPlayed];

            for (int i = 0; i < m_matchesPlayed; i++) {
                m_opponents[i] = opponents[i];
            }
        } else {
            m_opponents = nullptr;
        }
    }

    virtual ~Cricketer() { delete[] m_opponents; }

    virtual void addRecord() = 0;
    virtual void displayStats() = 0;
};
} // namespace CricketersManagementSystem
