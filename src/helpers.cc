#include <algorithm>
#include <format>
#include "clock.hpp"

Time App::curr_time() {
    auto ctime = time(nullptr);
    auto t = localtime(&ctime);
    return Time{ t->tm_hour, t->tm_min, t->tm_sec };
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
        std::wstring ws(line.begin(), line.end());
        int w = wcswidth(ws.c_str(), ws.size());
        max_cols = std::max(max_cols, w == -1 ? (int)line.size() : w);
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
    auto time = localtime(&now);

    return time->tm_gmtoff;
}

std::string App::format_tzoff(long off_sec) {
    char sign = off_sec >= 0 ? '+' : '-';
    long abs_off = std::abs(off_sec);
    int hours = abs_off / 3600;
    int minutes = (abs_off % 3600) / 60;
    return std::format("{}{:02}:{:02}", sign, hours, minutes);
}