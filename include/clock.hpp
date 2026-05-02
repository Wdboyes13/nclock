#pragma once

#include <filesystem>
#include <functional>
#include <ncurses.h>
#include <string>
#include <ctime>
#include <sstream>

#include "libfiglet.hpp"
#include "timeutils.hpp"

using srilakshmikanthanp::libfiglet::Figlet;
using srilakshmikanthanp::libfiglet::FlfFont;
using srilakshmikanthanp::libfiglet::FullWidth;

namespace fs = std::filesystem;

namespace app_constants {
    constexpr int CPAIR_HR = 1;
    constexpr int CPAIR_ERR = 1;
    constexpr int CPAIR_MIN = 2;
    constexpr int CPAIR_SEC = 3;
    constexpr int CPAIR_BAR = 4;
    constexpr int CPAIR_OVERLAY = 5;
}

#ifndef ctrl
#    define ctrl(x) ((x) & 0x1f)
#endif

struct Rect {
    int x{}, y{}, w{}, h{};
};

struct Time {
    int h{}, m{}, s{};
};

struct WinSz {
    int r{}, c{};
};

class App {
public:
    App();
    App(int argc, char* argv[]);
    ~App();
    int run();

private:
    void parse_args(int argc, char* argv[]);
    std::string format_time();
    Time curr_time();
    void cblock(WINDOW* win, attr_t cpid, std::function<void()> fnc);
    int colused(const std::string& str);
    void mvwprintfig(WINDOW* win, int row, int col, const std::string& fig_str);
    std::string get_utc_offset_string();
    void refresh();
    WINDOW* create_overlay();
    void do_error(const char* err);
    void do_kbdb_win();
    void do_new_fontload();
    void load_font(const std::string& path);
    void init_ncurses();

    Rect twin_sz;
    WINDOW *twin{nullptr};
    WINDOW *barwin{nullptr};
    clock_t last_refresh{};
    Figlet fig;
    std::string font_path;
    WinSz wsz;
    std::string format_str{"%H:%M:%S"};
};