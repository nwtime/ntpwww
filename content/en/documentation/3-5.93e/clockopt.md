---
title: "Reference Clock Options"
type: archives
noindex: true
---

#### Table of Contents

*   [Reference Clock Support](/archives/3-5.93e/clockopt/#reference-clock-support)
*   [Reference Clock Commands](/archives/3-5.93e/clockopt/#reference-clock-commands)

* * *

#### Reference Clock Support

The NTP Version 3 daemon currently supports several different radio, satellite and modem reference clocks plus a special pseudo-clock used for backup or when no other clock source is available. Detailed descriptions of individual device drivers and options can be found in the [Reference Clock Drivers](/archives/3-5.93e/refclock/) page. Additional information can be found in the pages referenced there, including the [Debugging Hints for Reference Clock Drivers](/archives/3-5.93e/rdebug/) and [How To Write a Reference Clock Driver](/archives/3-5.93e/howto/) pages. In many drivers, support for a PPS signal is available as described in [Pulse-per-second (PPS) Signal Interfacing](/archives/3-5.93e/pps/) page. Many drivers support special line discipline/streams modules which can significantly improve the accuracy using the driver. These are described in the [Line Disciplines and Streams Drivers](/archives/3-5.93e/ldisc/) page.

A reference clock will generally (though not always) be a radio timecode receiver which is synchronized to a source of standard time such as the services offered by the NRC in Canada and NIST and USNO in the U.S. The interface between the computer and the timecode receiver is device dependent and will vary, but is often a serial port. A device driver specific to each clock must be selected and compiled in the distribution; however, most common radio, satellite and modem clocks are included by default. Note that an attempt to configure a reference clock when the driver has not been included or the hardware port has not been appropriately configured results in a scalding remark to the system log file, but is otherwise non hazardous. 

For the purposes of configuration, <code>xntpd</code> treats reference clocks in a manner analogous to normal NTP peers as much as possible. Reference clocks are identified by a syntactically correct but invalid IP address, in order to distinguish them from normal NTP peers. Reference clock addresses are of the form <code>127.127.t.u</code>, where <code>t</code> is an integer denoting the clock type and <code>u</code> indicates the type-specific unit number. The <code>server</code> command is used to configure a reference clock, where the <code>address</code> argument in that command is the clock address. The <code>key</code>, <code>version</code> and <code>ttl</code> options are not used for reference clock support. The <code>mode</code> option is added for reference clock support, as described below. The <code>prefer</code> option can be useful to persuade the server to cherish a reference clock with somewhat more enthusiasm than other reference clocks or peers. Further information on this option can be found in the [Mitigation Rules and the prefer Keyword](/archives/3-5.93e/prefer/) page. The <code>minpoll</code> and <code>maxpoll</code> options have meaning only for selected clock drivers. See the individual clock driver document pages for additional information.

The stratum number of a reference clock is by default zero. Since the <code>xntpd</code> daemon adds one to the stratum of each peer, a primary server ordinarily displays an external stratum of one. In order to provide engineered backups, it is often useful to specify the reference clock stratum as greater than zero. The <code>stratum</code> option is used for this purpose. Also, in cases involving both a reference clock and a pulse-per-second (PPS) discipline signal, it is useful to specify the reference clock identifier as other than the default, depending on the driver. The <code>refid</code> option is used for this purpose. Except where noted, these options apply to all clock drivers.

#### Reference Clock Commands

<code>**server 127.127._t.u_ [prefer] [mode _int_]**</code>

: This command can be used to configure reference clocks in special ways. The options are interpreted as follows:

<code>prefer</code>

: Marks the reference clock as preferred. All other things being equal, this host will be chosen for synchronization among a set of correctly operating hosts. See the [Mitigation Rules and the <code>prefer</code> Keyword](/archives/3-5.93e/prefer/) page for further information.

<code>mode _int_</code>

: Specifies a mode number which is interpreted in a device-specific fashion. For instance, it selects a dialing protocol in the ACTS driver and a device subtype in the <code>parse</code> drivers.

<code>minpoll _minpoll_</code>

: This option specifies the minimum polling interval for NTP messages, in seconds to the power of two. The allowable range is 4 (16 s to 14 (16384 s) inclusive. The default is 6 (64 s) for all except modem reference clocks, where the default is 10 (1024 s). 

<code>maxpoll _maxpoll_</code>

: This option specifies the maximum polling interval for NTP messages, in seconds to the power of two. The allowable range is 4 (16 s to 14 (16384 s) inclusive. The default is 6 (64 s) for all except modem reference clocks, where the default is 14 (16384 s). 

<code>**fudge 127.127._t.u_ [time1 _sec_] [time2 _sec_] [stratum _int_] [refid _string_] [mode _int_] [flag1 0|1] [flag2 0|1] [flag3 0|1] [flag4 0|1]**</code>

: This command can be used to configure reference clocks in special ways. It must immediately follow the <code>server</code> command which configures the driver. Note that the same capability is possible at run time using the <code>[xntpdc](/archives/3-5.93e/xntpdc/)</code> program. The options are interpreted as follows:

<code>time1 _secs_</code>

: Specifies a constant to be added to the time offset produced by the driver, a fixed-point decimal number in seconds. This is used as a calibration constant to adjust the nominal time offset of a particular clock to agree with an external standard, such as a precision PPS signal. It also provides a way to correct a systematic error or bias due to serial port latencies, different cable lengths or receiver internal delay. The specified offset is in addition to the propagation delay provided by other means, such as internal DIPswitches. Where a calibration for an individual system and driver is available, an approximate correction is noted in the driver documentation pages. 

<code>time2 _secs_</code>

: Specifies a fixed-point decimal number in seconds, which is interpreted in a driver-dependent way. See the descriptions of specific drivers in the [reference clock drivers](/archives/3-5.93e/refclock/) page.

<code>stratum _int_</code>

: Specifies the stratum number assigned to the driver, an integer between 0 and 15. This number overrides the default stratum number ordinarily assigned by the driver itself, usually zero.

<code>refid _string_</code>

: Specifies an ASCII string of from one to four characters which defines the reference identifier used by the driver. This string overrides the default identifier ordinarily assigned by the driver itself.

<code>mode _int_</code>

: Specifies a mode number which is interpreted in a device-specific fashion. For instance, it selects a dialing protocol in the ACTS driver and a device subtype in the <code>parse</code> drivers. 

<code>flag1 flag2 flag3 flag4</code>

: These four flags are used for customizing the clock driver. The interpretation of these values, and whether they are used at all, is a function of the particular clock driver. However, by convention, and unless indicated otherwise, <code>flag3</code> is used to attach the <code>ppsclock</code> streams module to the configured driver, while <code>flag4</code> is used to enable recording verbose monitoring data to the clockstats file configured with the <code>filegen</code> command. Further information on the <code>ppsclock</code> streams module can be found in the [Pulse-per-second (PPS) Signal Interfacing](/archives/3-5.93e/pps/) page. Further information on the <code>filegen</code> command can be found in the [Monitoring Options](/archives/3-5.93e/monopt/) page.