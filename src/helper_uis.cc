#include "clock.hpp"

WINDOW* App::create_overlay() {
    WINDOW* overlay = newwin(wsz.r, wsz.c, 0, 0);
    wbkgd(overlay, COLOR_PAIR(CPAIR_OVERLAY));

    werase(overlay);
    wrefresh(overlay);
    return overlay;
}

void App::do_error(const char* err) {
    try {
        auto overlay = create_overlay();
        int dh = 15, dw = 45;
        WINDOW* dialog = newwin(dh, dw, (wsz.r - dh) / 2, (wsz.c - dw) / 2);
        wbkgd(dialog, COLOR_PAIR(CPAIR_OVERLAY));
        box(dialog, 0, 0);
        cblock(dialog, CPAIR_ERR, [&]() {
            mvwprintw(dialog, 2, 3, "!!Error!!");
        });
        mvwprintw(dialog, 3, 5, err);

        int btn_row = dh - 3, btn_col = (dw - 6) / 2;
        wattron(dialog, A_REVERSE);
        mvwprintw(dialog, btn_row, btn_col, "[ OK ]");
        wattroff(dialog, A_REVERSE);

        keypad(dialog, true);
        wrefresh(dialog);

        while (true) {
            int c = wgetch(dialog);
            if (c == '\n' || c == ' ' || c == ctrl('q')) {
                break;
            }
        }

        delwin(dialog);
        delwin(overlay);

        touchwin(stdscr);
        touchwin(barwin);
        if (twin) {
            touchwin(twin);
            wrefresh(twin);
        }
        ::refresh();
    } catch (std::exception& e) {
        endwin();
        printf("Fatal error: could not show error window");
        std::exit(1);
    }
}