---
title: "Chrono-log K-series WWVB receiver"
type: archives
---

Last update: 21-Oct-2010 23:44 UTC

* * *

#### Table of Contents

*   [Synopsis](/documentation/drivers/driver32/#synopsis)
*   [Description](/documentation/drivers/driver32/#description)

* * *

#### Synopsis

**Address:** <code>127.127.32._u_</code>
: **Reference ID:** `CHRONOLOG`
: **Driver ID:** `CHRONOLOG`
: **Serial Port:** <code>/dev/chronolog*u*</code>; 2400 bps, 8-bits, no parity
: **Features:** none

* * *

#### Description

This driver supports the Chrono-log K-series WWVB receiver. This is a very old receiver without provisions for leap seconds, quality codes, etc. It assumes output in the local time zone, and that the C library `mktime()` / `localtime()` routines will correctly convert back and forth between local and UTC. There is a hack in the driver for permitting UTC, but it has not been tested.

Most of this code is originally from `refclock_wwvb.c` with thanks. It has been so mangled that wwvb is not a recognizable ancestor.

<pre>Timecode format: Y yy/mm/ddCLZhh:mm:ssCL
Y - year/month/date line indicator
yy/mm/dd -- two-digit year/month/day
C - \r (carriage return)
L - \n (newline)
Z - timestamp indicator
hh:mm:ss - local time
</pre>
