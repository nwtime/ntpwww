---
title: "Reference Clock Options"
type: archives
---

![gif](/archives/pic/stack1a.jpg)Master Time Facility at the [UDel Internet Research Laboratory](/reflib/lab)

Last update: 04-Oct-2009 19:42 UTC

* * *

#### Table of Contents

*   [Reference Clock Support](/archives/4.2.6-series/clockopt/#reference-clock-support)
*   [Reference Clock Commands](/archives/4.2.6-series/clockopt/#reference-clock-commands)

* * *

#### Reference Clock Support

The NTP Version 4 daemon supports some three dozen different radio, satellite and modem reference clocks plus a special pseudo-clock used for backup or when no other clock source is available. Detailed descriptions of individual device drivers and options can be found in the [Reference Clock Drivers](/archives/4.2.6-series/refclock) page. Additional information can be found in the pages linked there, including the [Debugging Hints for Reference Clock Drivers](/archives/4.2.6-series/rdebug) and [How To Write a Reference Clock Driver](/archives/4.2.6-series/howto) pages. In addition, support for a PPS signal is available as described in [Pulse-per-second (PPS) Signal Interfacing](/archives/4.2.6-series/pps) page.

A reference clock will generally (though not always) be a radio timecode receiver which is synchronized to a source of standard time such as the services offered by the NRC in Canada and NIST and USNO in the US. The interface between the computer and the timecode receiver is device dependent, but is usually a serial port. A device driver specific to each reference clock must be selected and compiled in the distribution; however, most common radio, satellite and modem clocks are included by default. Note that an attempt to configure a reference clock when the driver has not been compiled or the hardware port has not been appropriately configured results in a scalding remark to the system log file, but is otherwise non hazardous.

For the purposes of configuration, <tt>ntpd</tt> treats reference clocks in a manner analogous to normal NTP peers as much as possible. Reference clocks are identified by a syntactically correct but invalid IP address, in order to distinguish them from normal NTP peers. Reference clock addresses are of the form <tt>127.127._t.u_</tt>, where _<tt>t</tt>_ is an integer denoting the clock type and _<tt>u</tt>_ indicates the unit number in the range 0-3. While it may seem overkill, it is in fact sometimes useful to configure multiple reference clocks of the same type, in which case the unit numbers must be unique.

The <tt>server</tt> command is used to configure a reference clock, where the _<tt>address</tt>_ argument in that command is the clock address. The <tt>key</tt>, <tt>version</tt> and <tt>ttl</tt> options are not used for reference clock support. The <tt>mode</tt> option is added for reference clock support, as described below. The <tt>prefer</tt> option can be useful to persuade the server to cherish a reference clock with somewhat more enthusiasm than other reference clocks or peers. Further information on this option can be found in the [Mitigation Rules and the <tt>prefer</tt> Keyword](/archives/4.2.6-series/prefer) page. The <tt>minpoll</tt> and <tt>maxpoll</tt> options have meaning only for selected clock drivers. See the individual clock driver document pages for additional information.

The <tt>fudge</tt> command is used to provide additional information for individual clock drivers and normally follows immediately after the <tt>server</tt> command. The _<tt>address</tt>_ argument specifies the clock address. The <tt>refid</tt> and <tt>stratum</tt> options control can be used to override the defaults for the device. There are two optional device-dependent time offsets and four flags that can be included in the <tt>fudge</tt> command as well.

The stratum number of a reference clock is by default zero. Since the <tt>ntpd</tt> daemon adds one to the stratum of each peer, a primary server ordinarily displays an external stratum of one. In order to provide engineered backups, it is often useful to specify the reference clock stratum as greater than zero. The <tt>stratum</tt> option is used for this purpose. Also, in cases involving both a reference clock and a pulse-per-second (PPS) discipline signal, it is useful to specify the reference clock identifier as other than the default, depending on the driver. The <tt>refid</tt> option is used for this purpose. Except where noted, these options apply to all clock drivers.

#### Reference Clock Commands

<dt id="server"><tt>server 127.127._t.u_ [prefer] [mode _int_] [minpoll _int_] [maxpoll _int_]</tt></dt>

This command can be used to configure reference clocks in special ways. The options are interpreted as follows:

&nbsp;&nbsp;&nbsp;&nbsp;<tt>prefer</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Marks the reference clock as preferred. All other things being equal, this host will be chosen for synchronization among a set of correctly operating hosts. See the [Mitigation Rules and the <tt>prefer</tt> Keyword](/archives/4.2.6-series/prefer) page for further information.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>mode _int_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Specifies a mode number which is interpreted in a device-specific fashion. For instance, it selects a dialing protocol in the ACTS driver and a device subtype in the <tt>parse</tt> drivers.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>minpoll _int_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;<tt>maxpoll _int_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;These options specify the minimum and maximum polling interval for reference clock messages in seconds, interpreted as dual logarithms (2 ^ x). For most directly connected reference clocks, both <tt>minpoll</tt> and <tt>maxpoll</tt> default to 6 (2^16 = 64 s). For modem reference clocks, <tt>minpoll</tt> defaults to 10 (2^10 = 1024 s = 17.1 m) and <tt>maxpoll</tt> defaults to 14 (2^14 = 16384 s = 4.5 h). The allowable range is 4 (16 s) to 17 (36.4 h) inclusive.

<dt id="fudge"><tt>fudge 127.127._t.u_ [time1 _sec_] [time2 _sec_] [stratum _int_] [refid _string_] [flag1 0|1] [flag2 0|1] [flag3 0|1] [flag4 0|1]</tt></dt>

This command can be used to configure reference clocks in special ways. It must immediately follow the <tt>server</tt> command which configures the driver. Note that the same capability is possible at run time using the <tt>[ntpdc](/archives/4.2.6-series/ntpdc)</tt> program. The options are interpreted as follows:

&nbsp;&nbsp;&nbsp;&nbsp;<tt>time1 _sec_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Specifies a constant to be added to the time offset produced by the driver, a fixed-point decimal number in seconds. This is used as a calibration constant to adjust the nominal time offset of a particular clock to agree with an external standard, such as a precision PPS signal. It also provides a way to correct a systematic error or bias due to serial port or operating system latencies, different cable lengths or receiver internal delay. The specified offset is in addition to the propagation delay provided by other means, such as internal DIPswitches. Where a calibration for an individual system and driver is available, an approximate correction is noted in the driver documentation pages.

**Note:** in order to facilitate calibration when more than one radio clock or PPS signal is supported, a special calibration feature is available. It takes the form of an argument to the <tt>enable</tt> command described in the [Miscellaneous Options](/archives/4.2.6-series/miscopt) page and operates as described in the [Reference Clock Drivers](/archives/4.2.6-series/refclock) page.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>time2 _secs_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Specifies a fixed-point decimal number in seconds, which is interpreted in a driver-dependent way. See the descriptions of specific drivers in the [reference clock drivers](/archives/4.2.6-series/refclock) page.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>stratum _int_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Specifies the stratum number assigned to the driver, an integer between 0 and 15. This number overrides the default stratum number ordinarily assigned by the driver itself, usually zero.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>refid _string_</tt>

&nbsp;&nbsp;&nbsp;&nbsp;Specifies an ASCII string of from one to four characters which defines the reference identifier used by the driver. This string overrides the default identifier ordinarily assigned by the driver itself.

&nbsp;&nbsp;&nbsp;&nbsp;<tt>flag1 flag2 flag3 flag4</tt>

&nbsp;&nbsp;&nbsp;&nbsp;These four flags are used for customizing the clock driver. The interpretation of these values, and whether they are used at all, is a function of the particular clock driver. However, by convention <tt>flag4</tt> is used to enable recording monitoring data to the <tt>clockstats</tt> file configured with the <tt>filegen</tt> command. Further information on the <tt>filegen</tt> command can be found in the [Monitoring Options](/archives/4.2.6-series/monopt) page.