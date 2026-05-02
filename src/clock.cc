#include <ncurses.h>
#include <ctime>

#include "clock.hpp"

using namespace srilakshmikanthanp::libfiglet;

int App::run() {
    this->refresh();

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

        uint64_t dms = (clock() - last_refresh) / (CLOCKS_PER_SEC / 1000);
        if (dms >= 500) {
            this->refresh();
        }
    }

    endwin();
    return 0;
}

int main() {
    auto app = new App;
    return app->run();
}