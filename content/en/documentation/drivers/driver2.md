---
title: "Trak 8820 GPS Receiver"
description: "The Trak 8820 GPS Receiver driver supports the Trak 8820 GPS Station Clock."
type: archives
---

#### Table of Contents

*   [Synopsis](/documentation/drivers/driver2/#synopsis)
*   [Description](/documentation/drivers/driver2/#description)
*   [Monitor Data](/documentation/drivers/driver2/#monitor-data)
*   [Fudge Factors](/documentation/drivers/driver2/#fudge-factors)
*   [Additional Information](/documentation/drivers/driver2/#additional-information)

* * *

#### Synopsis

**Address:** <code>127.127.2._u_</code>
: **Reference ID:** `GPS`
: **Driver ID:** `GPS_TRAK`
: **Serial Port:** <code>/dev/trak*u*</code>; 9600 baud, 8-bits, no parity
: **Features:** `tty_clk`

* * *

#### Description

This driver supports the Trak 8820 GPS Station Clock. The claimed accuracy at the 1-PPS output is 200-300 ns relative to the broadcast signal; however, in most cases the actual accuracy is limited by the precision of the timecode and the latencies of the serial interface and operating system.

For best accuracy, this radio requires the `tty_clk` line discipline, which captures a timestamp at the `*` on-time character of the timecode. Using this discipline the jitter is in the order of 1 ms and systematic error about 0.5 ms. If unavailable, the buffer timestamp is used, which is captured at the `\r` ending the timecode message. This introduces a systematic error of 23 character times, or about 24 ms at 9600 bps, together with a jitter well over 8 ms on Sun IPC-class machines.

Using the menus, the radio should be set for 9600 bps, one stop bit and no parity. It should be set to operate in computer (no echo) mode. The timecode format includes neither the year nor leap-second warning.

In operation, this driver sends a <code>RQTS\r</code> request to the radio at initialization in order to put it in continuous time output mode. The radio then sends the following message once each second:

<pre>*RQTS U,ddd:hh:mm:ss.0,q&lsaquo;cr&rsaquo;&lsaquo;lf&rsaquo;
on-time = *
ddd = day of year
hh:mm:ss = hours, minutes, seconds
q = quality indicator (phase error), 0-6:
     0 > 20 us
     6 > 10 us
     5 > 1 us
     4 > 100 ns
     3 > 10 ns
     2 < 10 ns</pre>

The alarm condition is indicated by `0` at `Q`, which means the radio has a phase error greater than 20 us relative to the broadcast time. The absence of year, DST and leap-second warning in this format is also alarmed.

The continuous time mode is disabled using the <code>RQTX\r</code> request, following which the radio sends a <code>RQTX DONE\<cr>\<lf></code> response. In the normal mode, other control and status requests are effective, including the leap-second status request <code>RQLS\<cr></code>. The radio responds with <code>RQLS yy,mm,dd\<cr>\<lf></code>, where `yy,mm,dd` are the year, month and day. Presumably, this gives the epoch of the next leap second, `RQLS 00,00,00` if none is specified in the GPS message. Specified in this form, the information is generally useless and is ignored by the driver.

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

: Specifies the driver reference identifier, an ASCII string from one to four characters, with default `GPS`.

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