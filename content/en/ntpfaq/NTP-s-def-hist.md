---
title: "4.2 History"
description: "This section of the NTP FAQ summarizes the history of NTP in a few words. Most material has been taken from a draft of A Brief History of NTP Time: Confessions of an Internet Timekeeper by Professor David L. Mills."
type: "archives"
--- 

This section summarizes the history of NTP in a few words. Most material has been taken from a draft of [A Brief History of NTP Time: Confessions of an Internet Timekeeper](/reflib/memos/hist.txt) by Professor David L. Mills.

* * *

The first NTP implementation started around 1980 with an accuracy of only several hundred milliseconds. That very first implementation was documented in Internet Engineering Note [IEN-173](/reflib/rfc/ien-173.txt). Later the first specification appeared in [RFC 778](https://www.rfc-editor.org/rfc/rfc778), but it was still named _Internet Clock Service_. At that time clock synchronization was needed for the HELLO routing protocol. NTP was introduced in [RFC 958](https://www.rfc-editor.org/rfc/rfc958) for the first time, mainly describing the packets seen on the network as well as some basic calculations involved. Early versions of NTP did not compensate any frequency error.

The first complete specification of the protocol and accompanying algorithms for NTP version 1 appeared 1988 in [RFC 1059](/reflib/rfc/rfc1059.txt). That version already had symmetric operation mode as well as client-server mode.

Version 2 introducing symmetric-key authentication (using DES-CBC) was described in [RFC 1119](/reflib/rfc/rfc1119/rfc1119b.pdf) only about one year later. About the same time another time sychronization protocol named _Digital Time Synchronization Service_ (DTSS) was presented by Digital Equipment Corporation. At that time the software named `xntp` was written by Dennis Fergusson at the University of Toronto. That software evolved to the software distribution that is publically available now.

Combining the good ideas of DTSS with those of NTP produced a new specification for NTP version 3, namely [RFC 1305](/reflib/rfc/rfc1305/rfc1305b.pdf), in 1992. That version introduced formal correctness principles [`esterror` and `maxerror`](/ntpfaq/ntp-s-algo-kernel/#522-monitoring) and revised algorithms. Furthermore, broadcast mode was added to the protocol.

While NTP per se only deals with adjusting the operating system's clock, there was some parallel research on improving time keeping within the operating system's kernel. [RFC 1589 A kernel model for precision timekeeping](/reflib/rfc/rfc1589.txt) described a new implementation and interface in 1994. That implementation could keep time with a precision of up to one microsecond.

The specification and the implementation has been continuously improved. The first new specification was [RFC 2030 Simple Network Time Protocol (SNTP) version 4 for IPv4, IPv6 and OSI](/reflib/rfc/rfc2030.txt).

External pulses can be used to calibrate and stabilize the operating system's clock. Therefore an operating system interface (API) has been designed and documented in [RFC 2783 Pulse-per-second API for Unix-like operating systems, version 1](/reflib/rfc/rfc2783.txt), published in 1999.

NTPv4, defined in [RFC 5909](/reflib/rfc/rfc5905.txt) provides features regarding automatic configuration (manycast mode), reliability, Internet traffic reduction, and authentication using public-key cryptography. Its kernel clock model can keep time with a precision of up to one nanosecond.