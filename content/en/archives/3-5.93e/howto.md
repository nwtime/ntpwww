---
title: "How to Write a Reference Clock Driver"
type: archives
---

#### Table of Contents

*   [Description](/archives/3-5.93e/howto/#description)
*   [Files Which Need to be Changed](/archives/3-5.93e/howto/#files-which-need-to-be-changed)
*   [Interface Routine Overview](/archives/3-5.93e/howto/#interface-routine-overview)

* * *

#### Description

Reference clock support maintains the fiction that the clock is actually an ordinary peer in the NTP tradition, but operating at a synthetic stratum of zero. The entire suite of algorithms used to filter the received data, select the best clocks or peers and combine them to produce a local clock correction are operative as with ordinary NTP peers. In this way, defective clocks can be detected and removed from the peer population. As no packets are exchanged with a reference clock, however, we replace the transmit, receive and packet procedures with separate code to simulate them. 

Radio and modem reference clocks by convention have addresses in the form <tt>127.127._t_._u_</tt>, where _t_ is the clock type and _u_ in the range 0-3 is used to distinguish multiple instances of clocks of the same type. Most clocks require a serial or parallel port or special bus peripheral. The particular device is normally specified by adding a soft link <tt>/dev/device_d_d</tt> to the particular hardware device involved, where <tt>_d_</tt> corresponds to the unit number.

The best way to understand how the clock drivers work is to study the <tt>ntp_refclock.c</tt> module and one of the drivers already implemented, such as <tt>refclock_wwvb.c</tt>. Routines <tt>refclock_transmit()</tt> and <tt>refclock_receive()</tt> maintain the peer variables in a state analogous to a network peer and pass received data on through the clock filters. Routines <tt>refclock_peer()</tt> and <tt>refclock_unpeer()</tt> are called to initialize and terminate reference clock associations, should this ever be necessary. A set of utility routines is included to open serial devices, process sample data, edit input lines to extract embedded timestamps and to perform various debugging functions.

The main interface used by these routines is the <tt>refclockproc</tt> structure, which contains for most drivers the decimal equivalents of the year, day, month, hour, second and millisecond/microsecond decoded from the ASCII timecode. Additional information includes the receive timestamp, exception report, statistics tallies, etc. In addition, there may be a driver-specific unit structure used for local control of the device. The support routines are passed a pointer to the <tt>peer</tt> structure, which is used for all peer-specific processing and contains a pointer to the <tt>refclockproc</tt> structure, which in turn contains a pointer to the unit structure, if used. A table <tt>typeunit[type][unit]</tt> contains the peer structure pointer for each configured clock type and unit.

Many drivers support the <tt>tty_clk</tt> and/or <tt>ppsclock</tt> line disciplines or streams modules described in the [Line Disciplines and Streams Modules](/archives/3-5.93e/ldisc) page. The <tt>tty_clk</tt> module reduces latency errors due to the operating system and serial port code in slower systems. The <tt>ppsclock</tt> module is an interface for the PPS signal provided by some radios. It can be connected via a level converter/pulse generator described in the [Gadget Box PPS Level Converter and CHU Modem](/archives/3-5.93e/gadget) page.

By convention, reference clock drivers are named in the form <tt>refclock__xxxx_.c</tt>, where _xxxx_ is a unique string. Each driver is assigned a unique type number, long-form driver name, short-form driver name, and device name. The existing assignments are in the [Reference Clock Drivers](/archives/3-5.93e/refclock) page and its dependencies. Drivers are conditionally compiled using a unique flag string in the <tt>CLOCKDEFS</tt> line described in the [Configuration Options](/archives/3-5.93e/config) page.

The standard clock driver interface includes a set of common support routines some of which do such things as start and stop the device, open the serial port, and establish special functions such as PPS signal support. Other routines read and write data to the device and process time values. Most drivers need only a little customizing code to, for instance, transform idiosyncratic timecode formats to standard form, poll the device as necessary, and handle exception conditions. A standard interface is available for remote debugging and monitoring programs, such as <tt>ntpq</tt> and <tt>xntpdc</tt>, as well as the <tt>filegen</tt> facility, which can be used to record device status on a continuous basis.

The interface code and this documentation have been developed over some time and required not a little hard work converting old drivers, etc. Should you find success writing a driver for a new radio or modem service, please consider contributing it to the common good. Send the driver file itself and patches for the other files to Dave Mills (mills@udel.edu).

#### Files Which Need to be Changed

A new reference clock implementation needs to supply, in addition to the driver itself, several changes to existing files.

<dt><tt>./include/ntp.h</tt></dt>

The reference clock type defines are used in many places. Each driver is assigned a unique type number. Unused numbers are clearly marked in the list. A unique <tt>REFCLK__xxxx_</tt> identification code should be recorded in the list opposite its assigned type number.

<dt><tt>./libntp/clocktypes.c</tt></dt>

The <tt>./libntp/clktype</tt> array is used by certain display functions. A unique short-form name of the driver should be entered together with its assigned identification code.

<dt><tt>./xntpd/ntp_control.c</tt></dt>

The <tt>clocktypes</tt> array is used for certain control message displays functions. It should be initialized with the reference clock class assigned to the driver, as per the NTP specification RFC-1305. See the <tt>./include/ntp_control.h</tt> header file for the assigned classes.

<dt><tt>./xntpd/refclock_conf.c</tt></dt>

This file contains a list of external structure definitions which are conditionally defined. A new set of entries should be installed similar to those already in the table. The <tt>refclock_conf</tt> array is a set of pointers to transfer vectors in the individual drivers. The external name of the transfer vector should be initialized in correspondence with the type number.

<dt><tt>./acconfig.h</tt></dt>

This is a configuration file used by the autoconfigure scheme. Add two lines in the form:

<pre>  /* Define if we have a FOO clock */
  #undef FOO
</pre>

where FOO is the define used to cause the driver to be included in the distribution.

<dt><tt>./configure.in</tt></dt>

This is a configuration file used by the autoconfigure scheme. Add lines similar to the following:

<pre>  AC_MSG_CHECKING(FOO clock_description)
  AC_ARG_ENABLE(FOO, [  --enable-FOO        clock_description],
      [ntp_ok=$enableval], [ntp_ok=$ntp_eac])
  if test "$ntp_ok" = "yes"; then
      ntp_refclock=yes
      AC_DEFINE(FOO)
  fi
  AC_MSG_RESULT($ntp_ok)
</pre>

(Note that <tt>$ntp_eac</tt> is the value from <tt>-- {dis,en}able-all-clocks</tt> for non-PARSE clocks and <tt>$ntp_eacp</tt> is the value from <tt>--{dis,en}able-parse- clocks</tt> for PARSE clocks. See the documentation on the autoconf and automake tools from the GNU distributions.)

<dt><tt>./xntpd/Makefile.am</tt></dt>

This is the makefile prototype used by the autoconfigure scheme. Add the driver file name to the entries already in the <tt>xntpd_SOURCES</tt> list.

Patches to <tt>automake-1.0</tt> are required for the autoconfigure scripts to work properly. The file <tt>automake- 1.0.patches</tt> can be used for this purpose.

<dt><tt>./xntpd/Makefile.am</tt></dt>

Do the following sequence of commands:

<pre>  automake
  autoconf
  autoheader
  configure
</pre>

or simply run <tt>make</tt>, which will do this command sequence automatically.

* * *

#### Interface Routine Overview

<dt><tt>refclock_newpeer</tt> - initialize and start a reference clock</dt>

This routine allocates and initializes the interface structure which supports a reference clock in the form of an ordinary NTP peer. A driver-specific support routine completes the initialization, if used. Default peer variables which identify the clock and establish its reference ID and stratum are set here. It returns one if success and zero if the clock address is invalid or already running, insufficient resources are available or the driver declares a bum rap.

<dt><tt>refclock_unpeer</tt> - shut down a clock</dt>

This routine is used to shut down a clock and return its resources to the system.

<dt><tt>refclock_transmit</tt> - simulate the transmit procedure</dt>

This routine implements the NTP transmit procedure for a reference clock. This provides a mechanism to call the driver at the NTP poll interval, as well as provides a reachability mechanism to detect a broken radio or other madness.

<dt><tt>refclock_sample</tt> - process a pile of samples from the clock</dt>

This routine converts the timecode in the form days, hours, minutes, seconds, milliseconds/microseconds to internal timestamp format. It then calculates the difference from the receive timestamp and assembles the samples in a shift register. It implements a recursive median filter to suppress spikes in the data, as well as determine a rough dispersion estimate. A configuration constant time adjustment <tt>fudgetime1</tt> can be added to the final offset to compensate for various systematic errors. The routine returns one if success and zero if failure due to invalid timecode data or very noisy offsets.

Note that no provision is included for the year, as provided by some (but not all) radio clocks. Ordinarily, the year is implicit in the Unix file system and hardware/software clock support, so this is ordinarily not a problem. Nevertheless, the absence of the year should be considered more a bug than a feature and may be supported in future.

<dt><tt>refclock_receive</tt> - simulate the receive and packet procedures</dt>

This routine simulates the NTP receive and packet procedures for a reference clock. This provides a mechanism in which the ordinary NTP filter, selection and combining algorithms can be used to suppress misbehaving radios and to mitigate between them when more than one is available for backup.

<dt><tt>refclock_gtlin</tt> - groom next input line and extract timestamp</dt>

This routine processes the timecode received from the clock and removes the parity bit and control characters. If a timestamp is present in the timecode, as produced by the <tt>tty_clk</tt> line discipline/streams module, it returns that as the timestamp; otherwise, it returns the buffer timestamp. The routine return code is the number of characters in the line.

<dt><tt>refclock_open</tt> - open serial port for reference clock</dt>

This routine opens a serial port for I/O and sets default options. It returns the file descriptor if success and zero if failure.

<dt><tt>refclock_ioctl</tt> - set serial port control functions</dt>

This routine attempts to hide the internal, system-specific details of serial ports. It can handle POSIX (<tt>termios</tt>), SYSV (<tt>termio</tt>) and BSD (<tt>sgtty</tt>) interfaces with varying degrees of success. The routine sets up the <tt>tty_clk, chu_clk</tt> and <tt>ppsclock</tt> streams module/line discipline, if compiled in the daemon and requested in the call. The routine returns one if success and zero if failure.

<dt><tt>refclock_control</tt> - set and/or return clock values</dt>

This routine is used mainly for debugging. It returns designated values from the interface structure that can be displayed using xntpdc and the clockstat command. It can also be used to initialize configuration variables, such as <tt>fudgetimes, fudgevalues,</tt> reference ID and stratum.

<dt><tt>refclock_buginfo</tt> - return debugging info</dt>

This routine is used mainly for debugging. It returns designated values from the interface structure that can be displayed using <tt>xntpdc</tt> and the <tt>clkbug</tt> command.