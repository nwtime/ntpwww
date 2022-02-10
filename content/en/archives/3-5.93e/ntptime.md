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

<code>ntptime [ -chr ] [ -e _est_error_ ] [ -f _frequency_ ] [ -m _max_error_ ] [ -o _offset_ ] [ -s _status_ ] [ -t _time_constant_]</code>

* * *

#### Description

This program is useful only with special kernels described in the [A Kernel Model for Precision Timekeeping](/archives/3-5.93e/kern/) page. It reads and displays time-related kernel variables using the <code>ntp_gettime()</code> system call. A similar display can be obtained using the <code>xntpdc</code> program and <code>kerninfo</code> command.

* * *

#### Options

<code>**-c**</code>

: Display the execution time of <code>ntptime</code> itself.

<code>**-e _est_error_**</code>

: Specify estimated error, in microseconds.

<code>**-f _frequency_**</code>

: Specify frequency offset, in parts per million.

<code>**-h**</code>

: Display times in Unix <code>timeval</code> format. Default is NTP format. 

<code>**-l**</code>

: Specify the leap bits as a code from 0 to 3. 

<code>**-m _max_error_**</code>

: Display help information.

<code>**-o _offset_**</code>

: Specify clock offset, in microseconds.

<code>**-r**</code>

: Display Unix and NTP times in raw format.

<code>**-s _status_**</code>

: Specify clock status. Better know what you are doing.

<code>**-t _time_constant_**</code>

: Specify time constant, an integer in the range 0-10.