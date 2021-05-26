---
title: "Conrad parallel port radio clock"
type: archives
---

Last update: 21-Oct-2010 23:44 UTC

* * *

#### Table of Contents

*   [Synopsis](/archives/drivers/driver35/#synopsis)
*   [Description](/archives/drivers/driver35/#description)
*   [Monitor Data](/archives/drivers/driver35/#monitor-data)
*   [Fudge factors](/archives/drivers/driver35/#fudge-factors)

* * *

#### Synopsis

Address: 127.127.35._u_  
Reference ID: <tt>PCF</tt>  
Driver ID: <tt>PCF</tt>  
Parallel Port: <tt>/dev/pcfclocks/_u_</tt> or <tt>/dev/pcfclock_u_</tt>

* * *

#### Description

This driver supports the parallel port radio clock sold by [Conrad Electronic](http://www.conrad.com/) under order numbers 967602 and 642002\. This clock is put between a parallel port and your printer. It receives the legal German time, which is either CET or CEST, from the DCF77 transmitter and uses it to set its internal quartz clock. The DCF77 transmitter is located near to Frankfurt/Main and covers a radius of more than 1500 kilometers.

The pcfclock device driver is required in order to use this reference clock driver. Currently device drivers for Linux and FreeBSD are available.

This driver uses C library functions to convert the received timecode to UTC and thus requires that the local timezone be CET or CEST. If your server is not located in Central Europe you have to set the environment variable TZ to CET before starting <tt>ntpd</tt>.

#### Monitor Data

Each timecode is written to the <tt>clockstats</tt> file in the format <tt>YYYY MM DD HH MI SS</tt>.

* * *

#### Fudge Factors

<dl>

<dt><tt>time1 _time_</tt></dt>

<dd>Specifies the time offset calibration factor, in seconds and fraction, with default 0.1725.</dd>

<dt><tt>time2 _time_</tt></dt>

<dd>Not used by this driver.</dd>

<dt><tt>stratum _number_</tt></dt>

<dd>Specifies the driver stratum, in decimal from 0 to 15, with default 0.</dd>

<dt><tt>refid _string_</tt></dt>

<dd>Specifies the driver reference identifier, an ASCII string from one to four characters, with default <tt>PCF</tt>.</dd>

<dt><tt>flag1 0 | 1</tt></dt>

<dd>Not used by this driver.</dd>

<dt><tt>flag2 0 | 1</tt></dt>

<dd>If set to 1, the radio clock's synchronisation status bit is ignored, ie the timecode is used without a check.</dd>

<dt><tt>flag3 0 | 1</tt></dt>

<dd>Not used by this driver.</dd>

<dt><tt>flag4 0 | 1</tt></dt>

<dd>Not used by this driver.</dd>

</dl>
