#include "clock.hpp"
#include <cstdio>
#include <ctime>
#include <sstream>
#include <cctype>

Time App::curr_time() {
#ifdef _WIN32
    const auto ctime = time(nullptr);
    auto t = localtime(&ctime);
#else
    const auto ctime = time(nullptr);
    std::tm tm_buf;
    auto t = localtime_r(&ctime, &tm_buf);
#endif
    return Time{ t->tm_hour, t->tm_min, t->tm_sec };
}

std::string App::format_time() {
    const auto ctime = std::time(nullptr);
#ifdef _WIN32
    auto t = std::localtime(&ctime);
#else
    std::tm tm_buf;
    auto t = std::localtime_r(&ctime, &tm_buf);
#endif
    char buf[128];
    std::strftime(buf, sizeof(buf), format_str.c_str(), t);
    return std::string(buf);
}

void App::parse_args(int argc, char* argv[]) {
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if ((arg == "-f" || arg == "--format") && i + 1 < argc) {
            format_str = argv[++i];
        } else if (arg.find("-f") == 0 && arg.size() > 2) {
            format_str = arg.substr(2);
        } else if (arg.find("--format=") == 0) {
            format_str = arg.substr(8);
        }
    }
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
        const int w = wcswidth(ws.c_str(), static_cast<int>(ws.size()));
        max_cols = std::max(max_cols, w == -1 ? static_cast<int>(line.size()) : w);
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

std::string App::get_utc_offset_string() {
    return timeutils::get_formatted_utc_offset();
}