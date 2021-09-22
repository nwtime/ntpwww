---
title: "Heath WWV/WWVH Receiver"
type: archives
---

#### Table of Contents

*   [Synopsis](/archives/3-5.93e/driver19/#synopsis)
*   [Description](/archives/3-5.93e/driver19/#description)
*   [Monitor Data](/archives/3-5.93e/driver19/#monitor-data)
*   [Fudge Factors](/archives/3-5.93e/driver19/#fudge-factors)
*   [Additional Information](/archives/3-5.93e/driver19/#additional-information)

* * *

#### Synopsis

**Address:** <code>127.127.19._u_</code>
: **Reference ID:** <code>WWV</code>
: **Driver ID:** <code>WWV_HEATH</code>
: **Serial Port:** <code>/dev/heath\__u_</code>; 1200 baud, 8-bits, no parity
: **Features:** <code>tty_clk</code>
: **Requires:** <code>/usr/include/sys/termios.h</code> header file with modem control

* * *

#### Description

This driver supports the Heath GC-1000 Most Accurate Clock, with RS232C Output Accessory. This is a WWV/WWVH receiver somewhat less robust than other supported receivers. Its claimed accuracy is 100 ms when actually synchronized to the broadcast signal, but this doesn't happen even most of the time, due to propagation conditions, ambient noise sources, etc. When not synchronized, the accuracy is at the whim of the internal clock oscillator, which can wander into the sunset without warning. Since the indicated precision is 100 ms, expect a host synchronized only to this thing to wander to and fro, occasionally being rudely stepped when the offset exceeds the default CLOCK_MAX of 128 ms. 

The internal DIPswitches should be set to operate at 1200 baud in MANUAL mode and the current year. The external DIPswitches should be set to GMT and 24-hour format. It is very important that the year be set correctly in the DIPswitches; otherwise, the day of year will be incorrect after 28 April of a normal or leap year.

In MANUAL mode the clock responds to a rising edge of the request to send (RTS) modem control line by sending the timecode. Therefore, it is necessary that the operating system implement the <code>TIOCMBIC</code> and <code>TIOCMBIS</code> ioctl system calls and <code>TIOCM_RTS</code> control bit. Present restrictions require the use of a POSIX-compatible programming interface, although other interfaces may work as well.

The clock message consists of 23 ASCII printing characters in the following format:

<code>hh:mm:ss.f     dd/mm/yr\<cr></code>

where:

`hh:mm:ss.f` = hours, minutes, seconds

`f` = deciseconds (`?` when out of spec)

`dd/mm/yr` = day, month, year

The alarm condition is indicated by `?`, rather than a digit, at A. Note that `0?:??:??.?` is displayed before synchronization is first established and `hh:mm:ss.?` once synchronization is established and then lost again for about a day.

A fudge time1 value of .07 s appears to center the clock offset residuals.

* * *

#### Monitor Data

When enabled by the <code>flag4</code> fudge flag, every received timecode is written as-is to the <code>clockstats</code> file. 

* * *

#### Fudge Factors

<code>**time1 _time_**</code>

: Specifies the time offset calibration factor, in seconds and fraction, with default 0.0.

<code>**time2 _time_**</code>

: Not used by this driver.

<code>**stratum _number_**</code>

: Specifies the driver stratum, in decimal from 0 to 15, with default 0.

<code>**refid _string_**</code>

: Specifies the driver reference identifier, an ASCII string from one to four characters, with default <code>WWV</code>.

<code>**flag1 0 | 1**</code>

: Not used by this driver.

<code>**flag2 0 | 1**</code>

: Not used by this driver.

<code>**flag3 0 | 1**</code>

: Enable <code>ppsclock</code> line discipline/streams module if set. 

<code>**flag4 0 | 1**</code>

: Enable <code>clockstats</code> recording if set.

* * *

#### Additional Information

[Reference Clock Drivers](/archives/3-5.93e/refclock)