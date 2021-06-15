---
title: "Spectracom WWVB/GPS Receivers"
type: archives
---

Author: David L. Mills (mills@udel.edu)  
Last update: 11-Sep-2010 05:56 UTC

* * *

#### Table of Contents

*   [Synopsis](/archives/drivers/driver4/#synopsis)
*   [Description](/archives/drivers/driver4/#description)
*   [PPS Signal Processing](/archives/drivers/driver4/#pps-signal-processing)
*   [Monitor Data](/archives/drivers/driver4/#monitor-data)
*   [Fudge Factors](/archives/drivers/driver4/#fudge-factors)

* * *

#### Synopsis

Address: 127.127.4._u_  
Reference ID: <tt>WWVB</tt>  
Driver ID: <tt>WWVB_SPEC</tt>  
Serial Port: <tt>/dev/wwvb_u_</tt>; 9600 baud, 8-bits, no parity  
Features: Optional PPS signal processing, <tt>tty_clk</tt>  
Requires: Optional PPS signal processing requires the PPSAPI signal interface.

* * *

#### Description

This driver supports all known Spectracom radio and satellite clocks, including the Model 8170 and Netclock/2 WWVB Synchronized Clocks and the Netclock/GPS GPS Master Clock. The claimed accuracy of the WWVB clocks is 100 <span class="style1">m</span>s relative to the broadcast signal. These clocks have proven a reliable source of time, except in some parts of the country with high levels of conducted RF interference. WIth the GPS clock the claimed accuracy is 130 ns. However, in most cases the actual accuracy is limited by the precision of the timecode and the latencies of the serial interface and operating system.

The DIPswitches on these clocks should be set to 24-hour display, AUTO DST off, data format 0 or 2 (see below) and baud rate 9600\. If this clock is used as the source for the IRIG Audio Decoder (<tt>refclock_irig.c</tt> in this distribution), set the DIPswitches for AM IRIG output and IRIG format 1 (IRIG B with signature control).

There are two timecode formats used by these clocks. Format 0, which is available with all clocks, and format 2, which is available with all clocks except the original (unmodified) Model 8170.

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

#### PPS Signal Processing

When PPS signal processing is enabled, and when the system clock has been set by this or another driver and the PPS signal offset is within 0.4 s of the system clock offset, the PPS signal replaces the timecode for as long as the PPS signal is active. If for some reason the PPS signal fails for one or more poll intervals, the driver reverts to the timecode. If the timecode fails for one or more poll intervals, the PPS signal is disconnected.

* * *

#### Monitor Data

The driver writes each timecode as received to the <tt>clockstats</tt> file. When enabled by the <tt>flag4</tt> fudge flag, a table of quality data maintained internally by the Netclock/2 is retrieved and written to the <tt>clockstats</tt> file when the first timecode message of a new day is received.

* * *

#### Fudge Factors

<dl>

<dt><tt>time1 _time_</tt></dt>

<dd>Specifies the PPS time offset calibration factor, in seconds and fraction, with default 0.0.</dd>

<dt><tt>time2 _time_</tt></dt>

<dd>Specifies the serial time offset calibration factor, in seconds and fraction, with default 0.0.</dd>

<dt><tt>stratum _number_</tt></dt>

<dd>Specifies the driver stratum, in decimal from 0 to 15, with default 0.</dd>

<dt><tt>refid _string_</tt></dt>

<dd>Specifies the driver reference identifier, an ASCII string from one to four characters, with default <tt>WWVB</tt>.</dd>

<dt><tt>flag1 0 | 1</tt></dt>

<dd>Disable PPS signal processing if 0 (default); enable PPS signal processing if 1.</dd>

<dt><tt>flag2 0 | 1</tt></dt>

<dd>If PPS signal processing is enabled, capture the pulse on the rising edge if 0 (default); capture on the falling edge if 1.</dd>

<dt><tt>flag3 0 | 1</tt></dt>

<dd>If PPS signal processing is enabled, use the <tt>ntpd</tt> clock discipline if 0 (default); use the kernel discipline if 1.</dd>

<dt><tt>flag4 0 | 1</tt></dt>

<dd>Enable verbose <tt>clockstats</tt> recording if set.</dd>

</dl>
