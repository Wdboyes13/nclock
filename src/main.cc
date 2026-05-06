#include <ncurses.h>
#include <chrono>
#include <exception>
#include <iostream>

#include "clock.hpp"

#define INPUT_TIMEOUT_MS 100
#define REFRESH_INTERVAL_MS 100

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
                case ctrl('n'):
                    current_mode = Mode::NORMAL;
                    break;
                case ctrl('s'):
                    current_mode = Mode::STOPWATCH;
                    break;
                case ctrl('m'):
                    current_mode = Mode::TIMER;
                    break;
                case ' ':
                    if (current_mode == Mode::STOPWATCH) {
                        this->toggle_stopwatch();
                    } else if (current_mode == Mode::TIMER) {
                        this->toggle_timer();
                    }
                    break;
                case ctrl('r'):
                    if (current_mode == Mode::STOPWATCH) {
                        this->reset_stopwatch();
                    } else if (current_mode == Mode::TIMER) {
                        this->reset_timer();
                    }
                    break;
            }
        }

        this->update_timer();

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
