#include "MIDIOutput.hpp"

#include "RtMidi.h"
#include "spdlog/spdlog.h"

#include <memory>
#include <string>
#include <vector>

MIDIOutput::MIDIOutput() :
    m_midiOutput(std::make_shared<RtMidiOut>()) {
    // Empty.
}

MIDIOutput::~MIDIOutput() {
    if (m_midiOutput->isPortOpen()) m_midiOutput->closePort();
}

std::vector<std::string> MIDIOutput::getDevices() const {
    std::vector<std::string> devices;

    unsigned int portCount = m_midiOutput->getPortCount();
    if (portCount > 0) {
        for (unsigned int i = 0; i < portCount; ++i) {
            devices.push_back(m_midiOutput->getPortName(i));
        }
    }

    return devices;
}

bool MIDIOutput::selectDevice(unsigned int a_deviceID) {
    if (m_midiOutput->isPortOpen()) m_midiOutput->closePort();

    if (a_deviceID > m_midiOutput->getPortCount() - 1) {
        return false;
    } else {
        m_deviceID = a_deviceID;
        // Open port.
        try {
            m_midiOutput->openPort(m_deviceID);
            return true;
        } catch (RtMidiError &error) {
            spdlog::get("logger")->warn("RtMidi error: {}", error.getMessage());
            return false;
        }
    }
}

bool MIDIOutput::sendSync() {
    std::vector<unsigned char> message;
    message.push_back(0xF8);  // 2-2 SYSTEM REALTIME MESSAGES, Timing Clock
    try {
        m_midiOutput->sendMessage(&message);
        return true;
    } catch (RtMidiError &error) {
        spdlog::get("logger")->warn("RtMidi error: {}", error.getMessage());
        return false;
    }
}

bool MIDIOutput::selectPattern(unsigned int a_pattern) {
    unsigned int bank = 0;
    std::vector<unsigned char> message;

    // Determine bank.
    if (a_pattern > 127) {
        a_pattern -= 128;
        bank = 1;
    }

    // Select bank.
    message.push_back(0xB0);  // 2-1 CHANNEL MESSAGES, Bank Select (MSB)
    message.push_back(0);
    message.push_back(0);
    try {
        m_midiOutput->sendMessage(&message);
    } catch (RtMidiError &error) {
        spdlog::get("logger")->warn("RtMidi error: {}", error.getMessage());
        return false;
    }
    message.clear();
    message.push_back(0xB0);  // 2-1 CHANNEL MESSAGES, Bank Select (LSB)
    message.push_back(0x20);
    message.push_back(bank);
    try {
        m_midiOutput->sendMessage(&message);
    } catch (RtMidiError &error) {
        spdlog::get("logger")->warn("RtMidi error: {}", error.getMessage());
        return false;
    }

    // Select pattern.
    message.clear();
    message.push_back(0xC0);  // 2-1 CHANNEL MESSAGES, Program Change
    message.push_back(a_pattern - 1);
    try {
        m_midiOutput->sendMessage(&message);
        return true;
    } catch (RtMidiError &error) {
        spdlog::get("logger")->warn("RtMidi error: {}", error.getMessage());
        return false;
    }
}

bool MIDIOutput::startPlayback() {
    std::vector<unsigned char> message;
    message.push_back(0xFA);  // 2-2 SYSTEM REALTIME MESSAGES, Start
    try {
        m_midiOutput->sendMessage(&message);
        return true;
    } catch (RtMidiError &error) {
        spdlog::get("logger")->warn("RtMidi error: {}", error.getMessage());
        return false;
    }
}

bool MIDIOutput::stopPlayback() {
    std::vector<unsigned char> message;
    message.push_back(0xFC);  // 2-2 SYSTEM REALTIME MESSAGES, Stop
    try {
        m_midiOutput->sendMessage(&message);
        return true;
    } catch (RtMidiError &error) {
        spdlog::get("logger")->warn("RtMidi error: {}", error.getMessage());
        return false;
    }
}
