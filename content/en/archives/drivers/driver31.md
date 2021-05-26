---
title: "Rockwell Jupiter GPS Receiver"
type: archives
---

Last update: 21-Oct-2010 23:44 UTC

* * *

#### Table of Contents

*   [Synopsis](/archives/drivers/driver31/#synopsis)
*   [Description](/archives/drivers/driver31/#description)
*   [Monitor Data](/archives/drivers/driver31/#monitor-data)
*   [Fudge Factors](/archives/drivers/driver31/#fudge-factors)
*   [Additional Information](/archives/drivers/driver31/#additional-information)

* * *

#### Synopsis

Address: 127.127.31._u_  
Reference ID: <tt>GPS</tt>  
Driver ID: JUPITER  
Serial Port: <tt>/dev/gps</tt>_u_;  9600 baud, 8-bits, no parity.

* * *

#### Description

This driver supports at least some models of the Rockwell Jupiter <tt>GPS</tt> receivers (Jupiter 11, Jupiter-T), they must at least support the _Zodiac Binary Protocol_.

The driver requires a standard <tt>PPS</tt> interface for the pulse-per-second output from the receiver. The serial data stream alone does not provide precision time stamps, whereas the PPS output is precise down to 40 ns (1 sigma) for the Jupiter 11 and 25 ns (1 sigma) for Jupiter-T according to the documentation. If you do not have the PPS signal available, then you should probably not be using the Jupiter receiver as a time source. This driver requires a <tt>PPS</tt> signal and the time output from Jupiter receivers is not predictable in <tt>NMEA</tt> mode; the reported time can take one second steps.

* * *

#### Monitor Data

The driver always puts a lot of useful information on the clockstats file, and when run with debugging can be quite chatty on stdout. When first starting to use the driver you should definitely review the information written to the clockstats file to verify that the driver is running correctly.

* * *

#### Fudge Factors

<dl>

<dt><tt>time1 _time_</tt></dt>

<dd>Specifies the time offset calibration factor, in seconds and fraction, with default 0.0.</dd>

<dt><tt>time2 _time_</tt></dt>

<dd>Not used by this driver. Should be left at zero.</dd>

<dt><tt>stratum _number_</tt></dt>

<dd>Specifies the driver stratum, in decimal from 0 to 15, with default 0.</dd>

<dt><tt>refid _string_</tt></dt>

<dd>Specifies the driver reference identifier, an <tt>ASCII</tt> string from one to four characters, with default <tt>GPS</tt>.</dd>

<dt><tt>flag1 0 | 1</tt></dt>

<dd>Not used by this driver.</dd>

<dt><tt>flag2 0 | 1</tt></dt>

<dd>Specifies the mobility of the <tt>GPS</tt> receiver: 0 for walking (default), 1 for driving.</dd>

<dt><tt>flag3 0 | 1</tt></dt>

<dd>Specifies the <tt>PPS</tt> signal on-time edge: 0 for assert (default), 1 for clear.</dd>

<dt><tt>flag4 0 | 1</tt></dt>

<dd>Not used by this driver.</dd>

</dl>

* * *

#### Additional Information

The driver was resurrected from a sorry state using the Windows NT port and a Jupiter 11, and has since seen little testing on other platforms. On Windows there exist a barrier though, as there is no publicly available <tt>PPSAPI</tt> implementation, at least not to my knowledge. However, there has been one success report using Linux 2.4.20 and PPSkit 2.1.1.

The Jupiter receivers seem to have quite a few names. They are referred to at least as Rockwell receivers, Navman receivers, Zodiac receivers, Conexant receivers and SiRF Technology receivers. Rockwell seems to be the original and most commonly used name and Navman seems to be the current supplier.

**Configuration**

The edge of the <tt>PPS</tt> signal that is on-time can be set with <tt>flag2</tt>. There is currently no way to cause the <tt>PPS</tt> signal to control the kernel <tt>PLL</tt>.

**Performance**

The performance is largely unexplored. I have achieved submillisecond stability using a Jupiter 11, but the poor result is more than likely due to the proprietary <tt>PPSAPI</tt> implementation or Windows itself.

This driver does not handle leap seconds.
