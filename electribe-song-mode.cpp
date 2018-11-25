#include "GUI.hpp"
#include "Worker.hpp"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include <memory>

int main() {
    auto console = spdlog::stdout_color_mt("logger");

    std::shared_ptr<Worker> worker = std::make_unique<Worker>();
    worker->run();

    GUI gui(worker);
    gui.run();

    return 0;
}
