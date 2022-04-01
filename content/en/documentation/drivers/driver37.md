---
title: "Forum Graphic GPS Dating station"
type: archives
---

* * *

#### Table of Contents

*   [Synopsis](/documentation/drivers/driver37/#synopsis)
*   [Description](/documentation/drivers/driver37/#description)
*   [Monitor Data](/documentation/drivers/driver37/#monitor-data)
*   [Fudge Factors](/documentation/drivers/driver37/#fudge-factors)

* * *

#### Synopsis

**Address:** <code>127.127.37._u_</code>
: **Reference ID:** `GPS`
: **Driver ID:** `GPS`
: **Parallel Port:** <code>/dev/fgclock*u*</code>

* * *

#### Description

This driver supports the Forum Graphic GPS Dating station sold by EMR company.

Unfortunately, sometimes FG GPS start continues reporting of the same date. The only way to fix this problem is GPS power cycling and `ntpd` restart after GPS power-up.

After Jan 10, 2000 my FG GPS unit started sending a wrong answer after 10:00am till 11:00am. It repeated the hour value in result string twice. I wrote a small code to avoid such problem. Unfortunately I have no second FG GPS unit to evaluate this problem. Please let me know if your GPS has no problems after Y2K.

* * *

#### Monitor Data

Each timecode is written to the `clockstats` file in the format `YYYY YD HH MI SS`.

* * *

#### Fudge Factors

<code>**time1 _time_**</code>

: Specifies the time offset calibration factor, in seconds and fraction, with default 0.0.

<code>**time2 _time_**</code>

: Not used by this driver.

<code>**stratum _number_**</code>

: Specifies the driver stratum, in decimal from 0 to 15, with default 0.

<code>**refid _string_**</code>

: Specifies the driver reference identifier, an ASCII string from one to four characters, with default `FG`.

<code>**flag1 0 | 1**</code>

: Not used by this driver.

<code>**flag2 0 | 1**</code>

: Not used by this driver.

<code>**flag3 0 | 1**</code>

: Not used by this driver.

<code>**flag4 0 | 1**</code>

: Not used by this driver.

* * *

[Dmitry Smirnov](mailto:das@amt.ru)