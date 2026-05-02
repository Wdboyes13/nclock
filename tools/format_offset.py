#!/usr/bin/env python3
"""
Cross-platform UTC offset formatting without non-portable format specifiers.

This module provides a robust way to format UTC offsets (e.g., +05:30 instead of +0530)
that works across Windows, Linux, and macOS.
"""

import time
from datetime import datetime, timezone, timedelta
from typing import Optional


def get_utc_offset_seconds(dt: Optional[datetime] = None) -> int:
    """
    Get UTC offset in seconds without relying on platform-specific gmtoff.
    
    Args:
        dt: Optional datetime object. If None, uses current local time.
    
    Returns:
        UTC offset in seconds (positive for east of UTC, negative for west)
    """
    if dt is None:
        dt = datetime.now()
    
    # Method 1: Try to use utctimetuple for systems that support it
    # This works on most Unix-like systems
    try:
        now_ts = time.time()
        local_ts = time.localtime(now_ts)
        utc_ts = time.gmtime(now_ts)
        
        # Calculate offset by comparing struct_time values
        local_offset = time.mktime(local_ts) - time.mktime(utc_ts)
        
        # mktime assumes the input is in local time, so we need to adjust
        # Use a reference date to avoid DST issues
        ref_local = time.mktime(time.struct_time((2000, 1, 1, 0, 0, 0, 5, 1, -1)))
        ref_utc = time.mktime(time.struct_time((2000, 1, 1, 0, 0, 0, 5, 1, 0)))
        offset = ref_local - ref_utc
        
        return int(round(offset))
    except Exception:
        pass
    
    # Method 2: Use datetime comparison (most portable)
    if dt.tzinfo is None:
        # Local time without timezone info
        utc_now = datetime.now(timezone.utc)
        local_now = datetime.now()
        
        # Calculate offset from UTC
        offset = local_now - utc_now.replace(tzinfo=None)
        return int(offset.total_seconds())
    else:
        # Has timezone info, use the offset directly
        utc_dt = dt.astimezone(timezone.utc)
        offset = dt - utc_dt.replace(tzinfo=None)
        return int(offset.total_seconds())


def format_utc_offset(offset_seconds: int) -> str:
    """
    Format UTC offset with colon separator (e.g., '+05:30' or '-08:00').
    
    Args:
        offset_seconds: UTC offset in seconds
    
    Returns:
        Formatted offset string with colon separator
    """
    sign = '+' if offset_seconds >= 0 else '-'
    abs_seconds = abs(offset_seconds)
    
    hours = abs_seconds // 3600
    minutes = (abs_seconds % 3600) // 60
    
    return f"{sign}{hours:02d}:{minutes:02d}"


def format_utc_offset_alternative(offset_seconds: int) -> str:
    """
    Alternative implementation using timedelta arithmetic.
    
    Args:
        offset_seconds: UTC offset in seconds
    
    Returns:
        Formatted offset string with colon separator
    """
    offset_td = timedelta(seconds=offset_seconds)
    
    # Calculate hours and minutes
    total_minutes = int(abs(offset_td.total_seconds()) // 60)
    hours = total_minutes // 60
    minutes = total_minutes % 60
    
    sign = '+' if offset_seconds >= 0 else '-'
    return f"{sign}{hours:02d}:{minutes:02d}"


def get_formatted_offset() -> str:
    """
    Get current UTC offset formatted with colon separator.
    
    Returns:
        Current UTC offset as string (e.g., '+05:30', '-08:00', '+00:00')
    """
    offset_seconds = get_utc_offset_seconds()
    return format_utc_offset(offset_seconds)


if __name__ == "__main__":
    # Test cases
    test_cases = [
        (0, "+00:00"),           # UTC
        (3600, "+01:00"),         # Central European Time
        (int(5.5 * 3600), "+05:30"),  # India Standard Time
        (-5 * 3600, "-05:00"),   # Eastern Standard Time
        (-8 * 3600, "-08:00"),   # Pacific Standard Time
        (int(9.5 * 3600), "+09:30"),  # Australian Central Standard Time
    ]
    
    print("Testing format_utc_offset:")
    for seconds, expected in test_cases:
        result = format_utc_offset(seconds)
        status = "PASS" if result == expected else "FAIL"
        print(f"  {status} {seconds:>6} -> {result} (expected: {expected})")
    
    print("\nCurrent system offset:")
    current_offset = get_formatted_offset()
    print(f"  {current_offset}")