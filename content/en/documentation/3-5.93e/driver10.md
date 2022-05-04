---
title: "Austron 2200A/2201A GPS Receivers"
type: archives
noindex: true 
sitemap_exclude: true
---

#### Table of Contents

*   [Synopsis](/documentation/3-5.93e/driver10/#synopsis)
*   [Description](/documentation/3-5.93e/driver10/#description)
*   [Monitor Data](/documentation/3-5.93e/driver10/#monitor-data)
*   [Fudge Factors](/documentation/3-5.93e/driver10/#fudge-factors)
*   [Additional Information](/documentation/3-5.93e/driver10/#additional-information)

* * *

#### Synopsis

**Address:** <code>127.127.10._u_</code>  
: **Reference ID:** <code>GPS</code>  
: **Driver ID:** <code>GPS_AS2201</code>  
: **Serial Port:** <code>/dev/gps\__u_</code>; 9600 baud, 8-bits, no parity  
: **Features:** <code>tty_clk</code>, <code>ppsclock</code> (required)

* * *

#### Description

This driver supports the Austron 2200A/2201A GPS/LORAN Synchronized Clock and Timing Receiver connected via a serial port. It supports several special features of the clock, including the Input Buffer Module, Output Buffer Module, IRIG-B Interface Module and LORAN Assist Module. It requires the RS232 Serial Interface module for communication with the driver. It requires the `ppsclock` streams module described in the [Line Disciplines and Streams Drivers](/documentation/3-5.93e/ldisc/) page. It also requires a gadget box and 1-PPS level converter, such as described in the [Pulse-per-second (PPS) Signal Interfacing](/documentation/3-5.93e/pps/) page.

This receiver is capable of a comprehensive and large volume of statistics and operational data. The specific data collection commands and attributes are embedded in the driver source code; however, the collection process can be enabled or disabled using the flag4 flag. If set, collection is enabled; if not, which is the default, it is disabled. A comprehensive suite of data reduction and summary scripts is in the ./scripts/stats directory of the xntp3 distribution.

To achieve the high accuracy this device provides, it is necessary to use the <code>ppsclock</code> feature of the xntp3 program distribution or, alternatively, to install the kernel modifications described in the README.kern. The clock can be wired to provide time to a single CPU or bussed in parallel to several CPUs, with one CPU controlling the receiver and the others just listening. Fair accuracy can be achieved in the single-CPU configuration without use of the 1-pps signal, but in multiple CPU configurations accuracy is severely degraded without it.

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

: Specifies the driver reference identifier, an ASCII string from one to four characters, with default <code>GPS</code>.

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

[Reference Clock Drivers](/documentation/3-5.93e/refclock/)