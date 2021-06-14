---
title: "Spectracom8170 and Netclock/2 WWVB Receivers"
type: archives
---

#### Table of Contents

*   [Synopsis](/archives/3-5.93e/driver4/#synopsis)
*   [Description](/archives/3-5.93e/driver4/#description)
*   [Monitor Data](/archives/3-5.93e/driver4/#monitor-data)
*   [Fudge Factors](/archives/3-5.93e/driver4/#fudge-factors)
*   [Additional Information](/archives/3-5.93e/driver4/#additional-information)

* * *

#### Synopsis

Address: 127.127.4._u_  
Reference ID: <tt>WWVB</tt>  
Driver ID: <tt>WWVB_SPEC</tt>  
Serial Port: <tt>/dev/wwvb_u_</tt>; 9600 baud, 8-bits, no parity  
Features: <tt>tty_clk</tt>  

* * *

#### Description

This driver supports the Spectracom Model 8170 and Netclock/2 WWVB Synchronized Clock. This clock has proven a reliable source of time, except in some cases of high ambient conductive RF interference. The claimed accuracy of the clock is 100 usec relative to the broadcast signal; however, in most cases the actual accuracy is limited by the precision of the timecode and the latencies of the serial interface and operating system. 

The DIPswitches on these clocks should be set to 24-hour display, AUTO DST off, data format 0 or 2 (see below) and baud rate 9600. If this clock is used as the source for the IRIG Audio Decoder (<tt>refclock_irig.c</tt> in this distribution), set the DIPswitches for AM IRIG output and IRIG format 1 (IRIG B with signature control).

There are two timecode formats used by these clocks. Format 0, which is available with both the Netclock/2 and 8170, and format 2, which is available only with the Netclock/2 and specially modified 8170. 

Format 0 (22 ASCII printing characters): 

<pre> 
<cr><lf>i ddd hh:mm:ss TZ=zz<cr><lf>

on-time = first <cr>  
i = synchronization flag (' ' = in synch, '?' = out synch)  
hh:mm:ss = hours, minutes, seconds
</pre>

The alarm condition is indicated by other than ' ' at <tt>i</tt>, which occurs during initial synchronization and when received signal is lost for about ten hours.

Format 2 (24 ASCII printing characters): 

<pre> 
lt;cr>lf>iqyy ddd hh:mm:ss.fff ld

on-time = <cr>  
i = synchronization flag (' ' = in synch, '?' = out synch)  
q = quality indicator (' ' = locked, 'A'...'D' = unlocked)  
yy = year (as broadcast)  
ddd = day of year  
hh:mm:ss.fff = hours, minutes, seconds, milliseconds
</pre>

The alarm condition is indicated by other than \' \' at <tt>i</tt>, which occurs during initial synchronization and when received signal is lost for about ten hours. The unlock condition is indicated by other than ' ' at <tt>q</tt>.

The <tt>q</tt> is normally ' ' when the time error is less than 1 ms and a character in the set <tt>A...D</tt> when the time error is less than 10, 100, 500 and greater than 500 ms respectively. The <tt>l</tt> is normally ' ', but is set to <tt>L</tt> early in the month of an upcoming UTC leap second and reset to ' ' on the first day of the following month. The <tt>d</tt> is set to <tt>S</tt> for standard time <tt>S</tt>, <tt>I</tt> on the day preceding a switch to daylight time, <tt>D</tt> for daylight time and <tt>O</tt> on the day preceding a switch to standard time. The start bit of the first <tt>\<cr\></tt> is synchronized to the indicated time as returned.

This driver does not need to be told which format is in use - it figures out which one from the length of the message. A three-stage median filter is used to reduce jitter and provide a dispersion measure. The driver makes no attempt to correct for the intrinsic jitter of the radio itself, which is a known problem with the older radios.

* * *

#### Monitor Data

The driver writes each timecode as received to the <tt>clockstats</tt> file. When enabled by the <tt>flag4</tt> fudge flag, a table of quality data maintained internally by the Netclock/2 is retrieved and written to the <tt>clockstats</tt> file when the first timecode message of a new day is received.

* * *

#### Fudge Factors

<dt><tt>time1 _time_</tt></dt>

Specifies the PPS time offset calibration factor, in seconds and fraction, with default 0.0. For a calibrated Sun IPC, the correct value is about .0048. 

<dt><tt>time2 _time_</tt></dt>

Not used by this driver. 

<dt><tt>stratum _number_</tt></dt>

Specifies the driver stratum, in decimal from 0 to 15, with default 0.

<dt><tt>refid _string_</tt></dt>

Specifies the driver reference identifier, an ASCII string from one to four characters, with default <tt>WWVB</tt>.

<dt><tt>flag1 0 | 1</tt></dt>

Not used by this driver. 

<dt><tt>flag2 0 | 1</tt></dt>

Not used by this driver. 

<dt><tt>flag3 0 | 1</tt></dt>

Enable <tt>ppsclock</tt> line discipline/streams module if set. 

<dt><tt>flag4 0 | 1</tt></dt>

Enable extended <tt>clockstats</tt> recording if set.

#### Additional Information

[Reference Clock Drivers](/archives/3-5.93e/refclock)
