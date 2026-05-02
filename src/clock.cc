#include <ncurses.h>
#include <chrono>
#include <exception>
#include <iostream>

#include "clock.hpp"

int App::run() {
    this->refresh();

    timeout(100);

    auto last_tick = std::chrono::steady_clock::now();

    while (true) {
        int c = getch();
        if (c == ctrl('q')) {
            break;
        } else if (c == ctrl('k')) {
            this->do_kbdb_win();
        } else if (c == ctrl('f')) {
            this->do_new_fontload();
        } else if (c == ctrl('d')) {
            this->load_font(EMBEDDED_FONT);
        } else if (c == ctrl('t')) {
            this->do_new_timezone();
        } else if (c == ctrl('u')) {
            this->set_tz_from_offset(0);
            tzoff = TzOff(TzOff::UTC);
        } else if (c == ctrl('l')) {
            this->set_tz_from_offset(local_off);
            tzoff = TzOff(TzOff::LOCAL);
        }

        auto now = std::chrono::steady_clock::now();
        auto dms = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_tick).count();
        
        if (dms >= 500) {
            this->refresh();
            last_tick = now;
        }
    }

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
