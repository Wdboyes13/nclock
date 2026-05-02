#include <form.h>
#include <exception>
#include "clock.hpp"
#include "efont.hpp"

void App::do_new_fontload() {
    auto overlay = create_overlay();

    int dh = 15, dw = 45;
    WINDOW* dialog = newwin(dh, dw, (wsz.r - dh) / 2, (wsz.c - dw) / 2);
    wbkgd(dialog, COLOR_PAIR(CPAIR_OVERLAY));
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
    std::string path = field_buffer(fields[0], 0);    

    size_t last_char = path.find_last_not_of(' ');
    if (last_char != std::string::npos) {
        path.erase(last_char + 1);
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
    if (fs::exists(path) || path == EMBEDDED_FONT) {
        try {
            if (path == EMBEDDED_FONT) {
                std::istringstream iss{ reinterpret_cast<char*>(standard_flf) };
                fig->set_font(flf_font::make_shared(iss));
            } else {
                auto new_font = flf_font::make_shared(path);
                fig->set_font(new_font);
            }

            werase(twin);
            wrefresh(twin);
            delwin(twin);
            twin = nullptr;

            const std::string test = (*fig)("88:88:88");
            int rendered_w = 0;
            {
                std::istringstream ss(test);
                std::string line;
                while (std::getline(ss, line)) {
                    rendered_w = std::max(rendered_w, (int)line.size());
                }
            }

            twin_sz.h = fig->get_font()->get_height() + 2;
            twin_sz.w = rendered_w + 10;
            twin_sz.y = (wsz.r - twin_sz.h) / 2;
            twin_sz.x = (wsz.c - twin_sz.w) / 2;

            twin = newwin(twin_sz.h, twin_sz.w, twin_sz.y, twin_sz.x);
            font_path = path;
        } catch (const std::exception& e) {
            std::string err_msg = "Invalid font format!";
            this->do_error(err_msg.c_str());
        }
    } else {
        this->do_error("Empty or bad path, will not set font");
    }
}
