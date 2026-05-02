#include <form.h>
#include "clock.hpp"

void App::do_new_timezone() {
    auto overlay = create_overlay();

    int dh = 15, dw = 45;
    WINDOW* dialog = newwin(dh, dw, (wsz.r - dh) / 2, (wsz.c - dw) / 2);
    wbkgd(dialog, COLOR_PAIR(CPAIR_OVERLAY));
    box(dialog, 0, 0);
    mvwprintw(dialog, 2, 3, "Enter UTC offset");

    FIELD* fields[] = { new_field(1, 39, 0, 0, 0, 0), nullptr };
    set_field_back(fields[0], A_UNDERLINE);
    field_opts_off(fields[0], O_AUTOSKIP);

    FORM* form = new_form(fields);
    WINDOW* fsub = derwin(dialog, 1, 39, 4, 3);
    set_form_win(form, dialog);
    set_form_sub(form, fsub);
    post_form(form);
    keypad(dialog, true);

    curs_set(true);

    ::refresh();
    wrefresh(dialog);

    while (true) {
        int c = wgetch(dialog);
        switch (c) {
            case '\n':
                goto done;
            case ctrl('q'):
                goto done;
            case KEY_BACKSPACE:
            case 127:
                form_driver(form, REQ_DEL_PREV);
                break;
            case KEY_LEFT:
                form_driver(form, REQ_PREV_CHAR);
                break;
            case KEY_RIGHT:
                form_driver(form, REQ_NEXT_CHAR);
                break;
            default:
                form_driver(form, c);
                break;
        }
        wrefresh(dialog);
    }

done:

    form_driver(form, REQ_VALIDATION);
    std::string offstr = field_buffer(fields[0], 0);

    size_t last_char = offstr.find_last_not_of(' ');
    if (last_char != std::string::npos) {
        offstr.erase(last_char + 1);
    } else {
        offstr.clear();
    }

    unpost_form(form);
    free_form(form);
    free_field(fields[0]);
    delwin(fsub);
    delwin(dialog);
    delwin(overlay);
    curs_set(false);

    touchwin(stdscr);
    touchwin(twin);
    touchwin(barwin);
    wrefresh(twin);
    ::refresh();

    if (!offstr.empty()) {
        set_tz_from_offset(tzstr_to_offset(offstr));
    } else {
        do_error("No offset specified");
    }
}