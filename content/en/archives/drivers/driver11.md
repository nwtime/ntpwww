---
title: "Arbiter 1088A/B GPS Receiver"
type: archives
---

Author: David L. Mills (mills@udel.edu)  
Last update: 11-Sep-2010 05:56 UTC

* * *

#### Table of Contents

*   [Synopsis](/archives/drivers/driver11/#synopsis)
*   [Description](/archives/drivers/driver11/#description)
*   [Fudge Factors](/archives/drivers/driver11/#fudge-factors)
*   [Additional Information](/archives/drivers/driver11/#additional-information)

* * *

#### Synopsis

Address: 127.127.11._u_  
Reference ID: <tt>GPS</tt>  
Driver ID: <tt>GPS_ARBITER</tt>  
Serial Port: <tt>/dev/gps_u_</tt>; 9600 baud, 8-bits, no parity  
Features: <tt>tty_clk</tt>

* * *

#### Description

This driver supports the Arbiter 1088A/B Satellite Controlled Clock. The claimed accuracy of this clock is 100 ns relative to the PPS output when receiving four or more satellites.

The receiver should be configured before starting the NTP daemon, in order to establish reliable position and operating conditions. It does not initiate surveying or hold mode. For use with NTP, the daylight savings time feature should be disables (<tt>D0</tt> command) and the broadcast mode set to operate in UTC (<tt>BU</tt> command).

The timecode format supported by this driver is selected by the poll sequence <tt>B5</tt>, which initiates a line in the following format to be repeated once per second until turned off by the <tt>B0</tt> command.

Format <tt>B5</tt> (24 ASCII printing characters):

<pre><cr><lf>i yy ddd hh:mm:ss.000bbb

on-time = <cr>
i = synchronization flag (' ' = locked, '?' = unlocked)
yy = year of century
ddd = day of year
hh:mm:ss = hours, minutes, seconds
.000 = fraction of second (not used)
bbb = tailing spaces for fill</pre>

The alarm condition is indicated by a `?` at `i`, which indicates the receiver is not synchronized. In normal operation, a line consisting of the timecode followed by the time quality character `TQ` followed by the receiver status string `SR` is written to the clockstats file.

The time quality character is encoded in IEEE P1344 standard:

Format <tt>TQ</tt> (IEEE P1344 estimated worst-case time quality)

<pre>0       clock locked, maximum accuracy
F       clock failure, time not reliable
4       clock unlocked, accuracy < 1 us
5       clock unlocked, accuracy < 10 us
6       clock unlocked, accuracy < 100 us
7       clock unlocked, accuracy < 1 ms
8       clock unlocked, accuracy < 10 ms
9       clock unlocked, accuracy < 100 ms
A       clock unlocked, accuracy < 1 s
B       clock unlocked, accuracy < 10 s</pre>

The status string is encoded as follows:

Format <tt>SR</tt> (25 ASCII printing characters)

<pre>V=vv S=ss T=t P=pdop E=ee

vv = satellites visible
ss = relative signal strength
t = satellites tracked
pdop = position dilution of precision (meters)
ee = hardware errors</pre>

A three-stage median filter is used to reduce jitter and provide a dispersion measure. The driver makes no attempt to correct for the intrinsic jitter of the radio itself.

#### Monitor Data

When enabled by the <tt>flag4</tt> fudge flag, an additional line containing the latitude, longitude, elevation and optional deviation data is written to the <tt>clockstats</tt> file. The deviation data operates with an external pulse-per-second (PPS) input, such as a cesium oscillator or another radio clock. The PPS input should be connected to the B event channel and the radio initialized for deviation data on that channel. The deviation data consists of the mean offset and standard deviation of the external PPS signal relative the GPS signal, both in microseconds over the last 16 seconds.

* * *

#### Fudge Factors

<dl>

<dt><tt>time1 _time_</tt></dt>

<dd>Specifies the time offset calibration factor, in seconds and fraction, with default 0.0.</dd>

<dt><tt>time2 _time_</tt></dt>

<dd>Not used by this driver.</dd>

<dt><tt>stratum _number_</tt></dt>

<dd>Specifies the driver stratum, in decimal from 0 to 15, with default 0.</dd>

<dt><tt>refid _string_</tt></dt>

<dd>Specifies the driver reference identifier, an ASCII string from one to four characters, with default <tt>GPS</tt>.</dd>

<dt><tt>flag1 0 | 1</tt></dt>

<dd>Not used by this driver.</dd>

<dt><tt>flag2 0 | 1</tt></dt>

<dd>Not used by this driver.</dd>

<dt><tt>flag3 0 | 1</tt></dt>

<dd>Not used by this driver.</dd>

<dt><tt>flag4 0 | 1</tt></dt>

<dd>Enable verbose <tt>clockstats</tt> recording if set.</dd>

</dl>

* * *

#### Additional Information

[Reference Clock Drivers](/archives/4.2.8-series/refclock)