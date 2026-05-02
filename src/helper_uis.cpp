#include "clock.hpp"

WINDOW* App::create_overlay() {
    WINDOW* overlay = newwin(wsz.r, wsz.c, 0, 0);
    wbkgd(overlay, COLOR_PAIR(app_constants::CPAIR_OVERLAY));
    for (int r = 0; r < wsz.r; r++) {
        for (int c = 0; c < wsz.c; c++) {
            mvwaddch(overlay, r, c, ' ' | A_DIM);
        }
    }
    return overlay;
}

void App::do_error(const char* err) {
    const auto overlay = create_overlay();
    const int dh = 15;
    const int dw = 45;
    WINDOW* dialog = newwin(dh, dw, (wsz.r - dh) / 2, (wsz.c - dw) / 2);
    wbkgd(dialog, COLOR_PAIR(app_constants::CPAIR_OVERLAY));
    box(dialog, 0, 0);
    cblock(dialog, app_constants::CPAIR_ERR, [&]() {
        mvwprintw(dialog, 2, 3, "!!Error!!");
    });
    mvwprintw(dialog, 3, 5, err);

    const int btn_row = dh - 3;
    const int btn_col = (dw - 6) / 2;
    wattron(dialog, A_REVERSE);
    mvwprintw(dialog, btn_row, btn_col, "[ OK ]");
    wattroff(dialog, A_REVERSE);

    keypad(dialog, true);
    wrefresh(dialog);

    while (true) {
        const int c = wgetch(dialog);
        if (c == '\n' || c == ' ' || c == ctrl('q')) {
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