#include "Beat.hpp"
#include "Heart.hpp"
#include "MIDIOutput.hpp"
#include "Sequence.hpp"

#include "spdlog/spdlog.h"

#include <chrono>
#include <functional>
#include <thread>

Heart::Heart() {
    // Empty.
}

Heart::Heart(Sequence a_sequence, std::shared_ptr<MIDIOutput> a_midiOutput, std::function<void(std::string, unsigned int, std::string)> a_onNextPattern) :
    m_sequence(a_sequence),
    m_interval(static_cast<int>(60.0 / m_sequence.getBPM() / 24.0 * 1000000)),
    onNextPattern(a_onNextPattern),
    m_midiOutput(a_midiOutput) {
    spdlog::get("logger")->debug("New heart created. Sequence size: {}", m_sequence.length());
}

void Heart::run() {
    const Beat lastBeat(m_sequence.getTotalMeasures());

    nextPattern();

    // Send one measure of sync.
    Beat initialMeasure(1, 1, 1);
    while (m_currentBeat < initialMeasure) {
        spdlog::get("logger")->debug("[{}] {}", m_currentBeat.toString(), initialMeasure.toString());
        pump();
    }

    m_midiOutput->startPlayback();
    while (m_currentBeat < lastBeat && !m_stopRequested) {
        spdlog::get("logger")->debug("[{}] next pattern on {}", m_currentBeat.toString(), m_sequence.currentPatternStart().toString());
        if (m_currentBeat == m_sequence.currentPatternStart()) {
            nextPattern();
        }
        pump();
    }
    m_midiOutput->stopPlayback();
}

void Heart::nextPattern() {
    m_midiOutput->selectPattern(m_sequence.currentPatternID());
    onNextPattern(m_currentBeat.toString(), m_sequence.currentPatternID(), m_sequence.currentPatternName());
    m_sequence.nextPattern();
}

void Heart::pump() {
    m_midiOutput->sendSync();

    long elapsedTime = 0;
    std::chrono::high_resolution_clock::time_point begin;
    std::chrono::high_resolution_clock::time_point end;

    while (elapsedTime < m_interval - m_intervalDrift) {
        begin = std::chrono::high_resolution_clock::now();
        std::this_thread::sleep_for(std::chrono::microseconds(250));
        end = std::chrono::high_resolution_clock::now();
        elapsedTime += std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
    }
    m_intervalDrift = (m_intervalDrift + elapsedTime - m_interval) / 2;

    m_currentBeat.tick();
}
