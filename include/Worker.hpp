#ifndef WORKER_HPP
#define WORKER_HPP

#include "Heart.hpp"
#include "MIDIOutput.hpp"
#include "Sequence.hpp"

#include <atomic>
#include <string>
#include <thread>

class Worker {
public:
    Worker();
    void setSequencePath(std::string a_path) { m_path = a_path; }
    std::vector<std::string> getMidiDevices() const { return m_midiOutput->getDevices(); }
    void selectMidiDevice(unsigned int a_selectedMidiDevice) { m_selectedMidiDevice = a_selectedMidiDevice; }
    void run();
    void work();
    void startJob();
    void stopJob();
private:
    std::shared_ptr<MIDIOutput> m_midiOutput;  // This shouldn't be here.
    std::atomic<unsigned int> m_selectedMidiDevice;
    std::string m_path;
    std::thread m_thread;
    std::atomic<bool> m_jobScheduled;
    Heart m_heart;
    Sequence m_sequence;
};

#endif
