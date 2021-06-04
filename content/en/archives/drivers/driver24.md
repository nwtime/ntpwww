---
title: "USNO Modem Time Service"
type: archives
---

#### Table of Contents

*  [Synopsis](/archives/drivers/driver24/#synopsis)
*  [Description](/archives/drivers/driver24/#description)
*  [Fudge Factors](/archives/drivers/driver24/#fudge-factors)

* * *

#### Synopsis

Address: <tt>127.127.24._u_</tt>  
Reference ID: <tt>USNO</tt>  
Driver ID: <tt>ACTS_USNO</tt>  
Serial Port: <tt>/dev/cua_u_</tt>; 1200 baud, 8-bits, no parity  
Requires: <tt>/usr/include/sys/termios.h</tt> header file with modem control

* * *

#### Description

No information available.

* * *

#### Fudge Factors

<dt><tt>time1 _time_</tt></dt>

Specifies the time offset calibration factor, in seconds and fraction, with default 0.0.

<dt><tt>time2 _time_</tt></dt>

Not used by this driver.

<dt><tt>stratum _number_</tt></dt>

Specifies the driver stratum, in decimal from 0 to 15, with default 0.

<dt><tt>refid _string_</tt></dt>

Specifies the driver reference identifier, an ASCII string from one to four characters, with default <tt>USNO</tt>.

<dt><tt>flag1 0 | 1</tt></dt>

Not used by this driver.

<dt><tt>flag2 0 | 1</tt></dt>

Not used by this driver.

<dt><tt>flag3 0 | 1</tt></dt>

Not used by this driver.

<dt><tt>flag4 0 | 1</tt></dt>

Enable <tt>clockstats</tt> recording if set.