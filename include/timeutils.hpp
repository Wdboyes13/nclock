/*
 * Cross-platform UTC offset formatting utility
 * 
 * Formats UTC offsets with colon separator (e.g., +05:30)
 * Works on Windows, Linux, and macOS without platform-specific format specifiers.
 */

#pragma once

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>

namespace timeutils {

inline std::string format_offset_seconds(int offset_seconds) {
    char sign = (offset_seconds >= 0) ? '+' : '-';
    int abs_seconds = (offset_seconds >= 0) ? offset_seconds : -offset_seconds;
    
    int hours = abs_seconds / 3600;
    int minutes = (abs_seconds % 3600) / 60;
    
    std::ostringstream oss;
    oss << sign << std::setfill('0') << std::setw(2) << hours 
        << ':' << std::setfill('0') << std::setw(2) << minutes;
    
    return oss.str();
}

inline int get_utc_offset_seconds() {
    auto now = std::chrono::system_clock::now();
    std::time_t tt = std::chrono::system_clock::to_time_t(now);
    
    std::tm local_tm = {};
    std::tm utc_tm = {};
    
#ifdef _WIN32
    localtime_s(&local_tm, &tt);
    gmtime_s(&utc_tm, &tt);
#else
    localtime_r(&tt, &local_tm);
    gmtime_r(&tt, &utc_tm);
#endif
    
    // Compare the day values to handle day boundary cases
    int local_days = local_tm.tm_yday;
    int utc_days = utc_tm.tm_yday;
    int day_diff = local_days - utc_days;
    
    // Calculate seconds within the day
    int local_sec = local_tm.tm_hour * 3600 + local_tm.tm_min * 60 + local_tm.tm_sec;
    int utc_sec = utc_tm.tm_hour * 3600 + utc_tm.tm_min * 60 + utc_tm.tm_sec;
    
    // Total offset: days * 86400 + seconds difference
    return day_diff * 86400 + (local_sec - utc_sec);
}

inline std::string get_formatted_utc_offset() {
    return format_offset_seconds(get_utc_offset_seconds());
}

}