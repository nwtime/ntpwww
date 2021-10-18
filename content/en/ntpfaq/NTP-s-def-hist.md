---
title: "4.2 History"
type: "archives"
--- 

This section summarizes the history of NTP in a few words. Most material has been taken from a draft of [A Brief History of NTP Time: Confessions of an Internet Timekeeper]() by Professor David L. Mills.

* * *

The first NTP implementation started around 1980 with an accuracy of only several hundred milliseconds. That very first implementation was documented in Internet Engineering Note [IEN-173](). Later the first specification appeared in [RFC 778](), but it was still named _Internet Clock Service_. At that time clock synchronization was needed for the HELLO routing protocol. NTP was introduced in [RFC 958]() for the first time, mainly describing the packets seen on the network as well as some basic calculations involved. Early versions of NTP did not compensate any frequency error.

The first complete specification of the protocol and accompanying algorithms for NTP version 1 appeared 1988 in [RFC 1059](). That version already had symmetric operation mode as well as client-server mode.

Version 2 introducing symmetric-key authentication (using DES-CBC) was described in [RFC 1119]() only about one year later. About the same time another time sychronization protocol named _Digital Time Synchronization Service_ (DTSS) was presented by Digital Equipment Corporation. At that time the software named `xntp` was written by Dennis Fergusson at the University of Toronto. That software evolved to the software distribution that is publically available now (See [Q: 4.3.2.1.](NTP-s-def-impl.htm#Q-NTP-IMPL-UNIX)).

Combining the good ideas of DTSS with those of NTP produced a new specification for NTP version 3, namely [RFC 1305](/reflib/rfc/rfc1305/rfc1305b.pdf), in 1992. That version introduced formal correctness principles (`esterror` and `maxerror`, see also [Q: 5.2.3.1.](NTP-s-algo-kernel.htm#Q-ALGO-KERNEL-MON-VALS)) and revised algorithms. Furthermore broadcast mode was added to the protocol.

While NTP per se only deals with adjusting the operating system's clock, there was some parallel research on improving time keeping within the operating system's kernel. [RFC 1589]() (_A kernel model for precision timekeeping_) described a new implementation and interface in 1994. That implementation could keep time with a precision of up to one microsecond.

While version 3 was still the latest specification available, both, the specification and the implementation has been continuously improved (this is what `xntp3-5` actually implements). Since about 1994 work for a new version of NTP is in progress. The first new specification was [RFC 2030](), _Simple Network Time Protocol (SNTP) version 4 for IPv4, IPv6 and OSI_.

External pulses can be used to calibrate and stabilize the operating system's clock. Therefore an operating system interface (API) has been designed and documented in [RFC 2783]() (_Pulse-per-second API for Unix-like operating systems, version 1_), finally published in 1999.

The next version of NTP will provide new features regarding automatic configuration (e.g. manycast mode), reliability, Internet traffic reduction, and authentication (using public-key cryptography). A new kernel clock model can keep time with a precision of up to one nanosecond.