#include <form.h>
#include <string>
#include <exception>
#include "clock.hpp"

void App::do_new_fontload() {
    const auto overlay = create_overlay();

    const int dh = 15;
    const int dw = 45;
    WINDOW* dialog = newwin(dh, dw, (wsz.r - dh) / 2, (wsz.c - dw) / 2);
    wbkgd(dialog, COLOR_PAIR(app_constants::CPAIR_OVERLAY));
    box(dialog, 0, 0);
    mvwprintw(dialog, 2, 3, "Enter path to font");

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
    wrefresh(dialog);

    while (true) {
        const int c = wgetch(dialog);
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
    std::string path = field_buffer(fields[0], 0);
    
    const size_t last_non_space = path.find_last_not_of(' ');
    if (last_non_space != std::string::npos) {
        path = path.substr(0, last_non_space + 1);
    } else {
        path.clear();
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

    if (!path.empty()) {
        load_font(path);
    }
}

void App::load_font(const std::string& path) {
    if (fs::exists(path)) {
        try {
            const auto new_font = FlfFont::make_shared(path);
            fig.set_font(new_font);
            delwin(twin);

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
            font_path = path;
        } catch (const std::exception& e) {
            this->do_error("Invalid font format!");
        }
    } else {
        this->do_error("Empty or bad path, will not set font");
    }
}