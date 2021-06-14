---
title: "Austron 2200A/2201A GPS Receivers"
type: archives
---

#### Table of Contents

*   [Synopsis](/archives/3-5.93e/driver10/#synopsis)
*   [Description](/archives/3-5.93e/driver10/#description)
*   [Monitor Data](/archives/3-5.93e/driver10/#monitor-data)
*   [Fudge Factors](/archives/3-5.93e/driver10/#fudge-factors)
*   [Additional Information](/archives/3-5.93e/driver10/#additional-information)

* * *

#### Synopsis

Address: 127.127.10._u_  
Reference ID: <tt>GPS</tt>  
Driver ID: <tt>GPS_AS2201</tt>  
Serial Port: <tt>/dev/gps_u_</tt>; 9600 baud, 8-bits, no parity  
Features: <tt>tty_clk</tt>, <tt>ppsclock</tt> (required)

* * *

#### Description

This driver supports the Austron 2200A/2201A GPS/LORAN Synchronized Clock and Timing Receiver connected via a serial port. It supports several special features of the clock, including the Input Buffer Module, Output Buffer Module, IRIG-B Interface Module and LORAN Assist Module. It requires the RS232 Serial Interface module for communication with the driver. It requires the `ppsclock` streams module described in the [Line Disciplines and Streams Drivers](/archives/3-5.93e/ldisc) page. It also requires a gadget box and 1-PPS level converter, such as described in the [Pulse-per-second (PPS) Signal Interfacing](/archives/3-5.93e/pps) page.

This receiver is capable of a comprehensive and large volume of statistics and operational data. The specific data collection commands and attributes are embedded in the driver source code; however, the collection process can be enabled or disabled using the flag4 flag. If set, collection is enabled; if not, which is the default, it is disabled. A comprehensive suite of data reduction and summary scripts is in the ./scripts/stats directory of the xntp3 distribution.

To achieve the high accuracy this device provides, it is necessary to use the <tt>ppsclock</tt> feature of the xntp3 program distribution or, alternatively, to install the kernel modifications described in the README.kern. The clock can be wired to provide time to a single CPU or bussed in parallel to several CPUs, with one CPU controlling the receiver and the others just listening. Fair accuracy can be achieved in the single-CPU configuration without use of the 1-pps signal, but in multiple CPU configurations accuracy is severely degraded without it.

* * *

#### Monitor Data

When enabled by the <tt>flag4</tt> fudge flag, every received timecode is written as-is to the <tt>clockstats</tt> file.

* * *

#### Fudge Factors

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

<dd>Enable <tt>ppsclock</tt> line discipline/streams module if set.</dd>

<dt><tt>flag4 0 | 1</tt></dt>

<dd>Enable <tt>clockstats</tt> recording if set.</dd>

* * *

#### Additional Information

[Reference Clock Drivers](/archives/3-5.93e/refclock)
