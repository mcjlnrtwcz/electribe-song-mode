#ifndef BEAT_HPP
#define BEAT_HPP

#include <string>

class Beat {
public:
    Beat();
    Beat(unsigned int a_measures);
    Beat(unsigned int a_measure, unsigned int a_quater, unsigned int a_clock);
    unsigned int getMeasure() const { return m_measure; }
    unsigned int getQuater() const { return m_quater; }
    unsigned int getClock() const { return m_clock; }
    unsigned int getTotalClocks() const { return m_measure * 4 * 24 + m_quater * 24 + m_clock; }
    void tick();
    std::string toString() const;
    bool operator<(const Beat &a_anotherBeat) const;
    bool operator==(const Beat &a_anotherBeat) const;
private:
    unsigned int m_measure = 1;
    unsigned int m_quater = 1;
    unsigned int m_clock = 1;
};

#endif
