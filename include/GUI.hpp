#ifndef GUI_HPP
#define GUI_HPP

#include "Worker.hpp"

#include <FL/Fl_Widget.H>
#include <FL/Fl_Window.H>

#include <memory>

class GUI {
public:
    GUI(std::shared_ptr<Worker> a_worker);
    void run();

private:
    std::shared_ptr<Fl_Window> m_window;
    std::shared_ptr<Fl_Window> m_deviceDialog;
    std::shared_ptr<Worker> m_worker;
    unsigned int m_selectedDeviceId = 0;
};

#endif
