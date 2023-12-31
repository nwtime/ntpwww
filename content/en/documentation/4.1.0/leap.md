---
title: "NTP Timescale and Leap Seconds"
type: archives
noindex: true 
sitemap_exclude: true
--- 

![gif](/documentation/pic/alice15.gif) [from _Alice's Adventures in Wonderland_, Lewis Carroll](/reflib/pictures/)

The Mad Hatter and the March Hare are discussing whether the Teapot serial number should have two or four digits.  

* * *

#### Table of Contents

*  [Introduction](/documentation/4.1.0/leap/#introduction)
*  [The NTP Timescale](/documentation/4.1.0/leap/#the-ntp-timescale)
*  [Conversion to Other Timescales](/documentation/4.1.0/leap/#conversion-to-other-timescales)
*  [Timescale Resolution and the Tick Interval](/documentation/4.1.0/leap/#timescale-resolution-and-the-tick-interval)
*  [Leap Seconds](/documentation/4.1.0/leap/#leap-seconds)
*  [Reckoning with NTP and UTC Leap seconds](/documentation/4.1.0/leap/#reckoning-with-ntp-and-utc-leap-seconds)

* * *

#### Introduction

In the year 2001 the Network Time Protocol (NTP) has been in use for over two decades and remains the longest running, continuously operating application protocol in the Internet. There was some concern, especially in government and financial institutions, that NTP might cause Internet applications to misbehave in terrible ways on the epoch of the new century, but this didn't happen. However, how NTP reckons the time is important when considering the relationship between NTP time and conventional civil time.

This document presents an analysis of the NTP timescale, in particular the metrication relative to the conventional civil timescale and when the NTP timescale rolls over in 2036. These issues are also important with respect to the Unix timescale, but that rollover will not happen until 2038. This document does not establish a standard, nor does it present specific algorithms which metricate the NTP timescale with respect to other timescales.

* * *

#### The NTP Timescale

It will be helpful in understanding the issues raised in this document to consider the concept of a universal timescale. The conventional civil timescale used in most parts of the world is based on Coordinated Universal Time (UTC) (sic), formerly known as Greenwich Mean Time (GMT). UTC is based on International Atomic Time (TAI sic), which is derived from hundreds of cesium clocks in the national standards laboratories of many countries. Deviations of UTC from TAI are implemented in the form of leap seconds, which occur on average every eighteen months.

For almost every computer application today, UTC represents the universal timescale extending into the indefinite past and indefinite future. We know of course that the UTC timescale did not exist prior to 1972, the Gregorian calendar did not exist prior to 1582, the Julian calendar did not exist prior to 54 BC and we cannot predict exactly when the next leap second will occur. Nevertheless, most folks would prefer that, even if we can't get future seconds numbering right beyond the next leap second, at least we can get the days numbering right until the end of reason.

The universal timescale can be implemented using a binary counter of indefinite width and with the unit seconds bit placed somewhere in the middle. The counter is synchronized to UTC such that it runs at the same rate (also the rate of TAI) and the units increment coincides with the UTC seconds tick. The NTP timescale is constructed from 64 bits of this counter, of which 32 bits number the seconds and 32 bits represent the fraction. With this design, the counter runs in 136-year cycles, called eras, the latest of which began with a counter value of zero at 0h 1 January 1900. The next era will begin when the seconds counter rolls over sometime in 2036. The design assumption is that further low order bits, if required, are provided by local interpolation, while further high order bits, when required, are provided by external means.

The important point to be made here is that the high order bits must ultimately be provided by astronomers and disseminated to the population by international means. Ultimately, should a need exist to align a particular NTP era to the current calendar, the operating system in which NTP is embedded must provide the necessary high order bits, most conveniently from the file system or flash memory.

With respect to the recent year 2000 issue, the most important thing to observe about the NTP timescale is that it knows nothing about days, years or centuries, only the seconds since the beginning of the current era which began on 1 January 1900. On 1 January 1970 when Unix life began, the NTP timescale showed 2,208,988,800 and on 1 January 1972 when UTC life began, it showed 2,272,060,800. On the last second of the year 1999, the NTP timescale showed 3,155,673,599 and one second later on the first second of the next century showed 3,155,673,600. Other than this observation, the NTP timescale has no knowledge of or provision for any of these eclectic seconds.

* * *

#### Conversion to Other Timescales

The NTP timescale is almost never used directly by system or application programs. The generic Unix kernel keeps time in seconds and microseconds (or nanoseconds) to provide both time of day and interval timer functions. In order to synchronize the Unix clock, NTP must convert to and from NTP representation and Unix representation. Unix kernels implement the time of day function using two 32-bit counters, one representing the signed seconds since Unix life began and the other the microseconds or nanoseconds of the second. In principle, the seconds counter will change sign in 2038. How the particular Unix semantics interprets the counter values is of concern, but is beyond the scope of discussion here.

While incorrect NTP time values are unlikely in a properly configured subnet using strong cryptography, redundant sources and diverse network paths, hazards remain due to incorrect software external to NTP. These include the Unix kernel and library routines which convert NTP time to and from Unix time and to and from conventional civil time in seconds, minutes, hours, days and years. Although NTP uses these routines to format monitoring data displays, they are not used to read or set the NTP clock. They may in fact cause problems with certain application programs, but this is not an issue which concerns NTP correctness.

It is possible that some external source to which NTP synchronizes may produce a discontinuity which could then induce a NTP discontinuity. The NTP primary (stratum 1) time servers, which are the ultimate time references for the entire NTP population, obtain time from various sources, including radio and satellite receivers and telephone modems. Not all sources provide year information and not all of these provide time in four-digit form. In point of fact, the NTP reference implementation does not use the year information, even if available. Instead, the year information is provided from the file system, which itself depends on the Unix clock.

Most computers include a time-of-year (TOY) clock chip which maintains the time when the power is off. When the operating system is booted, the system clock is set from the chip. As the chip does not record the year, this value is determined from the datestamp on a system configuration file. For this to be correct, the filestamp must by updated at least once each year. The NTP protocol specification requires the apparent NTP time derived from external servers to be compared to the system time before the clock is set. If the discrepancy is over 1000 seconds, an error alarm is raised requiring manual intervention. This makes it very unlikely that even a clique of seriously corrupted NTP servers will result in grossly incorrect time values. When the system clock is synchronized to NTP, the TOY chip is corrected to system time on a regular basis.

* * *

#### Timescale Resolution and the Tick Interval

Modern computer clocks use a hardware counter to generate processor interrupts at tick intervals in the order of a few milliseconds. At each tick the processor increments the software system clock by the number of microseconds or nanoseconds in the tick. The software resolution of the system clock is defined as the tick interval. Most modern processors implement some kind of high resolution hardware counter that can be used to interpolate the interval between the most recent tick and the actual clock reading. The hardware resolution of the system clock is defined as the time between increments of this counter. However, the actual reading latency due to the kernel interface and interpolation code can range from a few tens of microseconds in older processors to under a microsecond in modern processors.

System clock correctness principles require that clock readings must be always monotonically increasing, so that no two clock readings will be the same. As long as the reading latency exceeds the hardware resolution, this behavior is guaranteed. With reading latencies dropping below the microsecond in modern processors, the system clock in modern operating systems runs in nanoseconds, rather than the microseconds used in the original Unix kernel. With processor speeds exceeding 1 GHz, this assumption may be in jeopardy.

* * *

#### Leap Seconds

The International Earth Rotation Service (IERS) uses astronomical observations provided by USNO and other observatories to determine UTC, which is syntonic (identical frequency) with TAI but offset by a integral number of seconds. Starting from apparent mean solar time as observed, the UT0 timescale is determined using corrections for Earth orbit and inclination (the Equation of Time, as used by sundials), the UT1 (navigator's) timescale by adding corrections for polar migration and the UT2 timescale by adding corrections for known periodicity variations. UTC is based on UT1, which is presently fast relative to TAI by a fraction of a second per year. Since the UTC timescale runs at the TAI rate, when the magnitude of the UT1 correction approaches 0.5 second, a leap second is inserted or deleted in the UTC timescale on the last day of June or December.

For the most precise coordination and timestamping of events since 1972, it is necessary to know when leap seconds are implemented in UTC and how the seconds are numbered. The insertion of leap seconds into UTC is currently the responsibility of the IERS, which is located at the Paris Observatory. As specified in CCIR Report 517, a leap second is inserted following second 23:59:59 on the last day of June or December and becomes second 23:59:60 of that day. A leap second would be deleted by omitting second 23:59:59 on one of these days, although this has never happened. A table of historic leap seconds and the NTP time when each occurred is available via FTP from any NIST NTP server.

The UTC timescale thus ticks in standard (atomic) seconds and was set to an initial offset of 10 seconds relative to TAI at 0h MJD 41,318.0 according to the Julian calendar or 0h on 1 January 1972 according to the Gregorian calendar. This established the first tick of the UTC era and its reckoning with these calendars. Subsequently, the UTC timescale has marched backward relative to the TAI timescale exactly one second on scheduled occasions recorded in the institutional memory of our civilization. Note in passing that leap second adjustments affect the number of seconds per day and thus the number of seconds per year. Apparently, should we choose to worry about it, the UTC clock, Gregorian calendar and various cosmic oscillators will inexorably drift apart with time until rationalized by some future papal bull.

* * *

#### Reckoning with NTP and UTC Leap seconds

The NTP timescale is based on the UTC timescale, but not necessarily always coincident with it. At the first tick of the UTC Era, which began at 0h on 1 January 1972 (MJD 41,318.0) the NTP clock read 2,272,060,800, representing the number of standard seconds since the beginning of the NTP era at 0h on 1 January 1900 (MJD 15,021.0) according to the Gregorian calendar. The insertion of leap seconds in UTC and subsequently into NTP does not affect the UTC or NTP oscillator frequency, only the conversion between NTP network time and UTC civil time. However, since the only institutional memory available to NTP are the UTC broadcast services, the NTP timescale is in effect reset to UTC as each broadcast timecode is received. Thus, when a leap second is inserted in UTC and subsequently in NTP, knowledge of all previous leap seconds is lost.

Another way to describe this is to say there are as many NTP timescales as historic leap seconds. In effect, a new timescale is established after each new leap second. Thus, all previous leap seconds, not to mention the apparent origin of the timescale itself, lurch forward one second as each new timescale is established. If a clock synchronized to NTP in early 2001 was used to establish the UTC epoch of an event that occurred in early 1972 without correction, the event would appear 22 seconds late. However, NTP primary time servers resolve the epoch using the broadcast timecode, so that the NTP clock is set to the broadcast value on the current timescale. As a result, for the most precise determination of epoch relative to the historic Gregorian calendar and UTC timescale, the user must subtract from the apparent NTP epoch the offsets derived from the NIST table. This is a feature of almost all present day time distribution mechanisms.

The obvious question raised by this scenario is what happens during the leap second when NTP time stops and the clock remains unchanged. If the precision time kernel modifications have been implemented, the kernel includes a state machine that implements the actions required by the scenario. At the exact instant of the leap, the logical clock is stepped backward one second. However, the routine that actually reads the clock is constrained never to step backwards, unless the step is significantly larger than one second, which might occur due to explicit operator direction.

In this design time stands still during the leap second, but is correct commencing with the next second. Since clock readings must be positive monotonic, the apparent time will increase by one nanosecond for each reading. At the end of the second the apparent time may be ahead of the actual time depending on how many times the clocks was read during the second. Eventually, the actual time will catch up with the apparent time and operation continues normally.