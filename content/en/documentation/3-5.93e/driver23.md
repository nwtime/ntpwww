---
title: "PTB Modem Time Service"
type: archives
noindex: true
---

#### Table of Contents
*  [Synopsis](/archives/3-5.93e/driver23/#synopsis)
*  [Description](/archives/3-5.93e/driver23/#description)
*  [Monitor Data](/archives/3-5.93e/driver23/#monitor-data)
*  [Fudge Factors](/archives/3-5.93e/driver23/#fudge-factors)
*  [Additional Information](/archives/3-5.93e/driver23/#additional-information)

* * *

#### Synopsis

**Address:** <code>127.127.23._u_</code>
: **Reference ID:** <code>TPTB</code>
: **Driver ID:** <code>PTP-ACTS</code>
: **Serial Port:** <code>/dev/ptb\__u_</code>; 1200 baud, 8-bits, no parity
: **Features:** none
: **Requires:** <code>/usr/include/sys/termios.h</code> header file with modem control

* * *

#### Description

No further information available.

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

: Specifies the driver reference identifier, an ASCII string from one to four characters, with default USNO.

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

[Reference Clock Drivers](/archives/3-5.93e/refclock/)