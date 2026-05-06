#include <format>
#include <chrono>
#include "clock.hpp"

void App::refresh() {
    werase(twin);
    box(twin, 0, 0);

    Time time_to_display;

    if (current_mode == Mode::NORMAL) {
        time_to_display = curr_time();
    } else if (current_mode == Mode::STOPWATCH) {
        auto elapsed = stopwatch_elapsed;
        if (stopwatch_running) {
            elapsed += std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::steady_clock::now() - stopwatch_start);
        }
        auto total_seconds = elapsed.count() / 1000;
        time_to_display.h = total_seconds / 3600;
        time_to_display.m = (total_seconds % 3600) / 60;
        time_to_display.s = total_seconds % 60;
    } else if (current_mode == Mode::TIMER) {
        long total_seconds = 0;
        if (timer_running) {
            auto remaining = std::chrono::duration_cast<std::chrono::seconds>(
                timer_end - std::chrono::steady_clock::now()).count();
            if (remaining > 0) {
                total_seconds = remaining;
            } else {
                total_seconds = 0;
            }
        } else {
            if (timer_expired) {
                total_seconds = 0;
            } else {
                total_seconds = std::chrono::duration_cast<std::chrono::seconds>(timer_duration).count();
            }
        }
        time_to_display.h = total_seconds / 3600;
        time_to_display.m = (total_seconds % 3600) / 60;
        time_to_display.s = total_seconds % 60;
    }

    const auto colon = (*fig)(":");
    const auto colonuse = colused(colon);
    const auto h_txt = (*fig)(std::format("{:02}", time_to_display.h));
    const auto m_txt = (*fig)(std::format("{:02}", time_to_display.m));
    const auto s_txt = (*fig)(std::format("{:02}", time_to_display.s));

    int total_w = colused(h_txt) + colused(colon) + colused(m_txt) + colused(colon) + colused(s_txt);

    int ccol = (twin_sz.w - 2 - total_w) / 2 + 1;

    attr_t cp_hr = CPAIR_HR;
    attr_t cp_min = CPAIR_MIN;
    attr_t cp_sec = CPAIR_SEC;

    if (current_mode == Mode::TIMER && timer_expired) {
        cp_hr = CPAIR_ERR;
        cp_min = CPAIR_ERR;
        cp_sec = CPAIR_ERR;
    } else if (current_mode == Mode::STOPWATCH) {
        cp_hr = CPAIR_SEC;
        cp_min = CPAIR_SEC;
        cp_sec = CPAIR_SEC;
    } else if (current_mode == Mode::TIMER) {
        cp_hr = CPAIR_MIN;
        cp_min = CPAIR_MIN;
        cp_sec = CPAIR_MIN;
    }

    cblock(twin, cp_hr, [&]() {
        auto txt = (*fig)(std::format("{:02}", time_to_display.h));
        mvwprintfig(twin, 1, ccol, txt);
        ccol += colused(txt);
    });

    mvwprintfig(twin, 1, ccol, colon);
    ccol += colonuse;

    cblock(twin, cp_min, [&]() {
        auto txt = (*fig)(std::format("{:02}", time_to_display.m));
        mvwprintfig(twin, 1, ccol, txt);
        ccol += colused(txt);
    });

    mvwprintfig(twin, 1, ccol, colon);
    ccol += colonuse;

    cblock(twin, cp_sec, [&]() {
        auto txt = (*fig)(std::format("{:02}", time_to_display.s));
        mvwprintfig(twin, 1, ccol, txt);
        ccol += colused(txt);
    });

    cblock(barwin, CPAIR_BAR, [&]() {
        std::string mode_string;
        if (current_mode == Mode::NORMAL) {
            mode_string = "NORMAL";
        } else if (current_mode == Mode::STOPWATCH) {
            mode_string = "STOPWATCH";
        } else if (current_mode == Mode::TIMER) {
            mode_string = "TIMER";
        }

        std::string color_string = (has_colors()) ? "COLORED" : "NO COLOR";
        std::string font_string = (font_path == EMBEDDED_FONT) ? "standard (embedded)" : fs::path(font_path).filename().c_str();
        std::string tz_string;

        switch (tzoff.type) {
            case TzOff::LOCAL: {
                tz_string = std::format("local ({})", format_tzoff(local_utcoff()));
                break;
            }
            case TzOff::NONLOCAL: {
                tz_string = std::format("non-local ({})", format_tzoff(local_utcoff()));
                break;
            }
            case TzOff::UTC: {
                tz_string = "UTC (+00:00)";
                break;
            }
        }

        mvwprintw(barwin, 0, 0, " %s | %s | %s | %s | ctrl+k: view keybinds", mode_string.c_str(), color_string.c_str(), tz_string.c_str(), font_string.c_str());
    });

    ::refresh();
    wrefresh(twin);
    wrefresh(barwin);
}
