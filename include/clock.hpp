#include <format>
#include "clock.hpp"

void App::refresh() {
    werase(twin);
    box(twin, 0, 0);

    auto time = curr_time();

    const auto colon = fig(":");
    const auto colonuse = colused(colon);
    const auto h_txt = fig(std::format("{:02}", time.h));
    const auto m_txt = fig(std::format("{:02}", time.m));
    const auto s_txt = fig(std::format("{:02}", time.s));

    int total_w = colused(h_txt) + colused(colon) + colused(m_txt) + colused(colon) + colused(s_txt);

    int ccol = (twin_sz.w - 2 - total_w) / 2 + 1;
    int row = (twin_sz.h - 2 - fig.get_font()->get_height()) / 2 + 1;

    cblock(twin, CPAIR_HR, [&]() {
        auto txt = fig(std::format("{:02}", time.h));
        mvwprintfig(twin, row, ccol, txt);
        ccol += colused(txt);
    });

    mvwprintfig(twin, row, ccol, colon);
    ccol += colonuse;

    cblock(twin, CPAIR_MIN, [&]() {
        auto txt = fig(std::format("{:02}", time.m));
        mvwprintfig(twin, row, ccol, txt);
        ccol += colused(txt);
    });

    mvwprintfig(twin, row, ccol, colon);
    ccol += colonuse;

    cblock(twin, CPAIR_SEC, [&]() {
        auto txt = fig(std::format("{:02}", time.s));
        mvwprintfig(twin, row, ccol, txt);
        ccol += colused(txt);
    });

    cblock(barwin, CPAIR_BAR, [&]() {
        std::string color_string = (has_colors()) ? "COLORED" : "NO COLOR";
        std::string font_string = fs::path(font_path).filename().string();
        std::string tz_string = std::format("local ({})", format_tzoff(local_utcoff()));

        mvwprintw(barwin, 0, 0, " %s | %s | %s | ctrl+k: view keybinds", color_string.c_str(), tz_string.c_str(), font_string.c_str());
    });

    ::refresh();
    wrefresh(twin);
    wrefresh(barwin);
}
