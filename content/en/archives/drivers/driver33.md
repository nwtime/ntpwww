---
title: "Dumb Clock"
type: archives
---

Last update: 21-Oct-2010 23:44 UTC

* * *

#### Table of Contents

*   [Synopsis](/archives/drivers/driver33/#synopsis)
*   [Description](/archives/drivers/driver33/#description)

* * *

#### Synopsis

Address: 127.127.33._u_  
Reference ID: <tt>DUMBCLOCK</tt>  
Driver ID: <tt>DUMBCLOCK</tt>  
Serial Port: <tt>/dev/dumbclock_u_</tt>; 9600 bps, 8-bits, no parity  
Features: <tt>(none)</tt>

* * *

#### Description

This driver supports a dumb ASCII clock that only emits localtime at a reliable interval. This has no provisions for leap seconds, quality codes, etc. It assumes output in the local time zone, and that the C library mktime()/localtime() routines will correctly convert back and forth between local and UTC.

Most of this code is originally from refclock_wwvb.c with thanks. It has been so mangled that wwvb is not a recognizable ancestor.

<pre>Timecode format: hh:mm:ssCL
hh:mm:ss - local time
C - \r (carriage return)
L - \n (newline)
</pre>
