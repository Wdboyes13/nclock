#include <ncurses.h>
#include <ctime>
#include "clock.hpp"

int App::run() {
    this->refresh();

    while (true) {
        const int ch = getch();
        if (ch == ctrl('q')) {
            break;
        } else if (ch == KEY_RESIZE) {
            getmaxyx(stdscr, wsz.r, wsz.c);
            if (barwin) delwin(barwin);
            if (twin) delwin(twin);
            init_ncurses();
        } else if (ch == ctrl('k')) {
            this->do_kbdb_win();
        } else if (ch == 'f') {
            this->do_new_fontload();
        } else if (ch == 'd') {
            this->load_font("./standard.flf");
        }

        const uint64_t dms = static_cast<uint64_t>(clock() - last_refresh) / (CLOCKS_PER_SEC / 1000);
        if (dms >= 500) {
            this->refresh();
        }
    }

    return 0;
}

int main(int argc, char* argv[]) {
    App app(argc, argv);
    return app.run();
}