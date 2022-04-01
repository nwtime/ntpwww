---
title: "PPS Clock Discipline"
type: archives
noindex: true
---

#### Table of Contents

*   [Synopsis](/archives/3-5.93e/driver22/#synopsis)
*   [Description](/archives/3-5.93e/driver22/#description)
*   [Fudge Factors](/archives/3-5.93e/driver22/#fudge-factors)
*   [Additional Information](/archives/3-5.93e/driver22/#additional-information)

* * *

#### Synopsis

**Address:** <code>127.127.22._u_</code>
: **Reference ID:** <code>ATOM</code>
: **Driver ID:** <code>ATOM-PPS</code>
: **Serial Port:** <code>/dev/pps\__u_</code>; 9600 baud, 8-bits, no parity
: **Features**: <code>tty_clk</code>, <code>ppsclock</code>

* * *

#### Description

This driver furnishes an interface for pulse-per-second (PPS) signals produced by a cesium clock, radio clock or related equipment. It can be used to remove accumulated jitter and retime a secondary server when synchronized to a primary server over a congested, wide-area network and before redistributing the time to local clients. 

In order for this driver to work, the local clock must be set to within +-500 ms by another means, such as a radio clock or NTP itself. The PPS signal is connected via a serial port and [gadget box](/archives/3-5.93e/gadget/) consisting of a one-shot and RS232 level converter. When operated at 38.4 kbps with a SPARCstation IPC, this arrangement has a worst-case jitter less than 26 us. 

There are three ways in which this driver can be used. The first way uses the <code>LDISC_CLKPPS</code> line discipline and works only for the baseboard serial ports of the Sun SPARCstation running SunOS 4.x. In order to use this option, the -DPPS flag must be included in the <code>DEFS_LOCAL</code> line of the distribution configuration file <code>./Config.local</code>. The PPS signal is connected via the gadget box to the carrier detect (DCD) line of a serial port. The signal is activated by a <code>fudge flag3 1</code> command following the <code>server</code> command in the configuration file. This causes the <code>ppsclock</code> streams module to be configured for that port and to capture a timestamp at the on-time transition of the PPS signal. This driver then reads the timestamp directly by a designated <code>ioctl()</code> system call. This provides the most accurate time and least jitter of any other scheme. There is no need to configure a dedicated device for this purpose, which ordinarily is the device used for the associated radio clock.

The second way uses the <code>LDISC_CLKPPS</code> line discipline and works for any architecture supporting a serial port. In order to use this option, the `-DCLK` flag must be included in the <code>DEFS_LOCAL</code> line of the distribution configuration file <code>./Config.local</code>. If after a few seconds this driver finds no <code>ppsclock</code> module configured, it attempts to open a serial port device <code>/dev/pps%d</code>, where <code>%d</code> is the unit number, and assign the LDISC_CLKPPS line discipline to it. If the line discipline fails, no harm is done except the accuracy is reduced somewhat. The pulse generator in the gadget box must be adjusted to produce a start bit of length 26 usec at 38400 bps. Used with the <code>LDISC_CLKPPS</code> line discipline, this produces an ASCII DEL character (`\377`) followed by a timestamp at the on-time transition of the PPS signal.

The third way involves an auxiliary radio clock driver which calls the PPS driver with a timestamp captured by that driver. This use is documented in the source code for the driver(s) involved.

* * *

#### Fudge Factors

<code>**time1 _time_**</code>

: Specifies the time offset calibration factor, in seconds and fraction, with default 0.0. This parameter can be used to compensate for the UART and OS delays. Allow about 247 us for UART delays at 38400 bps and about 1 ms for SunOS streams nonsense.

<code>**time2 _time_**</code>

: Not used by this driver.

<code>**stratum _number_**</code>

: Specifies the driver stratum, in decimal from 0 to 15, with default 0.

<code>**refid _string_**</code>

: Specifies the driver reference identifier, an ASCII string from one to four characters, with default <code>ATOM</code>.

<code>**flag1 0 | 1**</code>

: Not used by this driver.

<code>**flag2 0 | 1**</code>

: Not used by this driver.

<code>**flag3 0 | 1**</code>

: Enables <code>ppsclock</code> line discipline/streams module if set.

<code>**flag4 0 | 1**</code>

: Not used by this driver.

* * *

#### Additional Information

[Reference Clock Drivers](/archives/3-5.93e/refclock/)