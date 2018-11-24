#include "Pattern.hpp"

class Beat;

Pattern::Pattern(unsigned int a_ID, std::string a_name, Beat a_startAt) :
    m_ID(a_ID),
    m_name(a_name),
    m_startAt(a_startAt) {
    // Empty.
}
