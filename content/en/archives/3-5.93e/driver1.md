---
title: "Undisciplined Local Clock"
type: archives
---

#### Table of Contents

*   [Synopsis](/archives/3-5.93e/driver1/#synopsis)
*   [Description](/archives/3-5.93e/driver1/#description)
*   [Monitor Data](/archives/3-5.93e/driver1/#monitor-data)
*   [Fudge Factors](/archives/3-5.93e/driver1/#fudge-factors)
*   [Additional Information](/archives/3-5.93e/driver1/#additional-information)

* * *

#### Synopsis

Address: 127.127.1._u_  
Reference ID: <tt>LCL</tt>  
Driver ID: <tt>LOCAL</tt>

* * *

#### Description

This is a hack to allow a machine to use its own system clock as a reference clock, i.e., to free-run using no outside clock discipline source. This is useful if NTP is to be used in an isolated environment with no radio clock or NIST modem available. Pick a machine that has a good clock oscillator (Digital machines are good, Sun machines are not) and configure it with this driver. Set the clock using the best means available, like eyeball-and-wristwatch. Then, point all the other machines at this one or use broadcast (not multicast) mode to distribute time. 

Another application for this driver is if a particular server clock is to be used as the clock of last resort when all other normal synchronization sources have gone away. This is especially useful if that server has an ovenized oscillator. For this you would configure this driver at a stratum greater than any other likely sources of time (say 3 or 4) to prevent the server taking over when legitimate sources are still available.

A third application for this driver is when an external discipline source is available, such as the NIST <tt>lockclock</tt> program, which synchronizes the local clock via a telephone modem and the NIST Automated Computer Time Service (ACTS), or the Digital Time Synchronization Service (DTSS), which runs on DCE machines. In this case the stratum should be set at zero, indicating a bona fide stratum-1 source. Exercise some caution with this, since there is no easy way to telegraph via NTP that something might be wrong in the discipline source itself. In the case of DTSS, the local clock can have a rather large jitter, depending on the interval between corrections and the intrinsic frequency error of the clock oscillator. In extreme cases, this can cause clients to exceed the 128-ms slew window and drop off the NTP subnet. In the default mode the behavior of the clock selection algorithm is modified when this driver is in use. The algorithm is designed so that this driver will never be selected unless no other discipline source is available. This can be overridden with the <tt>prefer</tt> keyword of the <tt>server</tt> configuration command, in which case only this driver will be selected for synchronization and all other discipline sources will be ignored. This behavior is intended for use when an external discipline source controls the system clock. See the [Mitigation Rules and the prefer Keyword](/archives/3-5.93e/prefer) page for a detailed description of the finicky behavior.

The stratum for this driver is set at 3 by default, but can be changed by the <tt>fudge</tt> configuration command and/or the <tt>xntpdc</tt> utility. The reference ID is LCL by default, but can be changed using the same mechanisms. **NEVER** configure this driver to operate at a stratum which might possibly disrupt a client with access to a bona fide primary server, unless the local clock oscillator is reliably disciplined by another source. **NEVER NEVER** configure a server which might devolve to an undisciplined local clock to use multicast mode.

This driver provides a mechanism to trim the local clock in both time and frequency, as well as a way to manipulate the leap bits. The <tt>fudge time1</tt> parameter adjusts the time (in seconds) and the <tt>fudge time2</tt> parameter adjusts the frequency (in parts per million). Both parameters are additive and operate only once; that is, each command (as from <tt>xntpdc</tt>) adds signed increments in time or frequency to the nominal local clock time and frequency. (Note: The frequency cannot be changed when the kernel modifications are in use - see the [A Kernel Model for Precision Timekeeping](/archives/3-5.93e/kern) page.) The <tt>fudge flag1</tt> and <tt>fudge flag2</tt> flags set the corresponding leap bits; for example, setting only <tt>flag1</tt> causes a leap second to be inserted at the end of the UTC day and setting only <tt>flag2</tt> causes a leap second to be deleted at the end of the UTC day. Setting both flags causes the local clock driver to appear unsynchronized, which may be a blessing if a server violates the above rules, since <tt>xntpdc</tt> can turn the bugger off. These bits are not reset automatically when the leap takes place; they must be turned off manually after the leap event and before the next UTC day. 

* * *

#### Monitor Data

No <tt>filegen clockstats</tt> monitor data are produced by this driver.

* * *

#### Fudge Factors

<dl>

<dt><tt>time1 _time_</tt></dt>

Specifies the time offset calibration factor, in seconds and fraction, with default 0.0.

<dt><tt>time2 _time_</tt></dt>

Specifies the frequency offset calibration factor, in parts per million, with default 0.0.

<dt><tt>stratum _number_</tt></dt>

Specifies the driver stratum, in decimal from 0 to 15, with default 3.

<dt><tt>refid _string_</tt></dt>

Specifies the driver reference identifier, an ASCII string from one to four characters, with default <tt>LCL</tt>.

<dt><tt>flag1 0 | 1</tt></dt>

Specifies a leap second to be inserted at the end of the current UTC day.

<dt><tt>flag2 0 | 1</tt></dt>

Specifies a leap second to be deleted at the end of the current UTC day. 

<dt><tt>flag3 0 | 1</tt></dt>

Not used by this driver.

<dt><tt>flag4 0 | 1</tt></dt>

Not used by this driver.

* * *

#### Additional Information

[Reference Clock Drivers](/archives/3-5.93e/refclock)
