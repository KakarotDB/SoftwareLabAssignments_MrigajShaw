#include <iostream>

namespace CricketersManagementSystem {

typedef Struct Match {
	std::string opponentTeam;
	int runsScored; //batting
	int ballsPlayed; //batting
	bool gotOut; //batting
	int wicketsTaken; //bowling
	double oversBowled; //bowling
} Match;

class Cricketer {
  protected:
    int m_matchesPlayed;
    std::string m_name;
	Match *m_matches;
  public:
    Cricketer(int matchesPlayed = 0, std::string name = "N/A",
              Match *matches = nullptr) 
        : m_matchesPlayed(matchesPlayed), m_name(name) {
        if (m_matchesPlayed > 0 && matches!= nullptr) {
            m_matches = new Match[m_matchesPlayed];

            for (int i = 0; i < m_matchesPlayed; i++) {
				m_matches[i] = matches[i];
            }
        } 
    }

    virtual ~Cricketer() { delete[] m_matches; }

    virtual void addRecord() = 0;
    virtual void displayStats() = 0;
};

class Batsman : virtual public Cricketer {
	public:
    	Batsman(int matchesPlayed = 0, std::string name = "N/A",
              Match *matches = nullptr) : Cricketer(matchesPlayed, name, matches) {}
		void addRecord()

};
} // namespace CricketersManagementSystem
