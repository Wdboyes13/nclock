#include <clock.hpp>
#include <cstdint>
#include <thread>

#define DLG_H 15
#define DLG_W 45
#define FIELD_W 39

void App::toggle_timer() {
    if (timer_running) {
        timer_running = false;
    } else {
        if (timer_expired) {
            timer_expired = false;
        }
        timer_end = std::chrono::steady_clock::now() + timer_duration;
        timer_running = true;
    }
}

void App::reset_timer() {
    timer_running = false;
    timer_expired = false;
}

void App::update_timer() {
    if (timer_running) {
        auto now = std::chrono::steady_clock::now();
        if (now >= timer_end) {
            timer_running = false;
            timer_expired = true;
            std::thread([]() {
                for (int i = 0; i < 3; i++) {
                    beep();
                }
            });
        }
    }
}

void App::getlen_timer() {
    auto overlay = create_overlay();
    WINDOW* dialog = newwin(DLG_H, DLG_W, (wsz.r - DLG_H) / 2, (wsz.c - DLG_W) / 2);
    wbkgd(dialog, COLOR_PAIR(CPAIR_OVERLAY));
    box(dialog, 0, 0);

    mvwprintw(dialog, 2, 3, "Enter timer duration");
    mvwprintw(dialog, 4, 3, "UP: Increment field");
    mvwprintw(dialog, 5, 3, "DOWN: Decrement field");
    mvwprintw(dialog, 6, 3, "LEFT: Move field selection to the left");
    mvwprintw(dialog, 7, 3, "RIGHT: Move field selection to the right");
    keypad(dialog, true);
    wrefresh(dialog);

    time_t dsecs = this->timer_duration.count() / 1000;
    Time newtime;
    newtime.h = dsecs / 3600;
    newtime.m = (dsecs % 3600) / 60;
    newtime.s = dsecs % 60;

    enum { HR,
           MIN,
           SEC } curr_field = HR;

    auto cfield = [&]() -> uint64_t* {
        switch (curr_field) {
            case HR:
                return &newtime.h;
            case MIN:
                return &newtime.m;
            case SEC:
                return &newtime.s;
        }
    };

    auto field_at_max = [&]() -> bool {
        switch (curr_field) {
            case HR:
                if (newtime.h >= 99) {
                    return true;
                }
                break;
            case MIN:
                if (newtime.m >= 59) {
                    return true;
                }
                break;
            case SEC:
                if (newtime.s >= 59) {
                    return true;
                }
                break;
        }
        return false;
    };

    bool done = false;
    while (!done) {
        size_t printed = (DLG_W - 8) / 2;
        auto write_field = [&](uint64_t* field) {
            if (field == cfield()) {
                cblock(dialog, CPAIR_HIGHLIGHT, [&]() {
                    mvwprintw(dialog, 10, printed, "%02llu", *field);
                });
            } else {
                printed += mvwprintw(dialog, 10, printed, "%02llu", *field);
            }
            printed += 2;
        };

        write_field(&newtime.h);
        mvwprintw(dialog, 10, printed, ":");
        printed += 1;

        write_field(&newtime.m);
        mvwprintw(dialog, 10, printed, ":");
        printed += 1;

        write_field(&newtime.s);

        wrefresh(dialog);

        int c = wgetch(dialog);
        switch (c) {
            case '\n':
            case ctrl('q'):
                done = true;
                break;
            case KEY_LEFT:
                switch (curr_field) {
                    case HR:
                        break;
                    case MIN:
                        curr_field = HR;
                        break;
                    case SEC:
                        curr_field = MIN;
                        break;
                }
                break;
            case KEY_RIGHT:
                switch (curr_field) {
                    case HR:
                        curr_field = MIN;
                        break;
                    case MIN:
                        curr_field = SEC;
                        break;
                    case SEC:
                        break;
                }
                break;
            case KEY_UP:
                if (!field_at_max()) {
                    *(cfield()) += 1;
                }
                break;
            case KEY_DOWN:
                if (*(cfield()) <= 0) {
                    *(cfield()) = 0;
                } else {
                    *(cfield()) -= 1;
                }
                break;
        }
    }

    delwin(dialog);
    delwin(overlay);

    curs_set(false);

    touchwin(stdscr);
    touchwin(twin);
    touchwin(barwin);

    wrefresh(twin);
    ::refresh();

    uint64_t newtime_s = (newtime.h * 3600) + (newtime.m * 60) + newtime.s;
    this->timer_duration = std::chrono::milliseconds(std::chrono::seconds(newtime_s));

    this->reset_timer();
}