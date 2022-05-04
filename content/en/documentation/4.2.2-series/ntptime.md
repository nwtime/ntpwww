---
title: "ntptime - read and set kernel time variables"
type: archives
noindex: true 
sitemap_exclude: true
---

![gif](/documentation/pic/pogo5.gif)[from _Pogo_, Walt Kelly](/reflib/pictures/)

The turtle has been swimming in the kernel.

* * *

#### Table of Contents

*   [Synopsis](/documentation/4.2.2-series/ntptime/#synopsis)
*   [Description](/documentation/4.2.2-series/ntptime/#description)
*   [Options](/documentation/4.2.2-series/ntptime/#options)

* * *

#### Synopsis

<code>ntptime [ -chr ] [ -e _est_error_ ] [ -f _frequency_ ] [ -m _max_error_ ] [ -o _offset_ ] [ -s _status_ ] [ -t _time_constant_]</code>

* * *

#### Description

This program is useful only with special kernels described in [A Kernel Model for Precision Timekeeping](/documentation/4.2.2-series/kern/). It reads and displays time-related kernel variables using the <code>ntp_gettime()</code> system call. A similar display can be obtained using the <code>ntpdc</code> program and <code>kerninfo</code> command.

* * *

#### Options

<code>**-c**</code>

: Display the execution time of <code>ntptime</code> itself.

<code>**-e _est_error_**</code>

: Specify estimated error, in microseconds.

<code>**-f _frequency_**</code>

: Specify frequency offset, in parts per million.

<code>**-h**</code>

: Display help information.

<code>**-m _max_error_**</code>

: Specify max possible errors, in microseconds.

<code>**-o _offset_**</code>

: Specify clock offset, in microseconds.

<code>**-r**</code>

: Display Unix and NTP times in raw format.

<code>**-s _status_**</code>

: Specify clock status. Better know what you are doing.

<code>**-t _time_constant_**</code>

: Specify time constant, an integer in the range 0-10.