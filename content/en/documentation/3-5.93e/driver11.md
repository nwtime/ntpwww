---
title: "Arbiter 1088A/B GPS Receiver"
type: archives
noindex: true 
sitemap_exclude: true
---

#### Table of Contents

*   [Synopsis](/documentation/3-5.93e/driver11/#synopsis)
*   [Description](/documentation/3-5.93e/driver11/#description)
*   [Monitor Data](/documentation/3-5.93e/driver11/#monitor-data)
*   [Fudge Factors](/documentation/3-5.93e/driver11/#fudge-factors)
*   [Additional Information](/documentation/3-5.93e/driver11/#additional-information)

* * *

#### Synopsis

**Address:** <code>127.127.11._u_</code> 
: **Reference ID:** <code>GPS</code>
: **Driver ID:** <code>GPS_ARBITER</code>
: **Serial Port:** <code>/dev/gps\__u_</code>; 9600 baud, 8-bits, no parity
: **Features:** <code>tty_clk</code>

* * *

#### Description

This driver supports the Arbiter 1088A/B Satellite Controlled Clock. The claimed accuracy of this clock is 100 ns relative to the PPS output when receiving four or more satellites.

The receiver should be configured before starting the NTP daemon, in order to establish reliable position and operating conditions. It does not initiate surveying or hold mode. For use with NTP, the daylight savings time feature should be disables (<code>D0</code> command) and the broadcast mode set to operate in UTC (<code>BU</code> command).

The timecode format supported by this driver is selected by the poll sequence <code>B5</code>, which initiates a line in the following format to be repeated once per second until turned off by the <code>B0</code> command.

Format <code>B5</code> (24 ASCII printing characters):

<pre>
&lsaquo;cr&rsaquo;&lsaquo;lf&rsaquo;i yy ddd hh:mm:ss.000bbb
</pre>

`on-time` = &lsaquo;cr&rsaquo;

`i` = synchronization flag (`' '` = locked, `?` = unlocked)

`yy` = year of century

`ddd` = day of year

`hh:mm:ss` = hours, minutes, seconds

`.000` = fraction of second (not used)

`bbb` = tailing spaces for fill

The alarm condition is indicated by a `?` at `i`, which indicates the receiver is not synchronized. In normal operation, a line consisting of the timecode followed by the time quality character `TQ` followed by the receiver status string `SR` is written to the clockstats file.

The time quality character is encoded in IEEE P1344 standard:

Format <code>TQ</code> (IEEE P1344 estimated worst-case time quality)

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

Format <code>SR</code> (25 ASCII printing characters)

<pre>V=vv S=ss T=t P=pdop E=ee</pre>

`vv` = satellites visible

`ss` = relative signal strength

`t` = satellites tracked

`pdop` = position dilution of precision (meters)

`ee` = hardware errors

A three-stage median filter is used to reduce jitter and provide a dispersion measure. The driver makes no attempt to correct for the intrinsic jitter of the radio itself.

#### Monitor Data

The driver writes each timecode as received to the <code>clockstats</code> file. When enabled by the <code>flag4</code> fudge flag, an additional line containing the latitude, longitude, elevation and optional deviation data is written to the <code>clockstats</code> file. The deviation data operates with an external pulse-per-second (PPS) input, such as a cesium oscillator or another radio clock. The PPS input should be connected to the B event channel and the radio initialized for deviation data on that channel. The deviation data consists of the mean offset and standard deviation of the external PPS signal relative the GPS signal, both in microseconds over the last 16 seconds. 

* * *

#### Fudge Factors

<code>**time1 _time_**</code>

: Specifies the time offset calibration factor, in seconds and fraction, with default 0.0. For a calibrated Sun IPC, the correct value is about .0065.

<code>**time2 _time_**</code>

: Not used by this driver.

<code>**stratum _number_**</code>

: Specifies the driver stratum, in decimal from 0 to 15, with default 0.

<code>**refid _string_**</code>

: Specifies the driver reference identifier, an ASCII string from one to four characters, with default <code>GPS</code>.

<code>**flag1 0 | 1**</code>

: Not used by this driver.

<code>**flag2 0 | 1**</code>

: Not used by this driver.

<code>**flag3 0 | 1**</code>

: Enable <code>ppsclock</code> line discipline/streams module if set. 

<code>**flag4 0 | 1**</code>

: Enable extended <code>clockstats</code> recording if set.

* * *

#### Additional Information

[Reference Clock Drivers](/documentation/3-5.93e/refclock/)