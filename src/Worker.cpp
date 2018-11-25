#include "Heart.hpp"
#include "MIDIOutput.hpp"
#include "Sequence.hpp"
#include "Worker.hpp"

#include <iomanip>  // Temporary.
#include <iostream>  // Debug.
#include <memory>
#include <string>  // Temporary.

void onNextPattern(std::string beat, unsigned int patternID, std::string patternName) {
    std::cout << "[DEBUG] [" << beat << "] Changing pattern to " << std::setfill('0') << std::setw(3) << patternID << " " << patternName << "\n";
}

Worker::Worker() :
    m_jobScheduled(false),
    m_midiOutput(std::make_shared<MIDIOutput>()),
    m_selectedMidiDevice(0) {
    // Empty.
}

void Worker::run() {
    m_thread = std::thread(&Worker::work, this);
    m_thread.detach();
}

void Worker::work() {
    while (true) {
        if (m_jobScheduled) {
            m_midiOutput->selectDevice(m_selectedMidiDevice);

            m_sequence.loadData(m_path);
            m_heart = Heart(m_sequence, m_midiOutput, onNextPattern);
            m_heart.run();
            // std::cout << "[DEBUG] Heart finished.\n";
            m_jobScheduled = false;
        }
    }
}

void Worker::startJob() {
    if (!m_jobScheduled) {
        m_jobScheduled = true;
        // std::cout << "[DEBUG] New job started.\n";
    }
}

void Worker::stopJob() {
    if (m_jobScheduled) {
        m_heart.requestStop();
        // std::cout << "[DEBUG] Stop requested.\n";
    }
}
