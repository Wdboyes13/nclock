#include <clock.hpp>

void App::toggle_timer() {
    if (timer_running) {
        timer_running = false;
    } else {
        if (timer_expired) {
            timer_expired = false;
        }
        timer_end = std::chrono::steady_clock::now() + timer_duration;
        timer_running = true;
    }
}

void App::reset_timer() {
    timer_running = false;
    timer_expired = false;
}

void App::update_timer() {
    if (timer_running) {
        auto now = std::chrono::steady_clock::now();
        if (now >= timer_end) {
            timer_running = false;
            timer_expired = true;
        }
    }
}