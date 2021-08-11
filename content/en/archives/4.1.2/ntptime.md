---
title: "ntptime - read and set kernel time variables"
type: archives
---

![gif](/archives/pic/pogo5.gif)[from _Pogo_, Walt Kelly](/reflib/pictures)

The turtle has been swimming in the kernel.

* * *

#### Table of Contents

*   [Synopsis](/archives/4.1.2/ntptime/#synopsis)
*   [Description](/archives/4.1.2/ntptime/#description)
*   [Options](/archives/4.1.2/ntptime/#options)

* * *

#### Synopsis

<tt>ntptime [ -chr ] [ -e _est_error_ ] [ -f _frequency_ ] [ -m _max_error_ ] [ -o _offset_ ] [ -s _status_ ] [ -t _time_constant_]</tt>

* * *

#### Description

This program is useful only with special kernels described in the [A Kernel Model for Precision Timekeeping](/archives/4.1.2/kern) page. It reads and displays time-related kernel variables using the <tt>ntp_gettime()</tt> system call. A similar display can be obtained using the <tt>ntpdc</tt> program and <tt>kerninfo</tt> command.

* * *

#### Options

<dt><tt>-c</tt></dt>

Display the execution time of <tt>ntptime</tt> itself.

<dt><tt>-e _est_error_</tt></dt>

Specify estimated error, in microseconds.

<dt><tt>-f _frequency_</tt></dt>

Specify frequency offset, in parts per million.

<dt><tt>-h</tt></dt>

Display help information.

<dt><tt>-m _max_error_</tt></dt>

Specify max possible errors, in microseconds.

<dt><tt>-o _offset_</tt></dt>

Specify clock offset, in microseconds.

<dt><tt>-r</tt></dt>

Display Unix and NTP times in raw format.

<dt><tt>-s _status_</tt></dt>

Specify clock status. Better know what you are doing.

<dt><tt>-t _time_constant_</tt></dt>

Specify time constant, an integer in the range 0-10.