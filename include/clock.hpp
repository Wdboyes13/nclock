#include <ncurses.h>
#include <ctime>
#include <functional>
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

    Rect twin_sz;
    WINDOW *twin, *barwin;
    clock_t last_refresh;
    figlet fig;
    std::string font_path;
    WinSz wsz;
};