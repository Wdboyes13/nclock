#include <clock.hpp>

void App::toggle_stopwatch() {
    if (stopwatch_running) {
        stopwatch_elapsed += std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now() - stopwatch_start);
        stopwatch_running = false;
    } else {
        stopwatch_start = std::chrono::steady_clock::now();
        stopwatch_running = true;
    }
}

void App::reset_stopwatch() {
    stopwatch_running = false;
    stopwatch_elapsed = std::chrono::milliseconds(0);
}