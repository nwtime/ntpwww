---
title: "Pulse-Per-Second (PPS) Signal Interfacing"
type: archives
---

![gif](/documentation/pic/alice32.gif) [from _Alice's Adventures in Wonderland_, Lewis Carroll](/reflib/pictures/)

Alice is trying to find the PPS signal connector.

Last update: 10-Mar-2014 05:17 UTC

* * *

#### Table of Contents

*   [Introduction](/documentation/4.2.8-series/pps/#introduction)
*   [Gadget Box](/documentation/4.2.8-series/pps/#gadget-box)
*   [Operating System Support](/documentation/4.2.8-series/pps/#operating-system-support)
*   [PPS Driver](/documentation/4.2.8-series/pps/#pps-driver)
*   [Using the Pulse-per-Second (PPS) Signal](/documentation/4.2.8-series/pps/#using-the-pulse-per-second-pps-signal)

* * *

#### Introduction

Most radio clocks are connected using a serial port operating at speeds of 9600 bps. The accuracy using typical timecode formats, where the on-time epoch is indicated by a designated ASCII character such as carriage-return <code><cr\></code>, is normally limited to 100 μs. Using carefully crafted averaging techniques, the NTP algorithms can whittle this down to a few tens of microseconds. However, some radios produce a pulse-per-second (PPS) signal which can be used to improve the accuracy to a few microseconds. This page describes the hardware and software necessary for NTP to use the PPS signal.

The PPS signal can be connected in either of two ways. On FreeBSD systems (with the <code>PPS_SYNC</code> and <code>pps kernel</code> options) it can be connected directly to the ACK pin of a parallel port. This is the preferred way, as it requires no additional hardware. Alternatively, it can be connected via the DCD pin of a serial port. However, the PPS signal levels are usually incompatible with the serial port interface signals. Note that NTP no longer supports connection via the RD pin of a serial port.

![gif](/documentation/pic/gadget.jpg)

**A Gadget Box built by Chuck Hanavin**


* * *

#### Gadget Box

The gadget box shown above is assembled in a 5"x3"x2" aluminum minibox containing the circuitry, serial connector and optional 12-V power connector. A complete set of schematics, PCB artwork, and drill templates can be obtained as [gadget.tar.Z](/reflib/software/gadget.tar.Z).

The gadget box includes two subcircuits. One of these converts a TTL positive edge into a fixed-width pulse at EIA levels and is for use with a timecode receiver or precision oscillator with a TTL PPS output. The other converts the timecode modulation broadcast by Canadian time/frequency standard station CHU into a 300-bps serial character stream at EIA levels and is for use with the [Radio CHU Audio Demodulator/Decoder](/documentation/drivers/driver7/) driver.

* * *

#### Operating System Support

Both the serial and parallel port connection require operating system support, which is available in a few operating systems, including FreeBSD, Linux (with PPSkit patch) and Solaris. Support on an experimental basis is available for several other systems, including SunOS and HP/Compaq/Digital Tru64. The kernel interface described on the [PPSAPI Interface for Precision Time Signals](/documentation/4.2.8-series/kernpps/) page is the only interface currently supported. Older PPS interfaces based on the <code>ppsclock</code> and <code>tty_clk</code> streams modules are no longer supported. The interface consists of the <code>timepps.h</code> header file which is specific to each system. It is included automatically when the distribution is built.

* * *

#### PPS Driver

PPS support is built into some drivers, in particular the WWVB and NMEA drivers, and may be added to other drivers in future. Alternatively, the PPS driver described on the [Type 22 PPS Clock Discipline](/documentation/drivers/driver22/) page can be used. It operates in conjunction with another source that provides seconds numbering. The selected source is designated as a prefer peer, using the <code>prefer</code> option, as described on the [Mitigation Rules and the <code>prefer</code> Keyword](/documentation/4.2.8-series/prefer/) page. The prefer peer is ordinarily the radio clock that provides the PPS signal, but in principle another radio clock or even a remote Internet server could be designated preferred.
> Note that the <code>pps</code> configuration command has been obsoleted by this driver.

* * *

#### Using the Pulse-per-Second (PPS) Signal

The PPS signal can be used in either of two ways, one using the NTP grooming and mitigation algorithms and the other using the kernel PPS signal support described in the [Kernel Model for Precision Timekeeping](/documentation/4.2.8-series/kern/) page. The presence of  kernel support is automatically detected during the NTP build process and supporting code automatically compiled. In either case, the PPS signal must be present and within nominal jitter and wander tolerances. In addition, the prefer peer must be a truechimer; that is, survive the sanity checks and intersection algorithm. Finally, the offset of the system clock relative to the prefer peer must be within ±0.5 s. The kernel maintains a watchdog timer for the PPS signal; if the signal has not been heard or is out of tolerance for more than some interval, currently two minutes, the kernel discipline is disabled and operation continues as if it were not present.

An option flag in the driver determines whether the NTP algorithms or kernel support is enabled (if available). For historical reasons, the NTP algorithms are selected by default, since performance is generally better using older, slower systems. However, performance is generally better with kernel support using newer, faster systems.