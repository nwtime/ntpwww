---
title: "ntptime - read kernel time variables"
type: archives
---

#### Table of Contents

*   [Synopsis](/archives/3-5.93e/ntptime/#synopsis)
*   [Description](/archives/3-5.93e/ntptime/#description)
*   [Options](/archives/3-5.93e/ntptime/#options)

* * *

#### Synopsis

<tt>ntptime [ -chr ] [ -e _est_error_ ] [ -f _frequency_ ] [ -m _max_error_ ] [ -o _offset_ ] [ -s _status_ ] [ -t _time_constant_]</tt>

* * *

#### Description

This program is useful only with special kernels described in the [A Kernel Model for Precision Timekeeping](/archives/3-5.93e/kern) page. It reads and displays time-related kernel variables using the <tt>ntp_gettime()</tt> system call. A similar display can be obtained using the <tt>xntpdc</tt> program and <tt>kerninfo</tt> command.

* * *

#### Options

<dt><tt>-c</tt></dt>

Display the execution time of <tt>ntptime</tt> itself.

<dt><tt>-e _est_error_</tt></dt>

Specify estimated error, in microseconds.

<dt><tt>-f _frequency_</tt></dt>

Specify frequency offset, in parts per million.

<dt><tt>-h</tt></dt>

Display times in Unix timeval format. Default is NTP format. 

<dt><tt>-l</tt></dt>

Specify the leap bits as a code from 0 to 3. 

<dt><tt>-m _max_error_</tt></dt>

Display help information.

<dt><tt>-o _offset_</tt></dt>

Specify clock offset, in microseconds.

<dt><tt>-r</tt></dt>

Display Unix and NTP times in raw format.

<dt><tt>-s _status_</tt></dt>

Specify clock status. Better know what you are doing.

<dt><tt>-t _time_constant_</tt></dt>

Specify time constant, an integer in the range 0-10.