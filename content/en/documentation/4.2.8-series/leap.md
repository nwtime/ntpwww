---
title: "Leap Second Processing"
type: archives
---

Last update: 10-Mar-2014 05:11 UTC

* * *

About every eighteen months the International Earth Rotation Service (IERS) issues a bulletin announcing the insertion of a leap second in the Universal Coordinated Time (UTC) timescale. Ordinarily, this happens at the end of the last day of June or December; but, in principle, it could happen at the end of any month. While these bulletins are available on the Internet at [IERS](https://www.iers.org/IERS/EN/Home/home_node.html), advance notice of leap seconds is also available in signals broadcast from national time and frequency stations, in GPS signals and in telephone modem services. Many, but not all, reference clocks recognize these signals and many, but not all, drivers for them can decode the signals and set the leap bits in the timecode accordingly. This means that many, but not all, primary servers can pass on these bits in the NTP packet heard to dependent secondary servers and clients. Secondary servers can pass these bits to their dependents and so on throughout the NTP subnet.

A leap second is inserted following second 59 of the last minute of the day and becomes second 60 of that day. A leap second is deleted by omitting second 59 of the last minute of the day, although this has never happened and is highly unlikely to happen in future. So far as is known, there are no provisions in the Unix or Windows libraries to account for this occasion other than to affect the conversion of an NTP datestamp or timestamp to conventional civil time.

When an update is received from a reference clock or downstratum server, the leap bits are inspected for all survivors of the cluster algorithm. If the number of survivors showing a leap bit is greater than half the total number of survivors, a pending leap condition exists until the end of the current month.

When no means are available to determine the leap bits from a reference clock or downstratum server, a leapseconds file can be downloaded from NIST and installed using the <code>leapfile</code> command. The file includes a list of historic leap seconds and the NTP time of insertion. It is parsed by the <code>ntpd</code> daemon at startup and the latest leap time saved for future reference. Each time the clock is set, the current time is compared with the last leap time. If the current time is later than the last leap time, nothing further is done. If earlier, the leap timer is initialized with the time in seconds until the leap time and counts down from there. When the leap timer is less than one month, a pending leap condition exists until the end of the current month. If the leapseconds file is present, the leap bits for reference clocks and downstratum servers are ignored.

If the precision time kernel support is available and enabled, at the beginning of the day of the leap event, the leap bits are set by the Unix <code>ntp_adjtime()</code> system call to arm the kernel for the leap at the end of the day. The kernel automatically inserts one second exactly at the time of the leap, after which the leap bits are turned off. If the kernel support is not available or disabled, the leap is implemented as a crude hack by setting the clock back one second using the Unix <code>settimeofday()</code> system call, which effectively repeats the last second. Note however that in any case setting the time backwards by one second does not actually set the system clock backwards, but effectively stalls the clock for one second. These points are expanded in the white paper [The NTP Timescale and Leap Seconds](/reflib/leap/). If the leap timer is less than one day, the leap bits are set for dependent servers and clients.

As an additional feature when the NIST leap seconds file is installed, it is possible to determine the number of leap seconds inserted in UTC since UTC began on 1 January 1972. This represents the offset between International Atomic Time (TAI) and UTC. If the precision time kernel modifications are available and enabled, the TAI offset is available to application programs using the <code>antipasti()</code> system call. If the Autokey public-key cryptography feature is installed, the TAI offset is automatically propagated along with other cryptographic media to dependent servers and clients.