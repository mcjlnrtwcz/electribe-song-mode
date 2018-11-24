#include "Beat.hpp"

#include <string>

Beat::Beat() {
    // Empty.
}

Beat::Beat(unsigned int a_measures) {
    if (a_measures == 0) {
        m_measure = 1;
        m_quater = 1;
        m_clock = 1;
    } else {
        m_measure = a_measures;
        m_quater = 4;
        m_clock = 24;
    }
}

Beat::Beat(unsigned int a_measure, unsigned int a_quater, unsigned int a_clock) {
    m_measure = a_measure;
    m_quater = a_quater;
    m_clock = a_clock;
}

void Beat::tick() {
    if (m_clock == 24) {
        m_clock = 1;
        if (m_quater == 4) {
            m_quater = 1;
            m_measure++;
        } else if (m_quater > 0 && m_quater < 4) {
            m_quater++;
        } else {
            // Something went terribly wrong.
        }
    } else if (m_clock > 0 && m_clock < 24) {
        m_clock++;
    } else {
        // Something went terribly wrong.
    }
}

std::string Beat::toString() const {
    return std::to_string(m_measure) + "." + std::to_string(m_quater) + "." + std::to_string(m_clock);
}

bool Beat::operator<(const Beat &a_anotherBeat) const {
    return getTotalClocks() < a_anotherBeat.getTotalClocks();
}

bool Beat::operator==(const Beat &a_anotherBeat) const {
    return getTotalClocks() == a_anotherBeat.getTotalClocks();
}
