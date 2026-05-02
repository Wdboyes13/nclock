#include "clock.hpp"

void App::do_kbdb_win() {
    auto overlay = create_overlay();

    int dh = wsz.r - 20, dw = wsz.c - 20;
    WINDOW* dialog = newwin(dh, dw, 10, 10);
    wbkgd(dialog, COLOR_PAIR(CPAIR_OVERLAY));
    box(dialog, 0, 0);
    mvwprintw(dialog, 1, 2, "Keybinds");

    mvwprintw(dialog, 3, 2, "Show keybinds: CTRL + K");
    mvwprintw(dialog, 4, 2, "Quit or close dialogue: CTRL + Q");
    mvwprintw(dialog, 5, 2, "Open font change menu: F");
    
    keypad(dialog, true);

    wrefresh(dialog);

    while (true) {
        int c = wgetch(dialog);
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