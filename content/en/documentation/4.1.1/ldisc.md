---
title: "Line Disciplines and Streams Modules"
type: archives
noindex: true 
sitemap_exclude: true
--- 

#### Table of Contents
*  [Description](/documentation/4.1.1/ldisc/#description)
*  [PPSAPI Application Program Interface](/documentation/4.1.1/ldisc/#ppsapi-application-program-interface)
*  [<tt>tty_clk</tt> Line Discipline/Streams Module](/documentation/4.1.1/ldisc/#tttty_clktt-line-disciplinestreams-module)
*  [<tt>TIOCDCDTIMESTAMP</tt> ioctl in FreeBSD](/documentation/4.1.1/ldisc/#tttiocdcdtimestamptt-ioctl-in-freebsd)
*  [<tt>ppsclock</tt> Streams Module](/documentation/4.1.1/ldisc/#ttppsclocktt-streams-module)
*  [<tt>TIOCSPPS</tt> and <tt>TIOCGETPPSEV</tt> ioctls in Solaris](/documentation/4.1.1/ldisc/#tttiocsppstt-and-tttiocgetppsevtt-ioctls-in-solaris)
*  [<tt>tty_chu</tt> Line Discipline/Streams Module (deprecated)](/documentation/4.1.1/ldisc/#tttty_chutt-line-disciplinestreams-module-deprecated)

* * *

#### Description

Most radio and modem clocks used for a primary (stratum-1) NTP server utilize serial ports operating at speeds of 9600 baud or greater. The intrinsic delay and jitter contributed by the serial port hardware and software driver can accumulate up to a millisecond in newer Unix systems and tens of milliseconds in older ones. In order to reduce the effects of delay and jitter, a set of special line disciplines, stream modules and operating system calls (ioctls) can be configured in some Unix kernels. These routines intercept special characters or signals provided by the radio or modem clock and save a timestamp for later processing.

The routines provide two important functions. Some insert a timestamp in the receive data stream upon occurrence of a designated character or characters at the serial interface. This can be used to timestamp an on-time character produced by a radio clock, for example. Other routines support an application program interface for pulse-per-second (PPS) signals generated by some radio clocks and laboratory instruments. These routines are normally accessed through the PPSAPI application program interface described below.

The routines can be compiled in the kernel in older BSD-derived systems, or installed as System V streams modules and either compiled in the kernel or dynamically loaded when required. In either case, they require minor changes in some kernel files and in the NTP daemon <code>ntpd</code>. The streams modules can be pushed and popped from the streams stack using conventional System V streams program primitives. Note that some Unix kernels do not support line disciplines and some do not support System V streams. The routines described here are known to work correctly with the Unix kernels called out in the descriptions, but have not been tested for other kernels.

* * *

#### PPSAPI Application Program Interface

Pulse-per-second (PPS) signals are normally processed as described in the [Pulse-per-second (PPS) Signal Interfacing](/documentation/4.1.1/pps/) page. The [PPS Clock Discipline](/documentation/drivers/driver22/) driver uses the PPSAPI application program interface to capture PPS signal transitions used to fine-tune the system clock. This interface, defined in RFC-2783, is the only PPS interface supported in NTP. While older PPS interfaces based on the ioctls described below continue to be supported, they are used only in the special header file <code>/usr/include/sys/timepps.h</code>, which implements the PPSAPI specific to each archeticture and operating system.

It is the intent of the evolving design to remove all PPS support from the various clock drivers and utilize only the PPS driver for PPS support. This allows the required sanity checks and signal grooming to be provided and maintained in one place and avoids cluttering up the drivers with duplicate functionality. Since the PPS signal samples are processed by the entire suite of NTP grooming, selection and clustering algorithms, noisy PPS signals and signals outside specific time and frequency tolerances are excluded.

The PPSAPI interface provides the following functions:

<code>**time_pps_create**</code>

: Creates a PPS interface instance and returns a handle to it.

<code>**time_pps_destroy**</code>

: Destroys a PPS interface and returns the resources used.

<code>**time_pps_setparams**</code>

: Sets the parameters associated with a PPS interface instance, including offsets to be automatically added to captured timestamps.

<code>**time_pps_getparams**</code>

: Returns the parameters associated with a PPS interface instance.

<code>**time_pps_getcap**</code>

: Returns the capabilities of the current interface and kernel implementation.

<code>**time_pps_fetch**</code>

: Returns the current timestamps associated with a PPS interface instance in either nanoseconds and nanoseconds (Unix <code>timespec</code>) or seconds and fraction (NTP) format.

<code>**time_pps_kcbind**</code>

: If kernel PPS processing is supported, this binds the support to the associated PPS interface instance.

The entire PPS interface functionality is currently provided by inline code in the <code>timepps.h</code> header files implemented for SunOS, Solaris, FreeBSD, Linux and Tru64. While not all implementations support the full PPSAPI specification, they do support all the functions required for the PPS driver. The FreeBSD, Linux and Solaris implementations can be used with the stock kernels provided with those systems; however, the Tru64 and SunOS kernels require additional functions not provided in the stock kernels. Solaris users are cautioned that these ioctls function improperly in Solaris versions prior to 2.8 with patch Generic_108528-02.

* * *

#### <tt>tty_clk</tt> Line Discipline/Streams Module

This routine intercepts characters received from the serial port and passes unchanged all except a set of designated characters to the generic serial port discipline. For each of the exception characters, the character is inserted in the receiver buffer followed by a local timestamp in Unix <code>timeval</code> format. Both <code>select()</code> and <code>SIGIO</code> are supported by the routine. Support for this routine is automatically detected during the NTP build process and interface code compiled as necessary.

There are two versions of the <code>tty_clk</code> routine. The <code>tty_clk.c</code> line discipline is designed for older BSD systems and is compiled in the kernel. The <code>tty_clk_STREAMS.c</code> is designed for System V streams, in which case it can be either compiled in the kernel or dynamically loaded. Since these programs are small, unobtrusive, and do nothing unless specifically enabled by an application program, it probably doesn't matter which version is chosen. Instructions on how to configure and build a kernel supporting either of these routines is in the <code>README</code> file in the <code>./kernel</code> directory.

The <code>tty_clk</code> routine defines a new ioctl <code>CLK_SETSTR</code>, which takes a pointer to a string of no more than 32 characters. Until the first <code>CLK_SETSTR</code> is performed, the routine will simply pass through characters. Once it is passed a string by <code>CLK_SETSTR</code>, any character in that string will be immediately followed by a timestamp in Unix <code>timeval</code> format. You can change the string whenever you want by doing another <code>CLK_SETSTR</code>. The character must be an exact, 8 bit match. The character `\000` cannot, be used, as it is the string terminator. Passing an empty string to <code>CLK_SETSTR</code> turns off timestamping. Passing <code>NULL</code> may produce surprising results.

* * *

#### <tt>TIOCDCDTIMESTAMP</tt> ioctl in FreeBSD

This ioctl is included in FreeBSD 2.2 and later. It causes a timestamp to be inserted in the serial port receive data stream when the data carrier detect (DCD) signal is asserted. This is useful for those radio clocks that indicate the on-time epoch by means of a modem control signal. It is not recommended that this be used for PPS timestamps, as this function is available using the PPS application program interface included in FreeBSD 3.4 and later.

The <code>TIOCDCDTIMESTAMP</code> ioctl() is detected and compiled automatically on FreeBSD systems if available. With FreeBSD 2.2 the measured delay between activation of the DCD signal and the time the timestamp is captured on a 66MHz 486DX2 is 19 <font face="Symbol">m</font>s and on a 100MHz Pentium is 6 <font face="Symbol">m</font>s.

* * *

#### <tt>ppsclock</tt> Streams Module

This routine is a streams module which causes a timestamp to be captured when the DCD signal is asserted. It is normally used in connection with a PPS signal generated by some radio clocks. However, it is normally used only by the PPSAPI interface and SunOS 4.1.3 and should be avoided in other contexts. Instructions on how to configure and build a kernel supporting either of these routines is in the <code>README</code> file in the <code>./kernel</code> directory.

The ppsclock streams module implements the <code>CIOGETEV</code> ioctl, which takes a pointer to the structure

<pre>struct ppsclockev {
     struct timeval tv;
     u_int serial;
};
</pre>

The <code>ppsclock</code> module is pushed on the streams stack of the serial port connected to the DCD line. At each positive-going edge of the PPS signal, the routine latches the current local timestamp and increments a counter. At each <code>CIOGETEV</code> ioctl call, the current values of the timestamp and counter are returned in the <code>ppsclockev</code> structure.

* * *

#### <tt>TIOCSPPS</tt> and <tt>TIOCGETPPSEV</tt> ioctls in Solaris

These ioctls are included in Solaris 2.4 and later. They implement the same function as the <code>ppsclock</code> streams module, but are implemented as integrated system calls independent of the streams facility. They are normally used in connection with a pulse-per-second (PPS) signal generated by some radio clocks. However, these ioctls are normally used only by the PPSAPI interface and should be avoided in other contexts. See the Sun documentation for the calling sequence and return values.

Users are cautioned that these ioctls function improperly in Solaris versions prior to 2.8 with patch Generic_108528-02.

* * *

#### <tt>tty_chu</tt> Line Discipline/Streams Module (deprecated)

This routine is a special purpose line discipline for receiving a special timecode broadcast by Canadian time and frequency standard station CHU. It has been removed from the distribution since its function has been replaced by the [Radio CHU Audio Demodulator/Decoder (type 7)](/documentation/drivers/driver7/) clock driver.
