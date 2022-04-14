---
title: "tickadj - set time-related kernel variables"
type: archives
noindex: true 
sitemap_exclude: true
---

#### Table of Contents

*   [Synopsis](/documentation/4.1.1/tickadj/#synopsis)
*   [Description](/documentation/4.1.1/tickadj/#description)
*   [Command Line Options](/documentation/4.1.1/tickadj/#command-line-options)
*   [Files](/documentation/4.1.1/tickadj/#files)
*   [Bugs](/documentation/4.1.1/tickadj/#bugs)

* * *

#### Synopsis

<code>tickadj [ -Aqs ] [ -a _tickadj_ ] [ -t _tick_ ]</code>

* * *

#### Description

The <code>tickadj</code> program reads, and optionally modifies, several timekeeping-related variables in the running kernel in some machines, via <code>/dev/kmem</code>. The particular variables it is concerned with are <code>tick</code>, which is the number of microseconds added to the system time for a clock interrupt, <code>tickadj</code>, which sets the slew rate and resolution used by the <code>adjtime</code> system call, and <code>dosynctodr</code>, which indicates to the kernels on some machines whether they should internally adjust the system clock to keep it in line with time-of-day clock or not.

Note that this program does NOT work in some kernels, in particular Solaris 2.6 or later. See the [report](/documentation/hints/solaris-dosynctodr/).

By default, with no arguments, <code>tickadj</code> reads the variables of interest in the kernel and displays them. At the same time, it determines an "optimal" value for the value of the <code>tickadj</code> variable if the intent is to run the <code>ntpd</code> Network Time Protocol (NTP) daemon, and prints this as well. Since the operation of <code>tickadj</code> when reading the kernel mimics the operation of similar parts of the <code>ntpd</code> program fairly closely, this can be useful when debugging problems with <code>ntpd</code>.

Note that <code>tickadj</code> should be run with some caution when being used for the first time on different types of machines. The operations which <code>tickadj</code> tries to perform are not guaranteed to work on all Unix machines and may in rare cases cause the kernel to crash.

* * *

#### Command Line Options

<code>**-a _tickadj_**</code>

: Set the kernel variable <code>tickadj</code> to the value <code>_tickadj_</code> specified.

<code>**-A**</code>

: Set the kernel variable <code>tickadj</code> to an internally computed "optimal" value.

<code>**-t _tick_**</code>

: Set the kernel variable <code>tick</code> to the value <code>_tick_</code> specified.

<code>**-s**</code>

: Set the kernel variable <code>dosynctodr</code> to zero, which disables the hardware time-of-year clock, a prerequisite for running the <code>ntpd</code> daemon under SunOS4.

<code>**-q**</code>

: Normally, <code>tickadj</code> is quite verbose about what it is doing. The <code>-q</code> flag tells it to shut up about everything except errors.

* * *

#### Files

<code>/vmunix  
/unix  
/dev/kmem  
</code>

* * *

#### Bugs

Fiddling with kernel variables at run time as a part of ordinary operations is a hideous practice which is only necessary to make up for deficiencies in the implementation of <code>adjtime</code> in many kernels and/or brokenness of the system clock in some vendors' kernels. It would be much better if the kernels were fixed and the <code>tickadj</code> program went away.