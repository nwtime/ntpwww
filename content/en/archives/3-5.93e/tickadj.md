---
title: "tickadj - set time-related kernel variables"
type: archives
---

#### Table of Contents

*   [Synopsis](/archives/3-5.93e/tickadj/#synopsis)
*   [Description](/archives/3-5.93e/tickadj/#description)
*   [Command Line Options](/archives/3-5.93e/tickadj/#command-line-options)
*   [Files](/archives/3-5.93e/tickadj/#files)
*   [Bugs](/archives/3-5.93e/tickadj/#bugs)

* * *

#### Synopsis

<tt>tickadj [ -Aqs ] [ -a _tickadj_ ] [ -t _tick_ ]</tt>

* * *

#### Description

The <tt>tickadj</tt> program reads, and optionally modifies, several timekeeping-related variables in the running kernel, via <tt>/dev/kmem</tt>. The particular variables it is concerned with are <tt>tick</tt>, which is the number of microseconds added to the system time for a clock interrupt, <tt>tickadj</tt>, which sets the slew rate and resolution used by the <tt>adjtime</tt> system call, and <tt>dosynctodr</tt>, which indicates to the kernels on some machines whether they should internally adjust the system clock to keep it in line with time-of-day clock or not.

By default, with no arguments, <tt>tickadj</tt> reads the variables of interest in the kernel and displays them. At the same time, it determines an "optimal" value for the value of the <tt>tickadj</tt> variable if the intent is to run the <tt>xntpd</tt> Network Time Protocol (NTP) daemon, and prints this as well. Since the operation of <tt>tickadj</tt> when reading the kernel mimics the operation of similar parts of the <tt>xntpd</tt> program fairly closely, this can be useful when debugging problems with <tt>xntpd</tt>.

Note that <tt>tickadj</tt> should be run with some caution when being used for the first time on different types of machines. The operations which <tt>tickadj</tt> tries to perform are not guaranteed to work on all Unix machines and may in rare cases cause the kernel to crash.

* * *

#### Command Line Options

<dt><tt>-a _tickadj_</tt></dt>

Set the kernel variable <tt>tickadj</tt> to the value _<tt>tickadj</tt>_ specified.

<dt><tt>-A</tt></dt>

Set the kernel variable <tt>tickadj</tt> to an internally computed "optimal" value.

<dt><tt>-t _tick_</tt></dt>

Set the kernel variable <tt>tick</tt> to the value _<tt>tick</tt>_ specified.

<dt><tt>-s</tt></dt>

Set the kernel variable <tt>dosynctodr</tt> to zero, which disables the hardware time-of-year clock, a prerequisite for running the <tt>xntpd</tt> daemon under SunOS4.

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