---
title: "Kernel Model for Precision Timekeeping"
type: archives
---

![gif](/documentation/pic/alice61.gif) [from _Pogo_, Walt Kelly](/reflib/pictures/)

Alice finds the kernel a house of cards.

* * *

The technical report <sup>[2](#myfootnote2)</sup>, which is a revision and update of an earlier report <sup>[3](#myfootnote3)</sup>, describes an engineering model for a precision clock discipline function for a generic operating system. The model is the same hybrid phase/frequecy-lock feedback loop used by <code>ntpd</code>, but implemented in the kernel. The code described in <sup>[2](#myfootnote2)</sup> is included in Solaris and Digital/Compaq/HP Tru64. It provides two system calls <code>ntp_gettime()</code> and <code>ntp_adjtime()</code> and can discipline the system clock with microsecond resolution. However, newer hardware and kernels with the same system calls can discipline the clock with nanosecond resolution. The new code described in <sup>[1](#myfootnote1)</sup> is in FreeBSD, Linux and Tru64. The software and documentation, including a simulator used to verify correct behavior, but not involving licensed code, is available in the [nanokernel.tar.gz](/reflib/software/nanokernel.tar.gz) distribution.

Ordinarily, the kernel clock discipline function is used with the NTP daemon, but could be used for other purposes. The [<code>ntptime</code>](/documentation/4.2.8-series/ntptime/) utility program can be used to control it manually.

The kernel model also provides support for an external precision timing source, such as described in the [Pulse-per-second (PPS) Signal Interfacing](/documentation/4.2.8-series/pps/) page. The new system calls are used by the [PPSAPI interface](/documentation/4.2.8-series/kernpps/) and in turn by the [PPS Clock Discipline](/documentation/drivers/driver22/) driver (type 22) to provide synchronization limited in principle only by the accuracy and stability of the external timing source. Typical results with the PPS signal from a GPS receiver and a modern computer are in the 3 μs range.

#### Footnotes

<a name="myfootnote1">1</a> Mills, D.L., and P.-H. Kamp. The nanokernel. _Proc. Precision Time and Time Interval (PTTI) Applications and Planning Meeting_ (Reston VA, November 2000). Paper: [PostScript](/reflib/papers/nano/nano2.ps) | [PDF](/reflib/papers/nano/nano2.pdf), Slides: [PostScript](/reflib/brief/nano/nano.ps) | [PDF](/reflib/brief/nano/nano.pdf) | [PowerPoint](/reflib/brief/nano/nano.ppt)

<a name="myfootnote2">2</a>  Mills, D.L. Unix kernel modifications for precision time synchronization. Electrical Engineering Department Report 94-10-1, University of Delaware, October 1994, 24 pp. Abstract: [PostScript](/reflib/reports/kern/kerna.ps) | [PDF](/reflib/reports/kern/kerna.pdf), Body: [PostScript](/reflib/reports/kern/kernb.ps) | [PDF](/reflib/reports/kern/kernb.pdf)

<a name="myfootnote3">3</a>  Mills, D.L. A kernel model for precision timekeeping. Network Working Group Report RFC-1589, University of Delaware, March 1994. 31 pp. [ASCII](/reflib/rfc/rfc1589.txt)