#ifndef HEART_HPP
#define HEART_HPP

#include "Beat.hpp"
#include "Sequence.hpp"

#include <atomic>
#include <functional>
#include <memory>
#include <string>

class MIDIOutput;

class Heart {
public:
    Heart();
    Heart(Sequence a_sequence, std::shared_ptr<MIDIOutput> a_midiOutput, std::function<void(std::string, unsigned int, std::string)> a_onNextPattern);
    void run();
    void requestStop() { m_stopRequested = true; }
private:
    Sequence m_sequence;
    std::shared_ptr<MIDIOutput> m_midiOutput;
    std::function<void(std::string, unsigned int, std::string)> onNextPattern;
    long m_interval;
    long m_intervalDrift = 0;
    Beat m_currentBeat = Beat(0, 1, 1);
    bool m_stopRequested = false;
    void nextPattern();
    void pump();
};

#endif
