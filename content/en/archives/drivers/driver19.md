---
title: "Heath WWV/WWVH Receiver"
type: archives
---

Author: David L. Mills (mills@udel.edu)
: Last update: 11-Sep-2010 05:56 UTC

* * *

#### Table of Contents

*   [Synopsis](/archives/drivers/driver19/#synopsis)
*   [Description](/archives/drivers/driver19/#description)
*   [Fudge Factors](/archives/drivers/driver19/#fudge-factors)
*   [Additional Information](/archives/drivers/driver19/#additional-information)

* * *

#### Synopsis

**Address:** <code>127.127.19._u_</code>
: **Reference ID:** `WWV`
: **Driver ID:** `WWV_HEATH`
: **Serial Port:** <code>/dev/heath*u*</code>; 1200 baud, 8-bits, no parity
: **Features:** `tty_clk`
: **Requires:** `/usr/include/sys/termios.h` header file with modem control

* * *

#### Description

This driver supports the Heath GC-1000 Most Accurate Clock, with RS232C Output Accessory. This is a WWV/WWVH receiver somewhat less robust than other supported receivers. It's claimed accuracy is 100 ms when actually synchronized to the broadcast signal, but this doesn't happen even most of the time, due to propagation conditions, ambient noise sources, etc. When not synchronized, the accuracy is at the whim of the internal clock oscillator, which can wander into the sunset without warning. Since the indicated precision is 100 ms, expect a host synchronized only to this thing to wander to and fro, occasionally being rudely stepped when the offset exceeds the default `CLOCK_MAX` of 128 ms.

The internal DIPswitches should be set to operate at 1200 baud in MANUAL mode and the current year. The external DIPswitches should be set to GMT and 24-hour format. It is very important that the year be set correctly in the DIPswitches; otherwise, the day of year will be incorrect after 28 April of a normal or leap year.

In MANUAL mode the clock responds to a rising edge of the request to send (RTS) modem control line by sending the timecode. Therefore, it is necessary that the operating system implement the `TIOCMBIC` and `TIOCMBIS` ioctl system calls and `TIOCM_RTS` control bit. Present restrictions require the use of a POSIX-compatible programming interface, although other interfaces may work as well.

The clock message consists of 23 ASCII printing characters in the following format:

<code>hh:mm:ss.f     dd/mm/yr\<cr></code>

`hh:mm:ss.f` = hours, minutes, seconds

`f` = deciseconds (`?` when out of spec)

`dd/mm/yr` = day, month, year

The alarm condition is indicated by `?`, rather than a digit, at A. Note that `0?:??:??.?` is displayed before synchronization is first established and `hh:mm:ss.?` once synchronization is established and then lost again for about a day.

A fudge `time1` value of .07 s appears to center the clock offset residuals.

* * *

#### Fudge Factors

<code>**time1 _time_**</code>

: Specifies the time offset calibration factor, in seconds and fraction, with default 0.0.

<code>**time2 _time_**</code>

: Not used by this driver.

<code>**stratum _number_**</code>

: Specifies the driver stratum, in decimal from 0 to 15, with default 0.

<code>**refid _string_**</code>

: Specifies the driver reference identifier, an ASCII string from one to four characters, with default `WWV`.

<code>**flag1 0 | 1**</code>

: Not used by this driver.

<code>**flag2 0 | 1**</code>

: Not used by this driver.

<code>**flag3 0 | 1**</code>

: Not used by this driver.

<code>**flag4 0 | 1**</code>

: Not used by this driver

* * *

#### Additional Information

[Reference Clock Drivers](/archives/4.2.8-series/refclock)