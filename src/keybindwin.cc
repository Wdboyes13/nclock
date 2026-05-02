#include "clock.hpp"

void App::do_kbdb_win() {
    const auto overlay = create_overlay();
    const int dh = wsz.r - 20;
    const int dw = wsz.c - 20;
    WINDOW* dialog = newwin(dh, dw, 10, 10);
    wbkgd(dialog, COLOR_PAIR(app_constants::CPAIR_OVERLAY));
    box(dialog, 0, 0);
    mvwprintw(dialog, 1, 2, "Keybinds");

    mvwprintw(dialog, 3, 2, "Show keybinds: CTRL + K");
    mvwprintw(dialog, 4, 2, "Quit or close dialogue: CTRL + Q");
    mvwprintw(dialog, 5, 2, "Open font change menu: F");
    
    keypad(dialog, true);
    wrefresh(dialog);

    while (true) {
        const int c = wgetch(dialog);
        if (c == ctrl('q')) {
            break;
        }
    }

    delwin(dialog);
    delwin(overlay);

    touchwin(stdscr);
    touchwin(twin);
    touchwin(barwin);
    wrefresh(twin);
    ::refresh();
}