#include "GUI.hpp"
#include "Worker.hpp"

#include <memory>

int main() {
    std::shared_ptr<Worker> worker = std::make_shared<Worker>();
    worker->run();

    GUI gui(worker);
    gui.run();

    return 0;
}
