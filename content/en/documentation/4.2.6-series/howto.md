---
title: "How to Write a Reference Clock Driver"
type: archives
noindex: true 
sitemap_exclude: true
---

![gif](/documentation/pic/pogo4.gif)[from _Pogo_, Walt Kelly](/reflib/pictures/)

You need a little magic.

* * *

#### Table of Contents

*   [Description](/documentation/4.2.6-series/howto/#description)
*   [Conventions, Fudge Factors and Flags](/documentation/4.2.6-series/howto/#conventions-fudge-factors-and-flags)
*   [Files Which Need to be Changed](/documentation/4.2.6-series/howto/#files-which-need-to-be-changed)
*   [Interface Routine Overview](/documentation/4.2.6-series/howto/#interface-routine-overview)
*   [Pulse-per-Second Interface](/documentation/4.2.6-series/howto/#pulse-per-second-interface)

* * *

#### Description

NTP reference clock support maintains the fiction that the clock is actually an ordinary server in the NTP tradition, but operating at a synthetic stratum of zero. The entire suite of algorithms filter the received data and select the best sources to correct the system clock. No packets are exchanged with a reference clock; however, the transmit, receive and packet procedures are replaced with code to simulate them.

The driver assumes three timescales: standard time maintained by a distant laboratory such as USNO or NIST, reference time maintained by the external radio and the system time maintained by NTP. The radio synchronizes reference time via radio, satellite or modem. As the transmission means may not always be reliable, most radios continue to provide clock updates for some time after signal loss using an internal reference oscillator. In such cases the radio may or may not reveal the time since last synchronized or the estimated time error.

All three timescales run only in Coordinated Universal Time (UTC) and are not adjusted for local timezone or standard/daylight time. The local timezone, standard/daylight indicator and year, if provided, are ignored. However, it is important to determine whether a leap second is to be inserted in the UTC timescale in the near future so NTP can insert it in the system timescale at the appropriate epoch.

The interface routines in the <code>ntp_refclock.c</code> source file call the following driver routines via a transfer vector:

<code>**startup**</code>

: The association has just been mobilized. The driver may allocate a private structure and open the device(s) required.

<code>**shutdown**</code>

: The association is about to be demobilized. The driver should close all device(s) and free private structures.

<code>**receive**</code>

: A timecode string is ready for retrieval using the <code>refclock_gtlin()</code> or <code>refclock_gtraw()</code> routines and provide clock updates.

<code>**poll**</code>

: Called at poll timeout, by default 64 s. Ordinarily, the driver will send a poll sequence to the radio as required.

<code>**timer**</code>

: Called once per second. This can be used for housekeeping functions. In the case with pulse-per-second (PPS) signals, this can be used to process the signals and provide clock updates.

The receive routine retrieves a timecode string via serial or parallel port, PPS signal or other means. It decodes the timecode in days, hours, minutes, seconds and nanoseconds and checks for errors. It provides these data along with the on-time timestamp to the <code>refclock_process</code> routine, which saves the computed offset in a 60-sample circular buffer. On occasion, either by timeout, sample count or call to the poll routine, the driver calls <code>refclock_receive</code> to process the circular buffer samples and update the system clock.

The best way to understand how the clock drivers work is to study one of the drivers already implemented, such as <code>refclock_wwvb.c</code>. The main interface is the <code>refclockproc</code> structure, which contains for most drivers the decoded timecode, on-time timestamp, reference timestamp, exception reports and statistics tallies, etc. The support routines are passed a pointer to the <code>peer</code> structure, which contains a pointer to the <code>refclockproc</code> structure, which in turn contains a pointer to the unit structure, if used. For legacy purposes, a table <code>typeunit[type][unit]</code> contains the peer structure pointer for each configured clock type and unit. This structure should not be used for new implementations.

Radio and modem reference clocks by convention have addresses of the form <code>127.127._t_._u_</code>, where _t_ is the clock type and _u_ in the range 0-3 is used to distinguish multiple instances of clocks of the same type. Most clocks require a serial or parallel port or special bus peripheral. The particular device is normally specified by adding a soft link <code>/dev/device_u_</code> to the particular hardware device.

By convention, reference clock drivers are named in the form <code>refclock__xxxx_.c</code>, where <code>_xxxx_</code> is a unique string. Each driver is assigned a unique type number, long-form driver name, short-form driver name and device name. The existing assignments are in the [Reference Clock Drivers](/documentation/4.2.6-series/refclock/) page and its dependencies. All drivers supported by the particular hardware and operating system are automatically detected in the autoconfigure phase and conditionally compiled.

* * *

#### Conventions, Fudge Factors and Flags

Most drivers support manual or automatic calibration for systematic offset bias using values encoded in the <code>fudge</code> configuration command. By convention, the <code>time1</code> value defines the calibration offset in seconds. For those drivers that support statistics collection using the <code>filegen</code> utility and the <code>clockstats</code> file, the <code>flag4</code> switch enables the utility.

If the calibration feature has been enabled, the <code>flag1</code> switch is set and the PPS signal is actively disciplining the system time, the <code>time1</code> value is automatically adjusted to maintain a residual offset of zero. Once its value has stabilized, the value can be inserted in the configuration file and the calibration feature disabled.

* * *

#### Files Which Need to be Changed

When a new reference clock driver is installed, the following files need to be edited. Note that changes are also necessary to properly integrate the driver in the configuration and makefile scripts, but these are decidedly beyond the scope of this page.

<code>**./include/ntp.h**</code>

: The reference clock type defines are used in many places. Each driver is assigned a unique type number. Unused numbers are clearly marked in the list. A unique <code>REFCLK__xxxx_</code> identification code should be recorded in the list opposite its assigned type number.

<code>**./libntp/clocktypes.c**</code>

: The <code>./libntp/clktype</code> array is used by certain display functions. A unique short-form name of the driver should be entered together with its assigned identification code.

<code>**./ntpd/ntp_control.c**</code>

: The <code>clocktypes</code> array is used for certain control message displays functions. It should be initialized with the reference clock class assigned to the driver, as per the NTP specification RFC-1305. See the <code>./include/ntp_control.h</code> header file for the assigned classes.

<code>**./ntpd/refclock_conf.c**</code>

: This file contains a list of external structure definitions which are conditionally defined. A new set of entries should be installed similar to those already in the table. The <code>refclock_conf</code> array is a set of pointers to transfer vectors in the individual drivers. The external name of the transfer vector should be initialized in correspondence with the type number.

* * *

#### Interface Routine Overview

<code>**refclock_newpeer</code> - initialize and start a reference clock.**

: This routine allocates and initializes the interface structure which supports a reference clock in the form of an ordinary NTP peer. A driver-specific support routine completes the initialization, if used. Default peer variables which identify the clock and establish its reference ID and stratum are set here. It returns one if success and zero if the clock address is invalid or already running, insufficient resources are available or the driver declares a bum rap.

<code>**refclock_unpeer</code> - shut down a clock**

: This routine is used to shut down a clock and return its resources to the system.

<code>**refclock_transmit</code> - simulate the transmit procedure**

: This routine implements the NTP transmit procedure for a reference clock. This provides a mechanism to call the driver at the NTP poll interval, as well as provides a reachability mechanism to detect a broken radio or other madness.

<code>**refclock_process</code> - insert a sample in the circular buffer**

: This routine saves the offset computed from the on-time timestamp and the days, hours, minutes, seconds and nanoseconds in the circular buffer. Note that no provision is included for the year, as provided by some (but not all) radio clocks. Ordinarily, the year is implicit in the Unix file system and hardware/software clock support, so this is ordinarily not a problem.

<code>**refclock_receive</code> - simulate the receive and packet procedures**

: This routine simulates the NTP receive and packet procedures for a reference clock. This provides a mechanism in which the ordinary NTP filter, selection and combining algorithms can be used to suppress misbehaving radios and to mitigate between them when more than one is available for backup.

<code>**refclock_gtraw, refclock_gtlin</code> - read the buffer and on-time timestamp**

: These routines return the data received from the clock and the on-time timestamp. The <code>refclock_gtraw</code> routine returns a batch of one or more characters returned by the Unix terminal routines in raw mode. The <code>refclock_gtlin</code> routine removes the parity bit and control characters and returns all the characters up to and including the line terminator. Either routine returns the number of characters delivered.

<code>**refclock_open</code> - open a serial port for reference clock**

: This routine opens a serial port for I/O and sets default options. It returns the file descriptor if success and zero if failure.

<code>**refclock_ioctl</code> - set serial port control functions**

: This routine attempts to hide the internal, system-specific details of serial ports. It can handle POSIX (<code>termios</code>), SYSV (<code>termio</code>) and BSD (<code>sgtty</code>) interfaces with varying degrees of success. The routine returns one if success and zero if failure.

<code>**refclock_ppsapi**</code>

: This routine initializes the Pulse-per-Second interface (see below).

<code>**refclock_pps**</code>

: This routine is called once per second to read the latest PPS offset and save it in the circular buffer (see below).

* * *

#### Pulse-per-Second Interface

When the Pulse-per-Second Application Interface (RFC 2783) is present, a compact PPS interface is available to all drivers. See the [Mitigation Rules and the Prefer Peer](/documentation/4.2.6-series/prefer/) page for further information. To use this interface, include the <code>timeppps.h</code> and <code>refclock_atom.h</code> header files and define the <code>refclock_atom</code> structure in the driver private storage. The <code>timepps.h</code> file is specific to each operating system and may not be available for some systems.

To use the interface, call <code>refclock_ppsapi</code> from the startup routine passing the device file descriptor and <code>refclock_atom</code> structure pointer. Then, call <code>refclock_pps</code> from the timer routine passing the association pointer and <code>refclock_atom</code> structure pointer. See the <code>refclock_atom.c</code> file for examples and calling sequences. If the PPS signal is valid, the offset sample will be saved in the circular buffer and a bit set in the association flags word indicating the sample is valid and the driver an be selected as a PPS peer. If this bit is set when the poll routine is called, the driver calls the <code>refclock_receive</code> routine to process the samples in the circular buffer and update the system clock.

* * *

![gif](/documentation/pic/pogo1a.gif)