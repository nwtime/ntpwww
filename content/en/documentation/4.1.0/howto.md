---
title: "How to Write a Reference Clock Driver"
type: archives
noindex: true
---

![gif](/documentation/pic/pogo4.gif)[from _Pogo_, Walt Kelly](/reflib/pictures/)

You need a little magic.

* * *

#### Table of Contents

*   [Description](/documentation/4.1.0/howto/#description)
*   [Conventions, Fudge Factors and Flags](/documentation/4.1.0/howto/#conventions-fudge-factors-and-flags)
*   [Files Which Need to be Changed](/documentation/4.1.0/howto/#files-which-need-to-be-changed)
*   [Interface Routine Overview](/documentation/4.1.0/howto/#interface-routine-overview)

* * *

#### Description

Reference clock support maintains the fiction that the clock is actually an ordinary peer in the NTP tradition, but operating at a synthetic stratum of zero. The entire suite of algorithms used to filter the received data, select the best clocks or peers and combine them to produce a local clock correction operate just like ordinary NTP peers. In this way, defective clocks can be detected and removed from the peer population. As no packets are exchanged with a reference clock; however, the transmit, receive and packet procedures are replaced with separate code to simulate them. 

Radio and modem reference clocks by convention have addresses in the form <code>127.127._t_._u_</code>, where <code>_t_</code> is the clock type and <code>_u_</code> in the range 0-3 is used to distinguish multiple instances of clocks of the same type. Most clocks require a serial or parallel port or special bus peripheral. The particular device is normally specified by adding a soft link <code>/dev/device\__d_</code> to the particular hardware device involved, where <code>_d_</code> corresponds to the unit number.

The best way to understand how the clock drivers work is to study the <code>ntp_refclock.c</code> module and one of the drivers already implemented, such as <code>refclock_wwvb.c</code>. Routines <code>refclock_transmit()</code> and <code>refclock_receive()</code> maintain the peer variables in a state analogous to a network peer and pass received data on through the clock filters. Routines <code>refclock_peer()</code> and <code>refclock_unpeer()</code> are called to initialize and terminate reference clock associations, should this ever be necessary. A set of utility routines is included to open serial devices, process sample data, edit input lines to extract embedded timestamps and to perform various debugging functions.

The main interface used by these routines is the <code>refclockproc</code> structure, which contains for most drivers the decimal equivalents of the year, day, month, hour, second and millisecond/microsecond decoded from the ASCII timecode. Additional information includes the receive timestamp, exception report, statistics tallies, etc. The support routines are passed a pointer to the <code>peer</code> structure, which is used for all peer-specific processing and contains a pointer to the <code>refclockproc</code> structure, which in turn contains a pointer to the unit structure, if used. For legacy purposes, a table <code>typeunit[type][unit]</code> contains the peer structure pointer for each configured clock type and unit.

The reference clock interface supports auxiliary functions to support in-stream timestamping, pulse-per-second (PPS) interfacing and precision time kernel support. In most cases the drivers do not need to be aware of them, since they are detected at autoconfigure time and loaded automatically when the device is opened. These include the <code>tty_clk</code> and <code>ppsclock</code> STREAMS modules and <code>ppsapi</code> PPS interface described in the [Line Disciplines and Streams Modules](/documentation/4.1.0/ldisc/) page. The <code>tty_clk</code> module reduces latency errors due to the operating system and serial port code in slower systems. The <code>ppsclock</code> module is an interface for the PPS signal provided by some radios. The <code>ppsapi</code> PPS interface replaces the <code>ppsclock</code> STREAMS module and is expected to become the IETF standard cross-platform interface for PPS signals. In either case, the PPS signal can be connected via a level converter/pulse generator described in the [Gadget Box PPS Level Converter and CHU Modem](/documentation/4.1.0/gadget/) page.

By convention, reference clock drivers are named in the form <code>refclock\__xxxx_.c</code>, where <code>_xxxx_</code> is a unique string. Each driver is assigned a unique type number, long-form driver name, short-form driver name, and device name. The existing assignments are in the [Reference Clock Drivers](/documentation/4.1.0/refclock/) page and its dependencies. All drivers supported by the particular hardware and operating system are automatically detected in the autoconfigure phase and conditionally compiled. They are configured when the daemon is started according to the configuration file, as described in the [Configuration Options](/documentation/4.1.0/config/) page.

The standard clock driver interface includes a set of common support routines some of which do such things as start and stop the device, open the serial port, and establish special functions such as PPS signal support. Other routines read and write data to the device and process time values. Most drivers need only a little customizing code to, for instance, transform idiosyncratic timecode formats to standard form, poll the device as necessary, and handle exception conditions. A standard interface is available for remote debugging and monitoring programs, such as <code>ntpq</code> and <code>ntpdc</code>, as well as the <code>filegen</code> facility, which can be used to record device status on a continuous basis.

The general organization of a typical clock driver includes a receive-interrupt routine to read a timecode from the I/O buffer and convert to internal format, generally in days, hours, minutes, seconds and fraction. Some timecode formats include provisions for leap-second warning and determine the clock hardware and software health. The interrupt routine then calls <code>refclock_process()</code> with these data and the timestamp captured at the on-time character of the timecode. This routine saves each sample as received in a circular buffer, which can store from a few up to 60 samples, in cases where the timecodes arrive one per second.

The <code>refclock_transmit()</code> routine in the interface is called by the system at intervals defined by the poll interval in the peer structure, generally 64 s. This routine in turn calls the transmit poll routine in the driver. In the intended design, the driver calls the <code>refclock_receive()</code> to process the offset samples that have accumulated since the last poll and produce the final offset and variance. The samples are processed by recursively discarding median outlyers until about 60 percent of samples remain, then averaging the surviving samples. When a reference clock must be explicitly polled to produce a timecode, the driver can reset the poll interval so that the poll routine is called a specified number of times at 1-s intervals.

The interface code and this documentation have been developed over some time and required not a little hard work converting old drivers, etc. Should you find success writing a driver for a new radio or modem service, please consider contributing it to the common good. Send the driver file itself and patches for the other files to Dave Mills (mills@udel.edu).

#### Conventions, Fudge Factors and Flags

Most drivers support manual or automatic calibration for systematic offset bias using values encoded in the <code>fudge</code> configuration command. By convention, the <code>time1</code> value defines the calibration offset in seconds. For those drivers that support statistics collection using the <code>filegen</code> utility and the <code>clockstats</code> file, the <code>flag4</code> switch enables the utility. When a PPS signal is available, a special automatic calibration facility is provided. If the <code>flag1</code> switch is set and the PPS signal is actively disciplining the system time, the calibration value is automatically adjusted to maintain a residual offset of zero. Should the PPS signal or the prefer peer fail, the adjustment is frozen and the remaining drivers continue to discipline the system clock with a minimum of residual error.

#### Files Which Need to be Changed

A new reference clock implementation needs to supply, in addition to the driver itself, several changes to existing files.

<code>**./include/ntp.h**</code>

: The reference clock type defines are used in many places. Each driver is assigned a unique type number. Unused numbers are clearly marked in the list. A unique <code>REFCLK\__xxxx_</code> identification code should be recorded in the list opposite its assigned type number.

<code>**./libntp/clocktypes.c**</code>

: The <code>./libntp/clktype</code> array is used by certain display functions. A unique short-form name of the driver should be entered together with its assigned identification code.

<code>**./ntpd/ntp_control.c**</code>

: The <code>clocktypes</code> array is used for certain control message displays functions. It should be initialized with the reference clock class assigned to the driver, as per the NTP specification RFC-1305. See the <code>./include/ntp_control.h</code> header file for the assigned classes.

<code>**./ntpd/refclock_conf.c**</code>

: This file contains a list of external structure definitions which are conditionally defined. A new set of entries should be installed similar to those already in the table. The <code>refclock_conf</code> array is a set of pointers to transfer vectors in the individual drivers. The external name of the transfer vector should be initialized in correspondence with the type number.

<code>**./acconfig.h**</code>

: This is a configuration file used by the autoconfigure scheme. Add two lines in the form:

<pre>  /* Define if we have a FOO clock */
  #undef FOO
</pre>

where <code>FOO</code> is the define used to cause the driver to be included in the distribution.

<code>**./configure.in**</code>

: This is a configuration file used by the autoconfigure scheme. Add lines similar to the following:

<pre>  AC_MSG_CHECKING(FOO clock_description)
  AC_ARG_ENABLE(FOO, [  --enable-FOO        clock_description],
      [ntp_ok=$enableval], [ntp_ok=$ntp_eac])
  if test "$ntp_ok" = "yes"; then
      ntp_refclock=yes
      AC_DEFINE(FOO)
  fi
  AC_MSG_RESULT($ntp_ok)
</pre>

(Note that <code>$ntp_eac</code> is the value from <code>-\-{dis,en}able-all-clocks</code> for non-PARSE clocks and <code>$ntp_eacp</code> is the value from <code>-\-{dis,en}able-parse- clocks</code> for PARSE clocks. See the documentation on the autoconf and automake tools from the GNU distributions.)

<code>**./ntpd/Makefile.am**</code>

: This is the makefile prototype used by the autoconfigure scheme. Add the driver file name to the entries already in the <code>ntpd_SOURCES</code> list.

Patches to <code>automake-1.0</code> are required for the autoconfigure scripts to work properly. The file <code>automake- 1.0.patches</code> can be used for this purpose.

<code>**./ntpd/Makefile.am**</code>

Do the following sequence of commands:

<pre>  automake
  autoconf
  autoheader
  configure
</pre>

or simply run <code>make</code>, which will do this command sequence automatically.

* * *

#### Interface Routine Overview

<code>**refclock_newpeer</code> - initialize and start a reference clock**

: This routine allocates and initializes the interface structure which supports a reference clock in the form of an ordinary NTP peer. A driver-specific support routine completes the initialization, if used. Default peer variables which identify the clock and establish its reference ID and stratum are set here. It returns one if success and zero if the clock address is invalid or already running, insufficient resources are available or the driver declares a bum rap.

<code>**refclock_unpeer</code> - shut down a clock**

: This routine is used to shut down a clock and return its resources to the system.

<code>**refclock_transmit</code> - simulate the transmit procedure**

: This routine implements the NTP transmit procedure for a reference clock. This provides a mechanism to call the driver at the NTP poll interval, as well as provides a reachability mechanism to detect a broken radio or other madness.

<code>**refclock_sample</code> - process a pile of samples from the clock**

: This routine converts the timecode in the form days, hours, minutes, seconds, milliseconds/microseconds to internal timestamp format. It then calculates the difference from the receive timestamp and assembles the samples in a shift register. It implements a recursive median filter to suppress spikes in the data, as well as determine a rough dispersion estimate. A configuration constant time adjustment <code>fudgetime1</code> can be added to the final offset to compensate for various systematic errors. The routine returns one if success and zero if failure due to invalid timecode data or very noisy offsets.

Note that no provision is included for the year, as provided by some (but not all) radio clocks. Ordinarily, the year is implicit in the Unix file system and hardware/software clock support, so this is ordinarily not a problem. Nevertheless, the absence of the year should be considered more a bug than a feature and may be supported in future.

<code>**refclock_receive</code> - simulate the receive and packet procedures**

: This routine simulates the NTP receive and packet procedures for a reference clock. This provides a mechanism in which the ordinary NTP filter, selection and combining algorithms can be used to suppress misbehaving radios and to mitigate between them when more than one is available for backup.

<code>**refclock_gtlin</code> - groom next input line and extract timestamp**

: This routine processes the timecode received from the clock and removes the parity bit and control characters. If a timestamp is present in the timecode, as produced by the <code>tty_clk</code> line discipline/streams module, it returns that as the timestamp; otherwise, it returns the buffer timestamp. The routine return code is the number of characters in the line.

<code>**refclock_open</code> - open serial port for reference clock**

: This routine opens a serial port for I/O and sets default options. It returns the file descriptor if success and zero if failure.

<code>**refclock_ioctl</code> - set serial port control functions**

: This routine attempts to hide the internal, system-specific details of serial ports. It can handle POSIX (<code>termios</code>), SYSV (<code>termio</code>) and BSD (<code>sgtty</code>) interfaces with varying degrees of success. The routine sets up the <code>tty_clk, chu_clk</code>, and <code>ppsclock</code> streams module/line discipline, if compiled in the daemon and requested in the call. The routine returns one if success and zero if failure.

<code>**refclock_control</code> - set and/or return clock values**

: This routine is used mainly for debugging. It returns designated values from the interface structure that can be displayed using ntpdc and the clockstat command. It can also be used to initialize configuration variables, such as <code>fudgetimes, fudgevalues, reference ID</code> and <code>stratum</code>.

<code>**refclock_buginfo</code> - return debugging info**

: This routine is used mainly for debugging. It returns designated values from the interface structure that can be displayed using <code>ntpdc</code> and the <code>clkbug</code> command.

* * *

![gif](/documentation/pic/pogo1a.gif)