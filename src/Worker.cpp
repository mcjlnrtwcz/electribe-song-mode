#include "Heart.hpp"
#include "MIDIOutput.hpp"
#include "Sequence.hpp"
#include "Worker.hpp"

#include "spdlog/spdlog.h"

#include <memory>
#include <string>

void onNextPattern(std::string beat, unsigned int patternID, std::string patternName) {
    spdlog::get("logger")->info("[{}] Changing pattern to id: {}, name: {}", beat, patternID,patternName);
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
            spdlog::get("logger")->debug("Worker finished.");
            m_jobScheduled = false;
        }
    }
}

void Worker::startJob() {
    if (!m_jobScheduled) {
        m_jobScheduled = true;
        spdlog::get("logger")->debug("New job started.");
    }
}

void Worker::stopJob() {
    if (m_jobScheduled) {
        m_heart.requestStop();
        spdlog::get("logger")->debug("Stop requested.");
    }
}
