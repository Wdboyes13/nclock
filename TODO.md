# TODO

## Completed
- `-f` / `--format` flag for custom strftime format strings

## List
- TimeZone Support
- Stopwatch mode (`--stopwatch`)
- Timer/countdown mode (`--timer`)

## Info
### TimeZone Support
Support for switching timezones. The program would bring up an input dialogue box, prompting the user to enter a UTC/GMT offset. The program would then validate it matches `[+-]\d{1,2}(?::\d{2})?`. The program would then store in its internal state the parsed time zone data. The program will show the current time zone in the bottom status bar. When the program fetches time, it will fetch the time for the set time zone.

The dialogue box will be made visible by striking the `t` (timezone) key. The time zone may be reset via the following methods:
1. `u` (utc) key - reset time zone to UTC/GMT
2. `l` (local) key - reset time zone to Local time (default)