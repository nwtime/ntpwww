---
title: "Reference Clock Commands and Options"
description: "Descriptions of the commands and options available to reference clocks."
type: archives
aliases:
    - /current-stable/clockopt/
---

![webp](/documentation/pic/stack1a.webp) Master Time Facility at the [UDel Internet Research Laboratory](/reflib/lab/)

* * *

#### Table of Contents

*   [Reference Clock Addresses](/documentation/4.2.8-series/clockopt/#reference-clock-addresses)
*   [Commands and Options](/documentation/4.2.8-series/clockopt/#commands-and-options)

* * *

#### Reference Clock Addresses

Unless noted otherwise, further information about these commands is on the [Reference Clock Support](/documentation/4.2.8-series/refclock/) page.

Reference clocks are identified by a syntactically correct but invalid IP address, in order to distinguish them from ordinary NTP peers. These addresses are of the form <code>127.127._t_._u_</code>, where <code>_t_</code> is an integer denoting the clock type and <code>_u_</code> indicates the unit number in the range 0-3. While it may seem overkill, it is in fact sometimes useful to configure multiple reference clocks of the same type, in which case the unit numbers must be unique.

* * *

#### Commands and Options

<code>**server 127.127._t.u_ [prefer] [mode _int_] [minpoll _int_] [maxpoll _int_]**</code>

: This command can be used to configure reference clocks in special ways. The options are interpreted as follows:

<code>prefer</code>

: Marks the reference clock as preferred. All other things being equal, this host will be chosen for synchronization among a set of correctly operating hosts. See the [Mitigation Rules and the <code>prefer</code> Keyword](/documentation/4.2.8-series/prefer/) page for further information.

<code>mode _int_</code>

: Specifies a mode number which is interpreted in a device-specific fashion. For instance, it selects a dialing protocol in the ACTS driver and a device subtype in the <code>parse</code> drivers.

<code>minpoll _int_</code>
<code>maxpoll _int_</code>

: These options specify the minimum and maximum polling interval for reference clock messages in log<sub>2</sub> seconds. For most directly connected reference clocks, both <code>minpoll</code> and <code>maxpoll</code> default to 6 (64 s). For modem reference clocks, <code>minpoll</code> is ordinarily set to 10 (about 17 m) and <code>maxpoll</code> to 15 (about 9 h). The allowable range is 4 (16 s) to 17 (36 h) inclusive.

<code>**fudge 127.127._t.u_ [time1 _sec_] [time2 _sec_] [stratum _int_] [refid _string_] [flag1 0|1] [flag2 0|1] [flag3 0|1] [flag4 0|1]**</code>

: This command can be used to configure reference clocks in special ways. It must immediately follow the <code>server</code> command which configures the driver. Note that the same capability is possible at run time using the [<code>ntpdc</code>](/documentation/4.2.8-series/ntpdc/) program. The options are interpreted as follows:

<code>**time1 _sec_**</code>

: Specifies a constant to be added to the time offset produced by the driver, a fixed-point decimal number in seconds. This is used as a calibration constant to adjust the nominal time offset of a particular clock to agree with an external standard, such as a precision PPS signal. It also provides a way to correct a systematic error or bias due to serial port or operating system latencies, different cable lengths or receiver internal delay. The specified offset is in addition to the propagation delay provided by other means, such as internal DIPswitches. Where a calibration for an individual system and driver is available, an approximate correction is noted in the driver documentation pages.

> **NOTE:** In order to facilitate calibration when more than one radio clock or PPS signal is supported, a special calibration feature is available. It takes the form of an argument to the <code>enable</code> command described in the [Miscellaneous Options](/documentation/4.2.8-series/miscopt/) page and operates as described in the [Reference Clock Support](/documentation/4.2.8-series/refclock/) page.

<code>**time2 _secs_**</code>

: Specifies a fixed-point decimal number in seconds, which is interpreted in a driver-dependent way. See the descriptions of specific drivers in the [Reference Clock Support](/documentation/4.2.8-series/refclock/) page.

<code>**stratum _int_**</code>

: Specifies the stratum number assigned to the driver in the range 0 to 15, inclusive. This number overrides the default stratum number ordinarily assigned by the driver itself, usually zero.

<code>**refid _string_**</code>

: Specifies an ASCII string of from one to four characters which defines the reference identifier used by the driver. This string overrides the default identifier ordinarily assigned by the driver itself.

<code>**flag1 flag2 flag3 flag4**</code>

: These four flags are used for customizing the clock driver. The interpretation of these values, and whether they are used at all, is a function of the particular driver. However, by convention <code>flag4</code> is used to enable recording monitoring data to the <code>clockstats</code> file configured with the <code>filegen</code> command. Additional information on the <code>filegen</code> command is on the [Monitoring Options](/documentation/4.2.8-series/monopt/) page.

<code>**minjitter _secs_**</code>

: If the source has a jitter that cannot be sensibly estimated, because it is not statistic jitter, the source will be detected as falseticker sooner or later. This has been observed e.g. with the serial data of certain GPS receivers. Enforcing a minimal jitter value avoids a too low estimation, keeping the clock in the zoo while still detecting higher jitter.

> **NOTE:** This changes the refclock samples and ends up in the clock dispersion, not the clock jitter, despite being called jitter. To see the modified values, check the NTP clock variable <code>filtdisp</code>, not <code>jitter</code>.

The falseticker problem can also be avoided by increasing <code>tos mindist</code>, which extends the intersection interval, but that affects the root dispersion and is intended for the case of multiple reference clocks with reliable jitter that do not intersect otherwise.