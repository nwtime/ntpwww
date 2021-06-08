---
title: "Kernel Model for Precision Timekeeping"
type: archives
---

![gif](/archives/pic/alice61.gif) [from _Pogo_, Walt Kelly](http://www.eecis.udel.edu/~mills/pictures.html)

Alice finds the kernel a house of cards.

* * *

The technical report <sup>[2](#myfootnote2)</sup>, which is a major revision and update of an earlier report <sup>[3](#myfootnote3)</sup>, describes an engineering model for a precision time-of-day function for a generic operating system. The model is based on the principles of disciplined oscillators using phase-lock loops (PLL) and frequency-lock loops (FLL) often found in the engineering literature. The model uses a hybrid PLL/FLL discipline algorithm implemented in the kernel. The hybrid loop provides automatic time and frequency steering with update intervals from a few seconds to over one day.

The hybrid PLL/FLL has been implemented in the Unix kernels for several operating systems, including FreeBSD and Linux and those made by Sun Microsystems, Digital/Compaq and Hewlett Packard. The modifications are currently included in the licensed kernels for Digital Unix 4.0 (aka Tru64) and Sun Solaris 2.8. Since the modifications involve proprietary kernel interface code, they cannot be provided for other licensed kernels directly. Inquiries should be directed to the manufacturer's representatives. The software and documentation, including a simulator with code segments almost identical to the implementations, but not involving licensed code, is available at [nanokernel.tar.gz](https://www.eecis.udel.edu/~ntp/ntp_spool/software/nanokernel.tar.gz).

Recently <sup>[1](#myfootnote1)</sup>, the model has been re-implemented to support a nanosecond system clock. The <tt>/usr/include/sys/timex.h</tt> header file defines the applications programming interface (API) routines and data structures. Implementations are available for Linux, FreeBSD, SunOS and Tru64; however, only the Linux and FreeBSD implementations, which are included in recent system versions, are directly available. The software and documentation, including a simulator with code segments almost identical to the implementations, but not involving licensed code, is available at [nanokernel.tar.gz](https://www.eecis.udel.edu/~ntp/ntp_spool/software/nanokernel.tar.gz).

The model changes the way the system clock is adjusted in time and frequency, as well as provides mechanisms to discipline its time and frequency to an external precision timing source, such as described in the [Pulse-per-second (PPS) Signal Interfacing](/archives/4.1.2/pps) page. The model incorporates a generic system call interface for use with the NTP or similar time synchronization protocol. The NTP software daemons for Version 3 <tt>xntpd</tt> and Version 4 <tt>ntpd</tt> use this API to provide synchronization limited in principle only by the accuracy and stability of the external timing source. There are two new system calls defined in <tt>timex.h</tt>, <tt>ntp_gettime()</tt>, which returns a structure including the current time, estimated error and maximum error, and <tt>ntp_adjtime()</tt>, which provides a means to adjust kernel variables, including the current time and frequency offsets.

These kernel modifications are normally used in conjunction with a kernel hardware interface such as described in the [Kernel Programming Interface for Precision Time Signals](/archives/4.1.2/kernpps) page.

#### Footnotes

<a name="myfootnote1">1</a> Mills, D.L., and P.-H. Kamp. The nanokernel. _Proc. Precision Time and Time Interval (PTTI) Applications and Planning Meeting_ (Reston VA, November 2000). Paper: [PostScript](http://www.eecis.udel.edu/%7emills/database/papers/nano/nano2.ps) | [PDF](http://www.eecis.udel.edu/%7emills/database/papers/nano/nano2.pdf), Slides: [PostScript](http://www.eecis.udel.edu/%7emills/database/brief/nano/nano.ps) | [PDF](http://www.eecis.udel.edu/%7emills/database/brief/nano/nano.pdf) | [PowerPoint](http://www.eecis.udel.edu/%7emills/database/brief/nano/nano.ppt)

<a name="myfootnote2">2</a>  Mills, D.L. Unix kernel modifications for precision time synchronization. Electrical Engineering Department Report 94-10-1, University of Delaware, October 1994, 24 pp. Abstract: [PostScript](http://www.eecis.udel.edu/%7emills/database/reports/kern/kerna.ps) | [PDF](http://www.eecis.udel.edu/%7emills/database/reports/kern/kerna.pdf), Body: [PostScript](http://www.eecis.udel.edu/%7emills/database/reports/kern/kernb.ps) | [PDF](http://www.eecis.udel.edu/%7emills/database/reports/kern/kernb.pdf)

<a name="myfootnote3">3</a>  Mills, D.L. A kernel model for precision timekeeping. Network Working Group Report RFC-1589, University of Delaware, March 1994. 31 pp. [ASCII](http://www.eecis.udel.edu/%7emills/database/rfc/rfc1589.txt)