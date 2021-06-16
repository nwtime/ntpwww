---
title: "tickadj - set time-related kernel variables"
type: archives
---

Last update: 10-Mar-2014 05:24 UTC

* * *

#### Table of Contents

*   [Synopsis](/archives/4.2.8-series/tickadj/#synopsis)
*   [Description](/archives/4.2.8-series/tickadj/#description)
*   [Command Line Options](/archives/4.2.8-series/tickadj/#command-line-options)
*   [Files](/archives/4.2.8-series/tickadj/#files)
*   [Bugs](/archives/4.2.8-series/tickadj/#bugs)

* * *

#### Synopsis

<tt>tickadj [ -Aqs ] [ -a _tickadj_ ] [ -t _tick_ ]</tt>

* * *

#### Description

The <tt>tickadj</tt> program reads, and optionally modifies, several timekeeping-related variables in older kernels that do not have support for precision timekeeping, including HP-UX, SunOS, Ultrix, SGI and probably others. Those machines provide means to patch the kernel <tt>/dev/kmem</tt>. Newer machines with kernel time support, including Solaris, Tru64, FreeBSD and Linux, should NOT use the program, even if it appears to work, as it will destabilize the kernel time support. Use the [<tt>ntptime</tt>](/archives/4.2.8-series/ntptime) program instead.

The particular variables that can be changed with <tt>tickadj</tt> include <tt>tick</tt>, which is the number of microseconds added to the system time for a clock interrupt, <tt>tickadj</tt>, which sets the slew rate and resolution used by the <tt>adjtime</tt> system call, and <tt>dosynctodr</tt>, which indicates to the kernels on some machines whether they should internally adjust the system clock to keep it in line with time-of-day clock or not.

By default, with no arguments, <tt>tickadj</tt> reads the variables of interest in the kernel and displays them. At the same time, it determines an "optimal" value for the value of the <tt>tickadj</tt> variable if the intent is to run the <tt>ntpd</tt> Network Time Protocol (NTP) daemon, and prints this as well. Since the operation of <tt>tickadj</tt> when reading the kernel mimics the operation of similar parts of the <tt>ntpd</tt> program fairly closely, this can be useful when debugging problems with <tt>ntpd</tt>.

Note that <tt>tickadj</tt> should be run with some caution when being used for the first time on different types of machines. The operations which <tt>tickadj</tt> tries to perform are not guaranteed to work on all Unix machines and may in rare cases cause the kernel to crash.

* * *

#### Command Line Options

<dt><tt>-a _tickadj_</tt></dt>

Set the kernel variable <tt>tickadj</tt> to the value _<tt>tickadj specified</tt>_.

<dt><tt>-A</tt></dt>

Set the kernel variable <tt>tickadj</tt> to an internally computed "optimal" value.

<dt><tt>-t _tick_</tt></dt>

Set the kernel variable <tt>tick</tt> to the value _<tt>tick</tt>_ specified.

<dt><tt>-s</tt></dt>

Set the kernel variable <tt>dosynctodr</tt> to zero, which disables the hardware time-of-year clock, a prerequisite for running the <tt>ntpd</tt> daemon under SunOS 4.x.

<dt><tt>-q</tt></dt>

Normally, <tt>tickadj</tt> is quite verbose about what it is doing. The <tt>-q</tt> flag tells it to shut up about everything except errors.

* * *

#### Files

<tt>/vmunix  
/unix  
/dev/kmem  
</tt>

* * *

#### Bugs

Fiddling with kernel variables at run time as a part of ordinary operations is a hideous practice which is only necessary to make up for deficiencies in the implementation of <tt>adjtime</tt> in many kernels and/or brokenness of the system clock in some vendors' kernels. It would be much better if the kernels were fixed and the <tt>tickadj</tt> program went away.