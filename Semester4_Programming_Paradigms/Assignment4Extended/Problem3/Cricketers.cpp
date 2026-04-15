#include <iostream>
#include <string>

namespace CricketersManagementSystem {

struct Match {
    std::string opponentTeam;
    int runsScored;     // batting
    int ballsPlayed;    // batting
    bool gotOut;        // batting
    int wicketsTaken;   // bowling
    double oversBowled; // bowling

    Match(std::string opp = "Unknown", int runs = 0, int balls = 0,
          bool out = false, int wickets = 0, double overs = 0.0)
        : opponentTeam(opp), runsScored(runs), ballsPlayed(balls), gotOut(out),
          wicketsTaken(wickets), oversBowled(overs) {}
};

class Cricketer {
  protected:
    std::string m_name;
    int m_matchesPlayed; // Number of currently stored records
    int m_capacity;      // Total allocated array size
    Match *m_matches;    // Dynamic array of structs

    // Helper to dynamically grow the array when full
    void resize() {
        m_capacity = (m_capacity == 0) ? 2 : m_capacity * 2;
        Match *temp = new Match[m_capacity];
        for (int i = 0; i < m_matchesPlayed; ++i) {
            temp[i] = m_matches[i];
        }
        delete[] m_matches;
        m_matches = temp;
    }

  public:
    Cricketer(std::string name = "N/A")
        : m_name(name), m_matchesPlayed(0), m_capacity(2),
          m_matches(new Match[2]) {}

    Cricketer(const Cricketer &other)
        : m_name(other.m_name), m_matchesPlayed(other.m_matchesPlayed),
          m_capacity(other.m_capacity) {
        m_matches = new Match[m_capacity];
        for (int i = 0; i < m_matchesPlayed; ++i) {
            m_matches[i] = other.m_matches[i];
        }
    }

    Cricketer &operator=(const Cricketer &other) {
        if (this != &other) {
            delete[] m_matches;

            m_name = other.m_name;
            m_matchesPlayed = other.m_matchesPlayed;
            m_capacity = other.m_capacity;
            m_matches = new Match[m_capacity];
            for (int i = 0; i < m_matchesPlayed; ++i) {
                m_matches[i] = other.m_matches[i];
            }
        }
        return *this;
    }

    void insertMatchRecord(const Match &record) {
        if (m_matchesPlayed >= m_capacity) {
            resize();
        }
        m_matches[m_matchesPlayed] = record;
        m_matchesPlayed++;
    }

    virtual void displayStats() const = 0;
};

class Batsman : virtual public Cricketer {
  public:
    Batsman(std::string name = "N/A") : Cricketer(name) {}

    double countBattingAverage() const {
        if (m_matchesPlayed == 0)
            return 0.0;

        int totalRuns = 0;
        int timesOut = 0;
        for (int i = 0; i < m_matchesPlayed; ++i) {
            totalRuns += m_matches[i].runsScored;
            if (m_matches[i].gotOut) {
                timesOut++;
            }
        }
        return (timesOut == 0) ? totalRuns
                               : static_cast<double>(totalRuns) / timesOut;
    }

    void findHighestRunsCountry() const {
        if (m_matchesPlayed == 0) {
            std::cout << "No match records available.\n";
            return;
        }

        int maxRuns = m_matches[0].runsScored;
        std::string maxOpponent = m_matches[0].opponentTeam;

        for (int i = 1; i < m_matchesPlayed; ++i) {
            if (m_matches[i].runsScored > maxRuns) {
                maxRuns = m_matches[i].runsScored;
                maxOpponent = m_matches[i].opponentTeam;
            }
        }
        std::cout << "Highest Runs: " << maxRuns << " against " << maxOpponent
                  << "\n";
    }

    void displayStats() const override {
        std::cout << "Batsman: " << m_name << "\n";
        std::cout << "Batting Average: " << countBattingAverage() << "\n";
    }
};

class Bowler : virtual public Cricketer {
  public:
    Bowler(std::string name = "N/A") : Cricketer(name) {}

    int countTotalWickets() const {
        int totalWickets = 0;
        for (int i = 0; i < m_matchesPlayed; ++i) {
            totalWickets += m_matches[i].wicketsTaken;
        }
        return totalWickets;
    }

    void findHighestWicketsCountry() const {
        if (m_matchesPlayed == 0) {
            std::cout << "No match records available.\n";
            return;
        }

        int maxWickets = m_matches[0].wicketsTaken;
        std::string maxOpponent = m_matches[0].opponentTeam;

        for (int i = 1; i < m_matchesPlayed; ++i) {
            if (m_matches[i].wicketsTaken > maxWickets) {
                maxWickets = m_matches[i].wicketsTaken;
                maxOpponent = m_matches[i].opponentTeam;
            }
        }
        std::cout << "Highest Wickets: " << maxWickets << " against "
                  << maxOpponent << "\n";
    }

    void displayStats() const override {
        std::cout << "Bowler: " << m_name << "\n";
        std::cout << "Total Wickets: " << countTotalWickets() << "\n";
    }
};

class AllRounder : public Batsman, public Bowler {
  public:
    AllRounder(std::string name = "N/A")
        : Cricketer(name), Batsman(name), Bowler(name) {}

    void addMatch(std::string opp, int runs, int balls, bool out, int wickets,
                  double overs) {
        Match newMatch(opp, runs, balls, out, wickets, overs);
        insertMatchRecord(newMatch); // Calls inherited base function
    }

    void displayStats() const override {
        std::cout << "AllRounder: " << m_name << "\n";
        std::cout << "| Matches Played: " << m_matchesPlayed << "\n";
        std::cout << "| Batting Average: " << countBattingAverage() << "\n";
        std::cout << "| Total Wickets: " << countTotalWickets() << "\n";
        findHighestRunsCountry();
        findHighestWicketsCountry();
    }
};

} // namespace CricketersManagementSystem

int main() {
    using namespace CricketersManagementSystem;

    AllRounder player("Jacques Kallis");

    player.addMatch("Australia", 102, 120, false, 2, 8.5);
    player.addMatch("England", 45, 60, true, 4, 10.0);
    player.addMatch("India", 15, 20, true, 0, 4.0);
    player.addMatch("Pakistan", 78, 85, true, 3, 9.2);

    player.displayStats();

    return 0;
}
