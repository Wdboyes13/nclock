#include "clock.hpp"
#include <sstream>

App::App() : fig(FlfFont::make_shared("./standard.flf"), FullWidth::make_shared()) {
    font_path = "./standard.flf";
    init_ncurses();
    this->refresh();
}

App::App(int argc, char* argv[]) : fig(FlfFont::make_shared("./standard.flf"), FullWidth::make_shared()) {
    font_path = "./standard.flf";
    parse_args(argc, argv);
    init_ncurses();
    this->refresh();
}

void App::init_ncurses() {
    initscr();
    noecho();
    raw();
    nodelay(stdscr, true);
    curs_set(false);

    if (has_colors()) {
        start_color();
        init_pair(app_constants::CPAIR_HR, COLOR_RED, COLOR_BLACK);
        init_pair(app_constants::CPAIR_MIN, COLOR_GREEN, COLOR_BLACK);
        init_pair(app_constants::CPAIR_SEC, COLOR_BLUE, COLOR_BLACK);
        init_pair(app_constants::CPAIR_BAR, COLOR_BLACK, COLOR_WHITE);
        init_pair(app_constants::CPAIR_OVERLAY, COLOR_WHITE, COLOR_BLACK);
        init_pair(app_constants::CPAIR_ERR, COLOR_WHITE, COLOR_RED); 
    }

    getmaxyx(stdscr, wsz.r, wsz.c);

    const std::string test = fig("00:00:00");
    int rendered_w = 0;
    {
        std::istringstream ss(test);
        std::string line;
        while (std::getline(ss, line)) {
            rendered_w = std::max(rendered_w, static_cast<int>(line.size()));
        }
    }

    twin_sz.h = static_cast<int>(fig.get_font()->get_height()) + 2;
    twin_sz.w = rendered_w + 10;
    twin_sz.y = (wsz.r - twin_sz.h) / 2;
    twin_sz.x = (wsz.c - twin_sz.w) / 2;

    twin = newwin(twin_sz.h, twin_sz.w, twin_sz.y, twin_sz.x);
    barwin = newwin(1, wsz.c, wsz.r - 1, 0);

    if (has_colors()) {
        wbkgd(barwin, COLOR_PAIR(app_constants::CPAIR_BAR));
    }
}

App::~App() {
    if (barwin) delwin(barwin);
    if (twin) delwin(twin);
    endwin();
}