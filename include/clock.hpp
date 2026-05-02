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
#include <ncurses.h>
#include <ctime>
#include <functional>
#include <optional>
#include <string>

#include "libfiglet.hpp"

namespace fs = std::filesystem;
using namespace srilakshmikanthanp::libfiglet;

#define CPAIR_HR 1
#define CPAIR_ERR 1
#define CPAIR_MIN 2
#define CPAIR_SEC 3
#define CPAIR_BAR 4
#define CPAIR_OVERLAY 5

#ifndef ctrl
#    define ctrl(x) ((x) & 0x1f)
#endif

struct Rect {
    int x, y, w, h;
};

struct Time {
    int h, m, s;
};

struct WinSz {
    int r, c;
};

struct TzOff {
    enum TzOffType { LOCAL,
                     UTC,
                     NONLOCAL } type;
    std::optional<long> off;
    TzOff(TzOffType type) : type(type), off(std::nullopt) {}
    TzOff(long off) : type(NONLOCAL), off(off) {}
};

class App {
  public:
    App();

    int run();

  private:
    Time curr_time();
    void cblock(WINDOW* win, attr_t cpid, std::function<void()> fnc);
    int colused(const std::string& str);
    void mvwprintfig(WINDOW* win, int row, int col, const std::string& fig_str);
    long local_utcoff();

    std::string format_tzoff(long off_sec);

    void refresh();

    WINDOW* create_overlay();
    void do_error(const char* err);

    void do_kbdb_win();

    void do_new_fontload();
    void load_font(const std::string& path);

    void do_new_timezone();
    void set_tz_from_offset(long off);
    long tzstr_to_offset(const std::string& str);

    Rect twin_sz;
    WINDOW *twin, *barwin;
    figlet fig;
    std::string font_path;
    WinSz wsz;
    TzOff tzoff;
    long local_off = 0;
};
