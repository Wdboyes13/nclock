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