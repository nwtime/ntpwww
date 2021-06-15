---
title: "Forum Graphic GPS Dating station"
type: archives
---

* * *

#### Table of Contents

*   [Synopsis](/archives/drivers/driver37/#synopsis)
*   [Description](/archives/drivers/driver37/#description)
*   [Monitor Data](/archives/drivers/driver37/#monitor-data)
*   [Fudge Factors](/archives/drivers/driver37/#fudge-factors)

* * *

#### Synopsis

Address: 127.127.37._u_  
Reference ID: <tt>GPS</tt>  
Driver ID: <tt>GPS</tt>  
Parallel Port: <tt>/dev/fgclock_u_</tt>

* * *

#### Description

This driver supports the Forum Graphic GPS Dating station sold by EMR company.

Unfortunately, sometimes FG GPS start continues reporting of the same date. The only way to fix this problem is GPS power cycling and ntpd restart after GPS power-up.

After Jan,10 2000 my FG GPS unit start send a wrong answer after 10:00am till 11:00am. It repeat hour value in result string twice. I wrote a small code to avoid such problem. Unfortunately I have no second FG GPS unit to evaluate this problem. Please let me know if your GPS has no problems after Y2K.

* * *

#### Monitor Data

Each timecode is written to the <tt>clockstats</tt> file in the format <tt>YYYY YD HH MI SS</tt>.

* * *

#### Fudge Factors

<dl>

<dt><tt>time1 _time_</tt></dt>

<dd>Specifies the time offset calibration factor, in seconds and fraction, with default 0.0.</dd>

<dt><tt>time2 _time_</tt></dt>

<dd>Not used by this driver.</dd>

<dt><tt>stratum _number_</tt></dt>

<dd>Specifies the driver stratum, in decimal from 0 to 15, with default 0.</dd>

<dt><tt>refid _string_</tt></dt>

<dd>Specifies the driver reference identifier, an ASCII string from one to four characters, with default <tt>FG</tt>.</dd>

<dt><tt>flag1 0 | 1</tt></dt>

<dd>Not used by this driver.</dd>

<dt><tt>flag2 0 | 1</tt></dt>

<dd>Not used by this driver.</dd>

<dt><tt>flag3 0 | 1</tt></dt>

<dd>Not used by this driver.</dd>

<dt><tt>flag4 0 | 1</tt></dt>

<dd>Not used by this driver.</dd>

</dl>

* * *

[Dmitry Smirnov](mailtodas@amt.ru)
