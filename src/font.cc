#include <form.h>
#include <limits.h>
#include <exception>
#include "clock.hpp"
#include "efont.hpp"

#define DLG_H     15
#define DLG_W     45
#define FIELD_W   39
#define FONT_TEST "88:88:88"

void App::do_new_fontload() {
    auto overlay = create_overlay();

    WINDOW* dialog = newwin(DLG_H, DLG_W, (wsz.r - DLG_H) / 2, (wsz.c - DLG_W) / 2);
    wbkgd(dialog, COLOR_PAIR(CPAIR_OVERLAY));
    box(dialog, 0, 0);
    mvwprintw(dialog, 2, 3, "Enter path to font");

    FIELD* fields[] = { new_field(1, FIELD_W, 0, 0, 0, 0), nullptr };
    set_field_back(fields[0], A_UNDERLINE);
    field_opts_off(fields[0], O_AUTOSKIP | O_STATIC);
    set_max_field(fields[0], PATH_MAX);

    FORM* form = new_form(fields);
    WINDOW* fsub = derwin(dialog, 1, FIELD_W, 4, 3);
    set_form_win(form, dialog);
    set_form_sub(form, fsub);
    post_form(form);
    keypad(dialog, true);

    curs_set(true);
    wrefresh(dialog);

    bool done = false;
    while (!done) {
        int c = wgetch(dialog);
        switch (c) {
            case '\n':
            case ctrl('q'):
                done = true;
                break;
            case KEY_RESIZE:
                touchwin(dialog);
                wrefresh(dialog);
                break;
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
            case KEY_UP:
                form_driver(form, REQ_BEG_FIELD);
                break;
            case KEY_DOWN:
                form_driver(form, REQ_END_FIELD);
                break;
            default:
                if (c >= 32 && c < 127) {
                    form_driver(form, c);
                }
                break;
        }
        
        if (!done) {
            wrefresh(dialog);
        }
    }

    form_driver(form, REQ_VALIDATION);
    std::string path = field_buffer(fields[0], 0);

    if (auto end = path.find_last_not_of(' '); end != std::string::npos) {
        path.resize(end + 1);
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
    if (!fs::exists(path) && path != EMBEDDED_FONT) {
        this->do_error("Empty or bad path, will not set font");
        return;
    }

    try {
        if (path == EMBEDDED_FONT) {
            std::istringstream iss{ reinterpret_cast<char*>(standard_flf) };
            fig->set_font(flf_font::make_shared(iss));
        } else {
            fig->set_font(flf_font::make_shared(path));
        }

        werase(twin);
        wrefresh(twin);
        
        delwin(twin);
        twin = nullptr;

        const std::string test = (*fig)(FONT_TEST);
        int rendered_w = 0;
        {
            std::istringstream ss(test);
            std::string line;
            while (std::getline(ss, line)) {
                rendered_w = std::max(rendered_w, static_cast<int>(line.size()));
            }
        }

        twin_sz.h = fig->get_font()->get_height() + 2;
        twin_sz.w = rendered_w + 10;
        twin_sz.y = (wsz.r - twin_sz.h) / 2;
        twin_sz.x = (wsz.c - twin_sz.w) / 2;

        twin = newwin(twin_sz.h, twin_sz.w, twin_sz.y, twin_sz.x);
        font_path = path;
    } catch (const std::exception& e) {
        this->do_error("Invalid font format!");
    }
}
