---
title: "PPS Clock Discipline"
type: archives
---

#### Table of Contents

*   [Synopsis](/archives/3-5.93e/driver22/#synopsis)
*   [Description](/archives/3-5.93e/driver22/#description)
*   [Fudge Factors](/archives/3-5.93e/driver22/#fudge-factors)
*   [Additional Information](/archives/3-5.93e/driver22/#additional-information)

* * *

#### Synopsis

Address: 127.127.22._u_  
Reference ID: <tt>ATOM</tt>  
Driver ID: <tt>ATOM-PPS</tt>  
Serial Port: <tt>/dev/pps_u_</tt>; 9600 baud, 8-bits, no parity  
Features: <tt>tty_clk</tt>, <tt>ppsclock</tt>

* * *

#### Description

This driver furnishes an interface for pulse-per-second (PPS) signals produced by a cesium clock, radio clock or related equipment. It can be used to remove accumulated jitter and retime a secondary server when synchronized to a primary server over a congested, wide-area network and before redistributing the time to local clients. 

In order for this driver to work, the local clock must be set to within +-500 ms by another means, such as a radio clock or NTP itself. The PPS signal is connected via a serial port and [gadget box](/archives/3-5.93e/gadget) consisting of a one-shot and RS232 level converter. When operated at 38.4 kbps with a SPARCstation IPC, this arrangement has a worst-case jitter less than 26 us. 

There are three ways in which this driver can be used. The first way uses the <tt>LDISC_CLKPPS</tt> line discipline and works only for the baseboard serial ports of the Sun SPARCstation running SunOS 4.x. In order to use this option, the -DPPS flag must be included in the <tt>DEFS_LOCAL</tt> line of the distribution configuration file <tt>./Config.local</tt>. The PPS signal is connected via the gadget box to the carrier detect (DCD) line of a serial port. The signal is activated by a <tt>fudge flag3 1</tt> command following the <tt>server</tt> command in the configuration file. This causes the <tt>ppsclock</tt> streams module to be configured for that port and to capture a timestamp at the on-time transition of the PPS signal. This driver then reads the timestamp directly by a designated <tt>ioctl()</tt> system call. This provides the most accurate time and least jitter of any other scheme. There is no need to configure a dedicated device for this purpose, which ordinarily is the device used for the associated radio clock.

The second way uses the <tt>LDISC_CLKPPS</tt> line discipline and works for any architecture supporting a serial port. In order to use this option, the -DCLK flag must be included in the <tt>DEFS_LOCAL</tt> line of the distribution configuration file <tt>./Config.local</tt>. If after a few seconds this driver finds no <tt>ppsclock</tt> module configured, it attempts to open a serial port device <tt>/dev/pps%d</tt>, where <tt>%d</tt> is the unit number, and assign the LDISC_CLKPPS line discipline to it. If the line discipline fails, no harm is done except the accuracy is reduced somewhat. The pulse generator in the gadget box must be adjusted to produce a start bit of length 26 usec at 38400 bps. Used with the <tt>LDISC_CLKPPS</tt> line discipline, this produces an ASCII DEL character (`\377`) followed by a timestamp at the on-time transition of the PPS signal.

The third way involves an auxiliary radio clock driver which calls the PPS driver with a timestamp captured by that driver. This use is documented in the source code for the driver(s) involved.

* * *

#### Fudge Factors

<dt><tt>time1 _time_</tt></dt>

<dd>Specifies the time offset calibration factor, in seconds and fraction, with default 0.0. This parameter can be used to compensate for the UART and OS delays. Allow about 247 us for UART delays at 38400 bps and about 1 ms for SunOS streams nonsense.</dd>

<dt><tt>time2 _time_</tt></dt>

<dd>Not used by this driver.</dd>

<dt><tt>stratum _number_</tt></dt>

<dd>Specifies the driver stratum, in decimal from 0 to 15, with default 0.</dd>

<dt><tt>refid _string_</tt></dt>

<dd>Specifies the driver reference identifier, an ASCII string from one to four characters, with default <tt>ATOM</tt>.</dd>

<dt><tt>flag1 0 | 1</tt></dt>

<dd>Not used by this driver.</dd>

<dt><tt>flag2 0 | 1</tt></dt>

<dd>Not used by this driver.</dd>

<dt><tt>flag3 0 | 1</tt></dt>

<dd>Enables <tt>ppsclock</tt> line discipline/streams module if set.</dd>

<dt><tt>flag4 0 | 1</tt></dt>

<dd>Not used by this driver.</dd>

* * *

#### Additional Information

[Reference Clock Drivers](/archives/3-5.93e/refclock)