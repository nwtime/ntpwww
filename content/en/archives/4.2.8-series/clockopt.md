---
title: "Reference Clock Commands and Options"
type: archives
---

![gif](/archives/pic/stack1a.jpg)Master Time Facility at the [UDel Internet Research Laboratory](/reflib/lab)

Last update: 26-Sep-2019 06:34 UTC

* * *

#### Table of Contents

*   [Reference Clock Addresses](/archives/4.2.8-series/clockopt/#reference-clock-addresses)
*   [Commands and Options](/archives/4.2.8-series/clockopt/#commands-and-options)

* * *

#### Reference Clock Addresses

Unless noted otherwise, further information about these commands is on the [Reference Clock Support](/archives/4.2.8-series/refclock) page.

Reference clocks are identified by a syntactically correct but invalid IP address, in order to distinguish them from ordinary NTP peers. These addresses are of the form 127.127._t_._u_, where _t_ is an integer denoting the clock type and _u_ indicates the unit number in the range 0-3. While it may seem overkill, it is in fact sometimes useful to configure multiple reference clocks of the same type, in which case the unit numbers must be unique.

* * *

#### Commands and Options

<dt id="server"><tt>server 127.127._t.u_ [prefer] [mode _int_] [minpoll _int_] [maxpoll _int_]</tt></dt>

This command can be used to configure reference clocks in special ways. The options are interpreted as follows:

<dt><tt>prefer</tt></dt>

Marks the reference clock as preferred. All other things being equal, this host will be chosen for synchronization among a set of correctly operating hosts. See the [Mitigation Rules and the <tt>prefer</tt> Keyword](/archives/4.2.8-series/prefer) page for further information.

<dt><tt>mode _int_</tt></dt>

Specifies a mode number which is interpreted in a device-specific fashion. For instance, it selects a dialing protocol in the ACTS driver and a device subtype in the <tt>parse</tt> drivers.

<dt><tt>minpoll _int_</tt>  
<tt>maxpoll _int_</tt></dt>

These options specify the minimum and maximum polling interval for reference clock messages in log<sub>2</sub> seconds. For most directly connected reference clocks, both <tt>minpoll</tt> and <tt>maxpoll</tt> default to 6 (64 s). For modem reference clocks, <tt>minpoll</tt> is ordinarily set to 10 (about 17 m) and <tt>maxpoll</tt> to 15 (about 9 h). The allowable range is 4 (16 s) to 17 (36 h) inclusive.

<dt id="fudge"><tt>fudge 127.127._t.u_ [time1 _sec_] [time2 _sec_] [stratum _int_] [refid _string_] [flag1 0|1] [flag2 0|1] [flag3 0|1] [flag4 0|1]</tt></dt>

This command can be used to configure reference clocks in special ways. It must immediately follow the <tt>server</tt> command which configures the driver. Note that the same capability is possible at run time using the <tt>[ntpdc](/archives/4.2.8-series/ntpdc)</tt> program. The options are interpreted as follows:

<dt><tt>time1 _sec_</tt></dt>

Specifies a constant to be added to the time offset produced by the driver, a fixed-point decimal number in seconds. This is used as a calibration constant to adjust the nominal time offset of a particular clock to agree with an external standard, such as a precision PPS signal. It also provides a way to correct a systematic error or bias due to serial port or operating system latencies, different cable lengths or receiver internal delay. The specified offset is in addition to the propagation delay provided by other means, such as internal DIPswitches. Where a calibration for an individual system and driver is available, an approximate correction is noted in the driver documentation pages.

{{% alert title="Note" color="warning" %}} 
In order to facilitate calibration when more than one radio clock or PPS signal is supported, a special calibration feature is available. It takes the form of an argument to the <tt>enable</tt> command described in the [Miscellaneous Options](/archives/4.2.8-series/miscopt) page and operates as described in the [Reference Clock Support](/archives/4.2.8-series/refclock) page.
{{% /alert %}}

<dt><tt>time2 _secs_</tt></dt>

Specifies a fixed-point decimal number in seconds, which is interpreted in a driver-dependent way. See the descriptions of specific drivers in the [Reference Clock Support](/archives/4.2.8-series/refclock) page.

<dt><tt>stratum _int_</tt></dt>

Specifies the stratum number assigned to the driver in the range 0 to 15, inclusive. This number overrides the default stratum number ordinarily assigned by the driver itself, usually zero.

<dt><tt>refid _string_</tt></dt>

Specifies an ASCII string of from one to four characters which defines the reference identifier used by the driver. This string overrides the default identifier ordinarily assigned by the driver itself.

<dt><tt>flag1 flag2 flag3 flag4</tt></dt>

These four flags are used for customizing the clock driver. The interpretation of these values, and whether they are used at all, is a function of the particular driver. However, by convention <tt>flag4</tt> is used to enable recording monitoring data to the <tt>clockstats</tt> file configured with the <tt>filegen</tt> command. Additional information on the <tt>filegen</tt> command is on the [Monitoring Options](/archives/4.2.8-series/monopt) page.

<dt><tt>minjitter _secs_</tt></dt>

If the source has a jitter that cannot be sensibly estimated, because it is not statistic jitter, the source will be detected as falseticker sooner or later. This has been observed e.g. with the serial data of certain GPS receivers. Enforcing a minimal jitter value avoids a too low estimation, keeping the clock in the zoo while still detecting higher jitter.

{{% alert title="Note" color="warning" %}}
This changes the refclock samples and ends up in the clock dispersion, not the clock jitter, despite being called jitter. To see the modified values, check the NTP clock variable "filtdisp", not "jitter".
{{% /alert %}}

The falseticker problem can also be avoided by increasing <tt>tos mindist</tt>, which extends the intersection interval, but that affects the root dispersion and is intended for the case of multiple reference clocks with reliable jitter that do not intersect otherwise.