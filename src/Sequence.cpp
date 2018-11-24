#include "Pattern.hpp"
#include "Sequence.hpp"

#include "rapidjson/document.h"

#include <fstream>
#include <string>


void Sequence::loadData(std::string a_path) {
    // Clear previous sequence data.
    m_patternList.clear();
    m_totalMeasures = 0;

    // Read file contents.
    std::ifstream stream(a_path);
    std::string raw_sequence;
    raw_sequence.assign((std::istreambuf_iterator<char>(stream)), (std::istreambuf_iterator<char>()));

    // Parse it into a Document.
    rapidjson::Document sequence;
    sequence.Parse(raw_sequence.c_str());

    m_BPM = sequence["bpm"].GetInt();

    // Create a list of patterns to play.
    const rapidjson::Value& patterns = sequence["patterns"];
    for (auto& pattern : patterns.GetArray()) {
        m_patternList.insert(
            m_patternList.begin(),
            Pattern(pattern["id"].GetInt(),
            pattern["name"].GetString(), Beat(m_totalMeasures, 4, 1)));
        m_totalMeasures += pattern["length"].GetInt() * pattern["repeat"].GetInt();
    }
}
