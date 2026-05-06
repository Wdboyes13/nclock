#include <algorithm>
#include <cmath>
#include <format>
#include <sstream>
#include <stdexcept>
#include "clock.hpp"

void App::set_tz_from_offset(long off) {
    int h = std::abs(off) / 3600;
    int m = (std::abs(off) % 3600) / 60;
    char sign = off >= 0 ? '-' : '+';
    auto tz = std::format("UTC{}{:02}:{:02}", sign, h, m);
    setenv("TZ", tz.c_str(), 1);
    tzset();
    tzoff = TzOff(off);
}

long App::tzstr_to_offset(const std::string& str) {
    int h = 0, m = 0;
    char sign;

    if (str.size() > 1 && (str[0] == '-' || str[0] == '+')) {
        if (sscanf(str.c_str(), "%c%d:%d", &sign, &h, &m) < 2) {
            throw std::runtime_error("Invalid offset format");
        }
    } else {
        sign = '+';
        if (sscanf(str.c_str(), "%d:%d", &h, &m) < 2) {
            throw std::runtime_error("Invalid offset format");
        }
    }

    long seconds = (h * 3600) + (m * 60);
    return sign == '-' ? -seconds : seconds;
}

Time App::curr_time() {
    auto ctime = time(nullptr);
    auto t = localtime(&ctime);
    return Time{ (uint64_t)t->tm_hour, (uint64_t)t->tm_min, (uint64_t)t->tm_sec };
}

void App::cblock(WINDOW* win, attr_t cpid, std::function<void()> fnc) {
    if (has_colors()) {
        wattron(win, COLOR_PAIR(cpid));
    }
    fnc();
    if (has_colors()) {
        wattroff(win, COLOR_PAIR(cpid));
    }
}

int App::colused(const std::string& str) {
    int max_cols = 0;
    std::istringstream stream(str);
    std::string line;

    while (std::getline(stream, line)) {
        max_cols = std::max(max_cols, static_cast<int>(line.size()));
    }

    return max_cols;
}

void App::mvwprintfig(WINDOW* win, int row, int col, const std::string& fig_str) {
    std::istringstream ss(fig_str);
    std::string line;
    int r = row;
    while (std::getline(ss, line)) {
        mvwprintw(win, r++, col, "%s", line.c_str());
    }
}

long App::local_utcoff() {
    auto now = time(NULL);
    auto t = localtime(&now);
    char buf[6];
    strftime(buf, sizeof(buf), "%z", t);
    
    std::string tz(buf);
    if (tz.length() == 5) {
        int hours = std::stoi(tz.substr(1, 2));
        int minutes = std::stoi(tz.substr(3, 2));
        long offset = (hours * 3600) + (minutes * 60);
        return tz[0] == '-' ? -offset : offset;
    }
    return 0;
}

std::string App::format_tzoff(long off_sec) {
    char sign = off_sec >= 0 ? '+' : '-';
    long abs_off = std::abs(off_sec);
    int hours = abs_off / 3600;
    int minutes = (abs_off % 3600) / 60;
    return std::format("{}{:02}:{:02}", sign, hours, minutes);
}

WINDOW* App::newwin(int nlines, int ncols, int begin_y, int begin_x) {
    WINDOW* win = ::newwin(nlines, ncols, begin_y, begin_x);
    if (!win) {
        throw std::runtime_error("Cannot create window");
    }
    return win;
}