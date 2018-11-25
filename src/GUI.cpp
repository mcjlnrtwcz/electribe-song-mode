#include "GUI.hpp"

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_Hold_Browser.H>

#include <iostream>
#include <memory>
#include <vector>

GUI::GUI(std::shared_ptr<Worker> a_worker) :
    m_worker(a_worker),
    m_window(std::make_shared<Fl_Window>(176, 48, "electribe-song-mode")) {
    Fl_Button *openBtn = new Fl_Button(8, 8, 32, 32, "@fileopen");
    openBtn->callback([](Fl_Widget *w, void *instance) {
        ((GUI *)instance)->m_worker->setSequencePath(fl_file_chooser("", "*.json", ""));
    }, (void *)this);

    Fl_Button *deviceBtn = new Fl_Button(48, 8, 32, 32, "@search");

    Fl_Button *startBtn = new Fl_Button(96, 8, 32, 32, "@>");
    startBtn->callback([](Fl_Widget *w, void *instance) {
        ((GUI *)instance)->m_worker->startJob();
    }, (void *)this);

    Fl_Button *stopBtn = new Fl_Button(136, 8, 32, 32, "@square");
    stopBtn->callback([](Fl_Widget *w, void *instance) {
        ((GUI *)instance)->m_worker->stopJob();
    }, (void *)this);

    m_window->end();

    // MIDI output device selection dialog.
    m_deviceDialog = std::make_shared<Fl_Window>(256, 256, "Select MIDI output device");

    Fl_Hold_Browser *selector = new Fl_Hold_Browser(8, 8, 240, 200);
    selector->callback([](Fl_Widget *w, void *instance) {
        ((GUI *)instance)->m_selectedDeviceId = ((Fl_Hold_Browser *)w)->value() - 1;
    }, (void *)this);
    for (auto &device : m_worker->getMidiDevices()) {
        selector->add(device.c_str());
    }
    if (selector->size() > 0) {
        selector->value(1);
        m_worker->selectMidiDevice(0);
    }

    Fl_Button *okBtn = new Fl_Button(184, 216, 64, 32, "OK");
    okBtn->callback([](Fl_Widget *w, void *instance) {
        GUI *gui = ((GUI *)instance);
        gui->m_worker->selectMidiDevice(gui->m_selectedDeviceId);
        gui->m_deviceDialog->hide();
    }, (void *)this);

    m_deviceDialog->end();

    deviceBtn->callback([](Fl_Widget *w, void *instance) {
        ((GUI *)instance)->m_deviceDialog->show();
    }, (void *)this);
}

void GUI::run() {
    m_window->show();
    Fl::run();
}
