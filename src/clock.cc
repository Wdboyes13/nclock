#include <ncurses.h>
#include <chrono>
#include <exception>
#include <iostream>

#include "clock.hpp"

using namespace srilakshmikanthanp::libfiglet;

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
        } else if (c == 'f') {
            this->do_new_fontload();
        } else if (c == 'd') {
            this->load_font("./standard.flf");
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
