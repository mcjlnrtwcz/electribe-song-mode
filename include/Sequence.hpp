#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP

#include "Beat.hpp"
#include "Pattern.hpp"

#include <string>
#include <vector>

class Sequence {
public:
    void loadData(std::string a_path);
    unsigned int getBPM() const { return m_BPM; }
    unsigned int getTotalMeasures() const { return m_totalMeasures; }
    unsigned int currentPatternID() const { return m_patternList.back().getID(); }
    std::string currentPatternName() const { return m_patternList.back().getName(); }
    Beat currentPatternStart() const { return m_patternList.back().startAt(); }
    void nextPattern() { m_patternList.pop_back(); }
    int length() { return m_patternList.size(); }
private:
    unsigned int m_BPM;
    unsigned int m_totalMeasures;
    std::vector<Pattern> m_patternList;
};

#endif
