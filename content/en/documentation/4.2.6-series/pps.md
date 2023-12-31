---
title: "Pulse-Per-Second (PPS) Signal Interfacing"
type: archives
noindex: true 
sitemap_exclude: true
---

![gif](/documentation/pic/alice32.gif) [from _Alice's Adventures in Wonderland_, Lewis Carroll](/reflib/pictures/)

Alice is trying to find the PPS signal connector.

* * *

#### Table of Contents

*   [Introduction](/documentation/4.2.6-series/pps/#introduction)
*   [Gadget Box](/documentation/4.2.6-series/pps/#gadget-box)
*   [Operating System Support](/documentation/4.2.6-series/pps/#operating-system-support)
*   [PPS Driver](/documentation/4.2.6-series/pps/#pps-driver)
*   [Using the Pulse-per-Second (PPS) Signal](/documentation/4.2.6-series/pps/#using-the-pulse-per-second-pps-signal)

* * *

#### Introduction

Most radio clocks are connected using a serial port operating at speeds of 9600 bps. The accuracy using typical timecode formats, where the on-time epoch is indicated by a designated ASCII character like carriage-return <code>\<cr></code>, is normally limited to 100 microseconds. Using carefuly crafted averaging techniques, the NTP algorithms can whittle this down to a few tens of microseconds. However, some radios produce a PPS signal which can be used to improve the accuracy to few microseconds. This page describes the hardware and software necessar for NTP to use the PPS signal.

![webp](/documentation/pic/gadget.webp)

A Gadget Box built by Chuck Hanavin


* * *

#### Gadget Box

The PPS signal can be connected in either of two ways: via the DCD data carrier detect pin of a serial port or via the ACK acknowledge pin of a parallel port, depending on the hardware and operating system. Note that NTP no longer supports connection via the RD data pin of a serial port.

However, the PPS signal levels are usually incompatible with serial port levels. The gadget box consists of a handful of electronic components assembled in a small aluminum box. It includes level converters and a optional modem designed to decode the radio timecode signals transmitted by Canadian time and frequency station CHU. This can be used with the [Radio CHU Audio Demodulator/Decoder](/documentation/drivers/driver7/) driver. A complete set of schematics, PCB artwork and drill templates can be obrtained via the web at [gadget.tar.Z](/reflib/software/gadget.tar.Z).

* * *

#### Operating System Support

Both the serial and parallel port connection require operating system support, which is available in only a few operating systems, including FreeBSD, Linux (with PPSkit patch) and Solaris. Support on an experimental basis is available for several other systems, including SunOS and HP/Compaq/Digital Tru64. The kernel interface described on the [PPSAPI Interface for Precision Time Signals](/documentation/4.2.6-series/kernpps/) page is the only interface currently supported. Older PPS interfaces based on the <code>ppsclock</code> and <code>tty_clk</code> streams modules are no longer supported. 

* * *

#### PPS Driver

PPS support requires the PPS driver (described on the [Type 22 PPS Clock Discipline](/documentation/drivers/driver22/) page. The driver operates in conjunction with a prefer peer, as described in the [Mitigation Rules and the <code>prefer</code> Keyword](/documentation/4.2.6-series/prefer/) page. The prefer peer is ordinarily the radio clock that provides the PPS signal, but in principle another radio clock or remote Internet server could be designated. A source is designated prefer using the <code>prefer</code> keyword, as described on the [Mitigation Rules and the <code>prefer</code> Keyword](/documentation/4.2.6-series/prefer/) page. Only one source can be designated preferred. PPS signals are processed by the PPS driver and other clock drivers which might be involved need not know or care about PPS capability. Note that the <code>pps</code> configuration command has been obsoleted by this driver.

* * *

#### Using the Pulse-per-Second (PPS) Signal

The PPS signal can be used in two ways, one using the NTP grooming and mitigations algorithms and the other using PPS signal support in the kernel, as described in the [Kernel Model for Precision Timekeeping](/documentation/4.2.6-series/kern/) page. In either case, the PPS signal must be present and within nominal jitter and wander tolerances. In addition, the PPS driver and prefer peer must survive the sanity checks and intersection algorithms. Finally, the offset of the system clock relative to the prefer peer must be less than 128 ms, or well within the 0.5-s unambiguous range. The PPS peer remains active as long as these conditions are met.

The presence of PPS kernel support is automatically detected during the NTP configuration process and supporting code automatically compiled. When kernel PPS support is enabled, the PPS driver can direct the signal directly to the kernel. Note that the PPS driver does not normally enable the PPS kernel, since performance is generally better with older systems. However, the kernel can be enabled by a driver fudge flag if necessary. This is advised for newer machines in the Pentium class.

The kernel maintains a watchdog timer for the PPS signal; if the signal has not been heard or is out of tolerance for more than some interval, currently two minutes, the kernel discipline is disabled and operation continues as if it were not present. 
