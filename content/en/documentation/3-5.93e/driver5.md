---
title: "TrueTime GPS/GOES/OMEGA Receivers"
type: archives
noindex: true 
sitemap_exclude: true
---

* * *

#### Table of Contents

*   [Synopsis](/documentation/3-5.93e/driver5/#synopsis)
*   [Description](/documentation/3-5.93e/driver5/#description)
*   [Monitor Data](/documentation/3-5.93e/driver5/#monitor-data)
*   [Fudge Factors](/documentation/3-5.93e/driver5/#fudge-factors)
*   [Additional Information](/documentation/3-5.93e/driver5/#additional-information)

* * *

#### Synopsis

**Address:** <code>127.127.5._u_</code>  
: **Reference ID:** <code>GPS, OMEGA, GOES</code>  
: **Driver ID:** <code>TRUETIME</code>  
: **Serial Port:** <code>/dev/true\__u_</code>; 9600 baud, 8-bits, no parity  
: **Features:** <code>tty_clk</code>

* * *

#### Description

This driver supports several models of Kinemetrics/TrueTime timing receivers, including 468-DC MK III GOES Synchronized Clock, GPS- DC MK III and GPS/TM-TMD GPS Synchronized Clock, XL-DC (a 151-602-210, reported by the driver as a GPS/TM-TMD), GPS-800 TCU (an 805-957 with the RS232 Talker/Listener module), OM-DC OMEGA Synchronized Clock, and very likely others in the same model families that use the same timecode formats.

Most of this code is originally from refclock_wwvb.c with thanks. It has been so mangled that wwvb is not a recognizable ancestor.

Timecode format: `ADDD:HH:MM:SSQCL` 

* `A` - control A (this is stripped before we see it) 
* `Q` - Quality indication (see below) 
* `C` - Carriage return 
* `L` - Line feed

Quality codes indicate possible error of:

**468-DC GOES Receiver** 
: **GPS-TM/TMD Receiver**

* `?` +/- 500 milliseconds 
* `#` +/- 50 milliseconds  
* `*` +/- 5 milliseconds 
* `.` +/- 1 millisecond  
* space: less than 1 millisecond

**OM-DC OMEGA Receiver:**

* `>` +/- 5 seconds  
* `?` +/- 500 milliseconds # +/- 50 milliseconds  
* `*` +/- 5 milliseconds . +/- 1 millisecond  
* `A-H` less than 1 millisecond. Character indicates which station is being received as follows:  A = Norway, B = Liberia, C = Hawaii, D = North Dakota, E = La Reunion, F = Argentina, G = Australia, H = Japan  

The carriage return start bit begins on 0 seconds and extends to 1 bit time.

**Notes on 468-DC and OMEGA receiver:**

Send the clock a <code>R</code> or <code>C</code> and once per second a timestamp will appear. Send a <code>R</code> to get the satellite position once (GOES only).

**Notes on the 468-DC receiver:**

Since the old east/west satellite locations are only historical, you can't set your clock propagation delay settings correctly and still use automatic mode. The manual says to use a compromise when setting the switches. This results in significant errors. The solution; use fudge time1 and time2 to incorporate corrections. If your clock is set for 50 and it should be 58 for using the west and 46 for using the east, use the line

`fudge 127.127.5.0 time1 +0.008 time2 -0.004`

This corrects the 4 milliseconds advance and 8 milliseconds retard needed. The software will ask the clock which satellite it sees.

The PCL720 from PC Labs has an Intel 8253 look-alike, as well as a bunch of TTL input and output pins, all brought out to the back panel. If you wire a PPS signal (such as the TTL PPS coming out of a GOES or other Kinemetrics/Truetime clock) to the 8253's GATE0, and then also wire the 8253's OUT0 to the PCL720's INPUT3.BIT0, then we can read CTR0 to get the number of microseconds since the last PPS upward edge, mediated by reading OUT0 to find out if the counter has wrapped around (this happens if more than 65535us (65ms) elapses between the PPS event and our being called.)

* * *

#### Monitor Data

When enabled by the <code>flag4</code> fudge flag, every received timecode is written as-is to the <code>clockstats</code> file.

* * *

#### Fudge Factors

<code>**time1 _time_**</code>

: Specifies the time offset calibration factor, in seconds and fraction, to be used for the West satellite, with default 0.0.

<code>**time2 _time_**</code>

:  Specifies the time offset calibration factor, in seconds and fraction, to be used for the East satellite, with default 0.0.

<code>**stratum _number_**</code>

: Specifies the driver stratum, in decimal from 0 to 15, with default 0.

<code>**refid _string_**</code>

: Specifies the driver reference identifier, an ASCII string from one to four characters, with default <code>TRUE</code>.

<code>**flag1 0 | 1**</code>

: Silence the clock side of ntpd, just reading the clock without trying to write to it.

<code>**flag2 0 | 1**</code>

: Generate a debug file <code>/tmp/true%d</code>.

<code>**flag3 0 | 1**</code>

: Enable <code>ppsclock</code> line discipline/streams module if set. 

<code>**flag4 0 | 1**</code>

: Enable <code>clockstats</code> recording if set.

* * *

#### Additional Information

[Reference Clock Drivers](/documentation/3-5.93e/refclock/)