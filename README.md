# NClock

A terminal-based clock that displays time in large, colorful ASCII art. Built with C++20 and ncurses, NClock renders each digit using FIGlet fonts for maximum visual impact.

## Features

- **Large ASCII Time Display**: Time is rendered in big, beautiful FIGlet characters that fill your terminal
- **Color-Coded Time Units**: Hours (red), minutes (green), and seconds (blue) are displayed in distinct colors when your terminal supports it
- **Keyboard Controls**:
  - `Ctrl+K`: View keybindings overlay
  - `Ctrl+Q`: Quit the application
  - `F`: Open font change menu
  - `D`: Reset to default font
- **Status Bar**: Shows color mode, timezone info, and current font being used

## Building

You'll need a C++20 compatible compiler and the ncurses library:

```bash
make
```

To clean the build:

```bash
make clean
```

To build and run:

```bash
make run
```

## Usage

```bash
./nclock
```

### Command-line Options

```bash
./nclock -f "%H:%M:%S"     # Default format (24-hour time)
./nclock -f "%I:%M:%S %p"  # 12-hour time with AM/PM
./nclock -f "%Y-%m-%d"    # Date only (year-month-day)
./nclock -f "%H:%M:%S\n%A"  # Time with weekday on second line
```

The `-f` or `--format` flag accepts any [strftime format string](https://en.cppreference.com/w/cpp/io/manip/put_time).

The clock will fill your terminal with a large time display. Controls are shown in the status bar at the bottom.

## Dependencies

- **ncurses** - Terminal handling library
- **libfiglet** - FIGlet font rendering (included in `include/`)
- **standard.flf** - FIGlet font file included in the project root

## License

NClock is MIT licensed. This project includes:

- The FIGlet font `standard.flf` (BSD-3-Clause)
- libfiglet header files (MIT)

See `LICENSE.md` for full license details.

## TODO

- Timezone support with UTC/GMT offset input
- Custom font loading capability