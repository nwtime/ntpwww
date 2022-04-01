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

**Address:** <code>127.127.24._u_</code>
: **Reference ID:** `USNO`
: **Driver ID:** `ACTS_USNO`
: **Serial Port:** <code>/dev/cua*u*</code>; 1200 baud, 8-bits, no parity
: **Requires:** `/usr/include/sys/termios.h` header file with modem control

* * *

#### Description

No information available.

* * *

#### Fudge Factors

<code>**time1 _time_**</code>

: Specifies the time offset calibration factor, in seconds and fraction, with default 0.0.

<code>**time2 _time_**</code>

: Not used by this driver.

<code>**stratum _number_**</code>

: Specifies the driver stratum, in decimal from 0 to 15, with default 0.

<code>**refid _string_**</code>

: Specifies the driver reference identifier, an ASCII string from one to four characters, with default `USNO`.

<code>**flag1 0 | 1**</code>

: Not used by this driver.

<code>**flag2 0 | 1**</code>

: Not used by this driver.

<code>**flag3 0 | 1**</code>

: Not used by this driver.

<code>**flag4 0 | 1**</code>

: Enable `clockstats` recording if set.