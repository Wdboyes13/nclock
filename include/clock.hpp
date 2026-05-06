#pragma once
#include <ncurses.h>
#include <ctime>
#include <functional>
#include <optional>
#include <string>
#include <chrono>

#include "libfiglet.hpp"

namespace fs = std::filesystem;
using namespace srilakshmikanthanp::libfiglet;

#define CPAIR_HR 1
#define CPAIR_ERR 1
#define CPAIR_MIN 2
#define CPAIR_SEC 3
#define CPAIR_BAR 4
#define CPAIR_OVERLAY 5

#define EMBEDDED_FONT "__embedded__"

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

enum class Mode {
    NORMAL,
    STOPWATCH,
    TIMER
};

class App {
  public:
    App();
    ~App();

    int run();

  private:
    Time curr_time();
    void cblock(WINDOW* win, attr_t cpid, std::function<void()> fnc);
    int colused(const std::string& str);
    void mvwprintfig(WINDOW* win, int row, int col, const std::string& fig_str);
    long local_utcoff();

    std::string format_tzoff(long off_sec);

    void refresh();
    WINDOW* newwin(int nlines, int ncols, int begin_y, int begin_x);

    WINDOW* create_overlay();
    void do_error(const char* err);

    void do_kbdb_win();

    void do_new_fontload();
    void load_font(const std::string& path);

    void do_new_timezone();
    void set_tz_from_offset(long off);
    long tzstr_to_offset(const std::string& str);

    void toggle_stopwatch();
    void reset_stopwatch();
    void toggle_timer();
    void reset_timer();
    void update_timer();

    Rect twin_sz;
    WINDOW *twin, *barwin;
    figlet* fig;
    std::string font_path;
    WinSz wsz;
    TzOff tzoff;
    long local_off = 0;

    Mode current_mode = Mode::NORMAL;

    std::chrono::steady_clock::time_point stopwatch_start;
    std::chrono::milliseconds stopwatch_elapsed{0};
    bool stopwatch_running = false;

    std::chrono::milliseconds timer_duration{std::chrono::minutes(5)};
    std::chrono::steady_clock::time_point timer_end;
    bool timer_running = false;
    bool timer_expired = false;
};
