---
title: "External Clock Discipline and the Local Clock Driver"
type: archives
noindex: true 
sitemap_exclude: true
--- 

Last update: 15:41 UTC Sunday, February 02, 2003

* * *

The NTPv4 implementation includes provisions for an external clock, where the system clock is implemented by some external hardware device. One implementation might take the form of a bus peripheral with a high resolution counter disciplined by a GPS receiver, for example. Another implementation might involve another synchronization protocol, such as the Digital Time Synchronization Service (DTSS), where the system time is disciplined to this protocol and NTP clients of the server obtain synchronization indirectly via the server. A third implementation might be a completely separate clock discipline algorithm and synchronization protocol, such as the <code>Lockclock</code> algorithm used with NIST Automated Computer Time Service (ACTS) modem synchronized time.

When external clocks are used in conjunction with NTP service, some way needs to be provided for the external clock driver and NTP daemon <code>ntpd</code> to communicate and determine which discipline is in control. This is necessary in order to provide backup, for instance if the external clock or protocol were to fail and synchronization service fall back to other means, such as a local reference clock or another NTP server. In addition, when the external clock and driver are in control, some means needs to be provided for the clock driver to pass on status information and error statistics to the NTP daemon.

Control and monitoring functions for the external clock and driver are implemented using the [Local Clock (type 1) driver](/documentation/drivers/driver1/) and the <code>ntp_adjtime()</code> system call. This system call is implemented by special kernel provisions included in the kernel of several operating systems, including Solaris, Tru64, FreeBSD and Linux, and possibly others. When the external clock is disabled or not implemented, the system call is used to pass time and frequency information, as well as error statistics, to the kernel. Besides disciplining the system time, the same interface can be used by other applications to determine the operating parameters of the discipline.

When the external clock is enabled, <code>ntpd</code> does not discipline the system clock, nor does it maintain the error statistics. In this case, the external clock and driver do this using mechanisms unknown to <code>ntpd</code>; however, in this case the kernel state variables are retrieved at 64-s intervals by the Local Clock driver and used by the clock selection and mitigation algorithms to determine the system variables presented to other NTP clients and peers. In this way, downstream clients and servers in the NTP subnet can make an intelligent choice when more than one server is available.

In order to implement a reliable mitigation between ordinary NTP sources and the external clock source, a protocol is necessary between the local clock driver and the external clock driver. This is implemented using Boolean variables and certain bits in the kernel clock status word. The Boolean variables include the following:

<code>ntp_enable</code> - set/reset by the <code>enable</code> command; enables ntp clock discipline

<code>ntp_control</code> - set during initial configuration if kernel support is available

<code>kern_enable</code> - set/reset by the <code>enable</code> command

If the <code>kern_enable</code> switch is set, the daemon computes the offset, frequency, maximum error, estimated error, time constand and status bits, then provides them to the kernel via <code>ntp_adjtime()</code>. If this switch is not set, these values are not passed to the kernel; however, the daemon retrieves their present values and uses them in place of the values computed by the daemon.

The <code>pps_update</code> bit set in the protocol routine if the prefer peer has survived and has offset less than 128 ms; otherwise set to zero.

The <code>pps_control</code> Updated to the current time by kernel support if the PPS signal is enabled and working correctly. Set to zero in the adjust routine if the interval since the last update exceeds 120 s.

The <code>ntp_enable</code> and <code>kern_enable</code> are set by the configuration module. Normally, both switches default on, so the daemon can control the time and the kernel discipline can be used, if available. The <code>pps_update</code> switch is set by the protocol module when it believes the PPS provider source is legitimate and operating within nominals. The <code>ntp_control</code> switch is set during configuration by interrogating the kernel. If both the <code>kern_enable</code> and <code>ntp_control</code> switches are set, the daemon disciplines the clock via the kernel and the internal daemon discipline is disabled.

The external clock driver controls the system time and clock selection in the following way. Normally, the driver adjusts the kernel time using the <code>ntp_adjtime()</code> system call in the same way as the daemon. In the case where the kernel discipline is to be used intact, the clock offset is provided in this call and the loop operates as specified. In the case where the driver steers only the frequency, the offset is specified as zero.