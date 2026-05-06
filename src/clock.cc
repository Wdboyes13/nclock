#include <ncurses.h>
#include <chrono>
#include <exception>
#include <iostream>

#include "clock.hpp"

#define INPUT_TIMEOUT_MS 100
#define REFRESH_INTERVAL_MS 100

void App::toggleStopwatch() {
    if (stopwatch_running) {
        stopwatch_elapsed += std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now() - stopwatch_start);
        stopwatch_running = false;
    } else {
        stopwatch_start = std::chrono::steady_clock::now();
        stopwatch_running = true;
    }
}

void App::resetStopwatch() {
    stopwatch_running = false;
    stopwatch_elapsed = std::chrono::milliseconds(0);
}

void App::toggleTimer() {
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

void App::resetTimer() {
    timer_running = false;
    timer_expired = false;
}

void App::updateTimer() {
    if (timer_running) {
        auto now = std::chrono::steady_clock::now();
        if (now >= timer_end) {
            timer_running = false;
            timer_expired = true;
        }
    }
}

int App::run() {
    this->refresh();

    timeout(INPUT_TIMEOUT_MS);
    keypad(stdscr, TRUE);

    auto last_tick = std::chrono::steady_clock::now();
    const auto tick = std::chrono::milliseconds(REFRESH_INTERVAL_MS);

    while (true) {
        int c = getch();

        if (c != ERR) {
            switch (c) {
                case ctrl('q'):
                    goto done;
                case KEY_RESIZE:
                    this->refresh();
                    break;
                case ctrl('k'):
                    this->do_kbdb_win();
                    break;
                case ctrl('f'):
                    this->do_new_fontload();
                    break;
                case ctrl('d'):
                    this->load_font(EMBEDDED_FONT);
                    break;
                case ctrl('t'):
                    this->do_new_timezone();
                    break;
                case ctrl('u'):
                    this->set_tz_from_offset(0);
                    tzoff = TzOff(TzOff::UTC);
                    break;
                case ctrl('l'):
                    this->set_tz_from_offset(local_off);
                    tzoff = TzOff(TzOff::LOCAL);
                    break;
                case 'n':
                    current_mode = Mode::NORMAL;
                    break;
                case 's':
                    current_mode = Mode::STOPWATCH;
                    break;
                case 't':
                    current_mode = Mode::TIMER;
                    break;
                case ' ':
                    if (current_mode == Mode::STOPWATCH) {
                        this->toggleStopwatch();
                    } else if (current_mode == Mode::TIMER) {
                        this->toggleTimer();
                    }
                    break;
                case 'r':
                    if (current_mode == Mode::STOPWATCH) {
                        this->resetStopwatch();
                    } else if (current_mode == Mode::TIMER) {
                        this->resetTimer();
                    }
                    break;
            }
        }

        this->updateTimer();

        auto now = std::chrono::steady_clock::now();
        if (now - last_tick >= tick || c != ERR) {
            this->refresh();
            last_tick = now;
        }
    }

done:
    endwin();
    return 0;
}

int main() {
    try {
        App app;
        return app.run();
    } catch (const std::exception& e) {
        endwin();
        std::cerr << "Fatal Error: " << e.what() << std::endl;
        return 1;
    }
}
