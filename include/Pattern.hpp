#ifndef PATTERN_HPP
#define PATTERN_HPP

#include "Beat.hpp"

#include <string>

class Pattern {
public:
    Pattern(unsigned int a_ID, std::string a_name, Beat a_startAt);
    unsigned int getID() const { return m_ID; }
    std::string getName() const { return m_name; }
    Beat startAt() const { return m_startAt; }
private:
    unsigned int m_ID;
    std::string m_name;
    Beat m_startAt;
};

#endif
