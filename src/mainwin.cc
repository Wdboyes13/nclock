#include <format>
#include <sstream>
#include "clock.hpp"

int get_figlet_width(const std::string& fig_str) {
    std::istringstream ss(fig_str);
    std::string line;
    int max_w = 0;
    while (std::getline(ss, line)) {
        max_w = std::max(max_w, static_cast<int>(line.size()));
    }
    return max_w;
}

void App::refresh() {
    werase(twin);
    box(twin, 0, 0);

    const bool is_default_format = (format_str == "%H:%M:%S");
    const std::string display_str = format_time();
    const auto fig_str = fig(display_str);
    const int total_w = get_figlet_width(fig_str);
    const int row = (twin_sz.h - 2 - static_cast<int>(fig.get_font()->get_height())) / 2 + 1;
    const int start_col = (twin_sz.w - 2 - total_w) / 2 + 1;

    if (is_default_format) {
        const auto time = curr_time();
        const auto colon = fig(":");
        const int colonuse = colused(colon);
        const auto h_txt = fig(std::format("{:02}", time.h));
        const auto m_txt = fig(std::format("{:02}", time.m));
        const auto s_txt = fig(std::format("{:02}", time.s));

        int ccol = start_col;

        cblock(twin, app_constants::CPAIR_HR, [&]() {
            mvwprintfig(twin, row, ccol, h_txt);
            ccol += colused(h_txt);
        });

        mvwprintfig(twin, row, ccol, colon);
        ccol += colonuse;

        cblock(twin, app_constants::CPAIR_MIN, [&]() {
            mvwprintfig(twin, row, ccol, m_txt);
            ccol += colused(m_txt);
        });

        mvwprintfig(twin, row, ccol, colon);
        ccol += colonuse;

        cblock(twin, app_constants::CPAIR_SEC, [&]() {
            mvwprintfig(twin, row, ccol, s_txt);
        });
    } else {
        mvwprintfig(twin, row, start_col, fig_str);
    }

    cblock(barwin, app_constants::CPAIR_BAR, [&]() {
        const std::string color_string = (has_colors()) ? "COLORED" : "NO COLOR";
        const std::string font_string = fs::path(font_path).filename().c_str();
        const std::string tz_string = std::format("local ({})", get_utc_offset_string());
        const std::string fmt_string = std::format("fmt: {}", format_str);

        mvwprintw(barwin, 0, 0, " %s | %s | %s | %s | ctrl+k: view keybinds", 
                  color_string.c_str(), tz_string.c_str(), font_string.c_str(), fmt_string.c_str());
    });

    ::refresh();
    wrefresh(twin);
    wrefresh(barwin);
    last_refresh = clock();
}