#include "clock.hpp"

App::App() : fig(flf_font::make_shared("./standard.flf"), full_width::make_shared()) {
    font_path = "./standard.flf";

    initscr();
    noecho();
    raw();
    nodelay(stdscr, true);
    curs_set(false);

    if (has_colors()) {
        start_color();
        init_pair(CPAIR_HR, COLOR_RED, COLOR_BLACK);
        init_pair(CPAIR_MIN, COLOR_GREEN, COLOR_BLACK);
        init_pair(CPAIR_SEC, COLOR_BLUE, COLOR_BLACK);
        init_pair(CPAIR_BAR, COLOR_BLACK, COLOR_WHITE);
        init_pair(CPAIR_OVERLAY, COLOR_WHITE, COLOR_BLACK);
    }

    getmaxyx(stdscr, wsz.r, wsz.c);

    const std::string test = fig("00:00:00");
    int rendered_w = 0;
    {
        std::istringstream ss(test);
        std::string line;
        while (std::getline(ss, line)) {
            rendered_w = std::max(rendered_w, (int)line.size());
        }
    }

    twin_sz.h = fig.get_font()->get_height() + 2;
    twin_sz.w = rendered_w + 10;
    twin_sz.y = (wsz.r - twin_sz.h) / 2;
    twin_sz.x = (wsz.c - twin_sz.w) / 2;

    twin = newwin(twin_sz.h, twin_sz.w, twin_sz.y, twin_sz.x);
    barwin = newwin(1, wsz.c, wsz.r - 1, 0);

    if (has_colors()) {
        wbkgd(barwin, COLOR_PAIR(CPAIR_BAR));
    }

    this->refresh();
}