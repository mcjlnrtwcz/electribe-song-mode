#ifndef MIDIOUTPUT_HPP
#define MIDIOUTPUT_HPP

#include "RtMidi.h"

#include <memory>
#include <string>
#include <vector>

class MIDIOutput {
public:
    MIDIOutput();
    ~MIDIOutput();
    std::vector<std::string> getDevices() const;
    bool selectDevice(unsigned int a_deviceID);
    bool sendSync();
    bool selectPattern(unsigned int a_pattern);
    bool startPlayback();
    bool stopPlayback();
private:
    std::shared_ptr<RtMidiOut> m_midiOutput;
    int m_deviceID;
};

#endif
