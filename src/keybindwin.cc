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
    mvwprintw(dialog, 5, 2, "Open font change menu: CTRL + F");
    mvwprintw(dialog, 6, 2, "Change font to default: CTRL + D");
    mvwprintw(dialog, 7, 2, "Change time zone: CTRL + T");
    mvwprintw(dialog, 8, 2, "Change time zone to UTC: CTRL + U");
    mvwprintw(dialog, 9, 2, "Change time zone to Local: CTRL + L");
    mvwprintw(dialog, 11, 2, "Normal Mode: CTRL + N");
    mvwprintw(dialog, 12, 2, "Stopwatch Mode: CTRL + S");
    mvwprintw(dialog, 13, 2, "Timer Mode: CTRL + M");
    mvwprintw(dialog, 14, 2, "Start/Stop Timer/Stopwatch: Space");
    mvwprintw(dialog, 15, 2, "Reset Timer/Stopwatch: CTRL + R");

    ::refresh();
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
