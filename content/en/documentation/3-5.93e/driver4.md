---
title: "Spectracom8170 and Netclock/2 WWVB Receivers"
type: archives
noindex: true
---

#### Table of Contents

*   [Synopsis](/archives/3-5.93e/driver4/#synopsis)
*   [Description](/archives/3-5.93e/driver4/#description)
*   [Monitor Data](/archives/3-5.93e/driver4/#monitor-data)
*   [Fudge Factors](/archives/3-5.93e/driver4/#fudge-factors)
*   [Additional Information](/archives/3-5.93e/driver4/#additional-information)

* * *

#### Synopsis

**Address:** <code>127.127.4._u_</code>  
: **Reference ID:** <code>WWVB</code>  
: **Driver ID:** <code>WWVB_SPEC</code>  
: **Serial Port:** <code>/dev/wwvb\__u_</code>; 9600 baud, 8-bits, no parity  
: **Features:** <code>tty_clk</code>  

* * *

#### Description

This driver supports the Spectracom Model 8170 and Netclock/2 WWVB Synchronized Clock. This clock has proven a reliable source of time, except in some cases of high ambient conductive RF interference. The claimed accuracy of the clock is 100 usec relative to the broadcast signal; however, in most cases the actual accuracy is limited by the precision of the timecode and the latencies of the serial interface and operating system. 

The DIPswitches on these clocks should be set to 24-hour display, AUTO DST off, data format 0 or 2 (see below) and baud rate 9600. If this clock is used as the source for the IRIG Audio Decoder (<code>refclock_irig.c</code> in this distribution), set the DIPswitches for AM IRIG output and IRIG format 1 (IRIG B with signature control).

There are two timecode formats used by these clocks. Format 0, which is available with both the Netclock/2 and 8170, and format 2, which is available only with the Netclock/2 and specially modified 8170. 

Format 0 (22 ASCII printing characters): 

<pre> 
&lsaquo;cr&rsaquo;&lsaquo;lf&rsaquo;i ddd hh:mm:ss TZ=zz&lsaquo;cr&rsaquo;&lsaquo;lf&rsaquo;
</pre>

`on-time` = first &lsaquo;cr&rsaquo;&lsaquo;lf&rsaquo;  
`i` = synchronization flag (`' '` = in synch, `?` = out synch)  
`hh:mm:ss` = hours, minutes, seconds

The alarm condition is indicated by other than `' '` at `i`, which occurs during initial synchronization and when received signal is lost for about ten hours.

Format 2 (24 ASCII printing characters): 

<pre>
&lsaquo;cr&rsaquo;&lsaquo;lf&rsaquo;iqyy ddd hh:mm:ss.fff ld
</pre>

`on-time` = &lsaquo;cr&rsaquo;&lsaquo;lf&rsaquo;  
`i` = synchronization flag (`' '` = in synch, `?` = out synch)  
`q` = quality indicator (`' '` = locked, `A`...`D` = unlocked)  
`yy` = year (as broadcast)  
`ddd` = day of year  
`hh:mm:ss.fff` = hours, minutes, seconds, milliseconds

The alarm condition is indicated by other than `' '` at `i`, which occurs during initial synchronization and when received signal is lost for about ten hours. The unlock condition is indicated by other than `' '` at `q`.

The `q` is normally `' '` when the time error is less than 1 ms and a character in the set `A...D` when the time error is less than 10, 100, 500 and greater than 500 ms respectively. The `l` is normally `' '`, but is set to `L` early in the month of an upcoming UTC leap second and reset to `' '` on the first day of the following month. The `d` is set to `S` for standard time `S`, `I` on the day preceding a switch to daylight time, `D` for daylight time and `O` on the day preceding a switch to standard time. The start bit of the first &lsaquo;cr&rsaquo; is synchronized to the indicated time as returned.

This driver does not need to be told which format is in use - it figures out which one from the length of the message. A three-stage median filter is used to reduce jitter and provide a dispersion measure. The driver makes no attempt to correct for the intrinsic jitter of the radio itself, which is a known problem with the older radios.

* * *

#### Monitor Data

The driver writes each timecode as received to the <code>clockstats</code> file. When enabled by the <code>flag4</code> fudge flag, a table of quality data maintained internally by the Netclock/2 is retrieved and written to the <code>clockstats</code> file when the first timecode message of a new day is received.

* * *

#### Fudge Factors

<code>**time1 _time_**</code>

: Specifies the PPS time offset calibration factor, in seconds and fraction, with default 0.0. For a calibrated Sun IPC, the correct value is about .0048. 

<code>**time2 _time_**</code>

: Not used by this driver. 

<code>**stratum _number_**</code>

: Specifies the driver stratum, in decimal from 0 to 15, with default 0.

<code>**refid _string_**</code>

: Specifies the driver reference identifier, an ASCII string from one to four characters, with default <code>WWVB</code>.

<code>**flag1 0 | 1**</code>

: Not used by this driver. 

<code>**flag2 0 | 1**</code>

: Not used by this driver. 

<code>**flag3 0 | 1**</code>

: Enable <code>ppsclock</code> line discipline/streams module if set. 

<code>**flag4 0 | 1**</code>

: Enable extended <code>clockstats</code> recording if set.

#### Additional Information

[Reference Clock Drivers](/archives/3-5.93e/refclock/)