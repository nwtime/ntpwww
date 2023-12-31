---
title: "Kernel Model for Precision Timekeeping"
type: archives
noindex: true 
sitemap_exclude: true
---

![gif](/documentation/pic/alice61.gif) [from _Pogo_, Walt Kelly](/reflib/pictures/)

Alice finds the kernel a house of cards.

* * *

The technical report <sup>[2](#myfootnote2)</sup>, which is a revision and update of an earlier report <sup>[3](#myfootnote3)</sup>, describes an engineering model for a precision clock discipline function for a generic operating system. The model is the same hybrid phase/frequency-lock feedback loop used by <code>ntpd</code>, but implemented in the kernel. The code described in <sup>[2](#myfootnote2)</sup> is included in Solaris and Digital/Compaq/HP Tru64. It provides two system calls <code>ntp_gettime()</code> and <code>ntp_adjtime()</code> and can discipline the system clock with microsecond resolution. However, newer hardware and kernels with the same system calls can discipline the clock with nanosecond resolution. The new code described in <sup>[1](#myfootnote1)</sup> is in FreeBSD and is an option for Linux, SunOS and Tru64; however, of the options, only the Linux implementation, which does not include licensed code, is readily available. The software and documentation, including a simulator used to verify correct behavior, but not involving licensed code, is available from [nanokernel.tar.gz](/reflib/software/nanokernel.tar.gz).

The kernel model also provides support for an external precision timing source, such as described in the [Pulse-per-second (PPS) Signal Interfacing](/documentation/4.2.6-series/pps/) page. The new system calls are used by the [PPSAPI interface](/documentation/4.2.6-series/kernpps/) and in turn by the [PPS Clock Discipline](/documentation/drivers/driver22/) driver (type 22) to provide synchronization limited in principle only by the accuracy and stability of the external timing source.

#### Footnotes

<a name="myfootnote1">1</a> Mills, D.L., and P.-H. Kamp. The nanokernel. _Proc. Precision Time and Time Interval (PTTI) Applications and Planning Meeting_ (Reston VA, November 2000). Paper: [PDF](/reflib/papers/nano/nano2.pdf), Slides: [PDF](/reflib/brief/nano/nano.pdf)

<a name="myfootnote2">2</a>  Mills, D.L. Unix kernel modifications for precision time synchronization. Electrical Engineering Department Report 94-10-1, University of Delaware, October 1994, 24 pp. Abstract: [PDF](/reflib/reports/kern/kerna.pdf), Body: [PDF](/reflib/reports/kern/kernb.pdf)

<a name="myfootnote3">3</a>  Mills, D.L. A kernel model for precision timekeeping. Network Working Group Report RFC-1589, University of Delaware, March 1994. 31 pp. [ASCII](/reflib/rfc/rfc1589.txt)