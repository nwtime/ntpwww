---
title: "PSTI/Traconex 1020 WWV/WWVH Receiver"
type: archives
---

Author: David L. Mills (mills@udel.edu)
: Last update: 11-Sep-2010 05:56 UTC

* * *

#### Table of Contents

*   [Synopsis](/documentation/drivers/driver3/#synopsis)
*   [Description](/documentation/drivers/driver3/#description)
*   [Monitor Data](/documentation/drivers/driver3/#monitor-data)
*   [Fudge Factors](/documentation/drivers/driver3/#fudge-factors)
*   [Additional Information](/documentation/drivers/driver3/#additional-information)

* * *

#### Synopsis

**Address:** <code>127.127.3._u_</code>
: **Reference ID:** `WWV`
: **Driver ID:** `WWV_PST`
: **Serial Port:** <code>/dev/wwv*u*</code>; 9600 baud, 8-bits, no parity
: **Features:** `tty_clk`

* * *

#### Description

This driver supports the PSTI 1010 and Traconex 1020 WWV/WWVH Receivers. No specific claim of accuracy is made for these receivers, but actual experience suggests that 10 ms would be a conservative assumption.

The dipswitches should be set for 9600 bps line speed, 24-hour day-of-year format and UTC time zone. Automatic correction for DST should be disabled. It is very important that the year be set correctly in the DIP-switches; otherwise, the day of year will be incorrect after 28 April of a normal or leap year. As there are only four dipswitches to set the year and the base value of zero correspondes to 1986, years beyond 2001 recycle with the value of zero corresponding to 2002. The propagation delay DIP-switches should be set according to the distance from the transmitter for both WWV and WWVH, as described in the instructions. While the delay can be set only to within 11 ms, the `fudge time1` parameter can be used for vernier corrections.

Using the poll sequence `QTQDQM`, the response timecode is in three sections totalling 50 ASCII printing characters, as concatenated by the driver, in the following format:

<pre>ahh:mm:ss.fffs&lsaquo;cr&rsaquo; yy/dd/mm/ddd&lsaquo;cr&rsaquo;
frdzycchhSSFTttttuuxx&lsaquo;cr&rsaquo;

on-time = first &lsaquo;cr&rsaquo;
hh:mm:ss.fff = hours, minutes, seconds, milliseconds
a = AM/PM indicator (' ' for 24-hour mode)
yy = year (from DIPswitches)
dd/mm/ddd = day of month, month, day of year
s = daylight-saving indicator (' ' for 24-hour mode)
f = frequency enable (O = all frequencies enabled)
r = baud rate (3 = 1200, 6 = 9600)
d = features indicator (@ = month/day display enabled)
z = time zone (0 = UTC)
y = year (5 = 91)
cc = WWV propagation delay (52 = 22 ms)
hh = WWVH propagation delay (81 = 33 ms)
SS = status (80 or 82 = operating correctly)
F = current receive frequency (4 = 15 MHz)
T = transmitter (C = WWV, H = WWVH)
tttt = time since last update (0000 = minutes)
uu = flush character (03 = ^c)
xx = 94 (unknown)</pre>

The alarm condition is indicated by other than `8` at `a`, which occurs during initial synchronization and when received signal is lost for an extended period; unlock condition is indicated by other than `0000` in the `tttt` subfield.

* * *

#### Monitor Data

When enabled by the `flag4` fudge flag, every received timecode is written as-is to the `clockstats` file.

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

: Not used by this driver.

* * *

#### Additional Information

[Reference Clock Drivers](/documentation/4.2.8-series/refclock/)