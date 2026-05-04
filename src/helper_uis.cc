#include "clock.hpp"

WINDOW* App::create_overlay() {
    WINDOW* overlay = newwin(wsz.r, wsz.c, 0, 0);
    wbkgd(overlay, COLOR_PAIR(CPAIR_OVERLAY));

    werase(overlay);
    wrefresh(overlay);
    return overlay;
}

void App::do_error(const char* err) {
    const int old_curs = curs_set(0);

    try {
        const auto overlay = create_overlay();

        const int dh = 15, dw = 45;
        WINDOW* dialog = newwin(dh, dw, (wsz.r - dh) / 2, (wsz.c - dw) / 2);
        wbkgd(dialog, COLOR_PAIR(CPAIR_OVERLAY));
        box(dialog, 0, 0);
        
        cblock(dialog, CPAIR_ERR, [&]() {
            mvwprintw(dialog, 2, 3, "!!Error!!");
        });

        int err_row = 4;
        int err_col = 3;
        int max_msg_w = dw - 6;
        std::string err_msg = err;
        
        while (static_cast<int>(err_msg.size()) > max_msg_w) {
            mvwprintw(dialog, err_row++, err_col, "%-.*s", max_msg_w, err_msg.c_str());
            err_msg = err_msg.substr(max_msg_w);
        }
        
        if (!err_msg.empty()) {
            mvwprintw(dialog, err_row, err_col, "%s", err_msg.c_str());
        }

        const int btn_row = dh - 3;
        const int btn_col = (dw - 6) / 2;
        
        cblock(dialog, A_REVERSE, [&]() {
            mvwprintw(dialog, btn_row, btn_col, "[ OK ]");
        });

        wnoutrefresh(dialog);
        doupdate();
        keypad(dialog, true);
        flushinp();
        
        while (true) {
            const int c = wgetch(dialog);
            if (c == '\n' || c == ' ' || c == ctrl('q') || c == 27) {
                break;
            }
        }

        delwin(dialog);
        delwin(overlay);
        curs_set(old_curs);
        
        touchwin(stdscr);
        
        if (barwin) {
            touchwin(barwin);
        }
        
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
