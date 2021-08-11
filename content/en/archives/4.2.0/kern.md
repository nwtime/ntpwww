---
title: "Kernel Model for Precision Timekeeping"
type: archives
---

![gif](/archives/pic/alice61.gif) [from _Pogo_, Walt Kelly](/reflib/pictures)

Alice finds the kernel a house of cards.

Last update: 20:26 UTC Monday, December 02, 2002

* * *

The technical report <sup>[2](#myfootnote2)</sup>, which is a major revision and update of RFC-1589 <sup>[3](#myfootnote3)</sup>, describes an engineering model for a precision time-of-day function for a generic operating system. The model is based on the principles of disciplined oscillators using phase-lock loops (PLL) and frequency-lock loops (FLL) often found in the engineering literature. The model uses a hybrid PLL/FLL discipline algorithm implemented in the kernel. The algorithm, which is very similar to the algorithm implemented in the NTP daemon, provides automatic time and frequency steering with update intervals from a few seconds to tens of minutes.

The hybrid PLL/FLL code described in <sup>[2](#myfootnote2)</sup> is included in Solaris and Digital/Compaq/HP Tru64. It includes two system calls <tt>ntp_gettime()</tt> and <tt>ntp_adjtime()</tt> and can discipline the system clock with microsecond resolution. However, newer hardware and kernels with the same system calls can discipline the clock with nanosecond resolution. The new code described in <sup>[1](#myfootnote1)</sup> is available for Linux, FreeBSD, SunOS and Tru64; however, only the Linux and FreeBSD implementations, which do not include licensed code, are readily available. The software and documentation, including a simulator used to verify correct behavior, but not involving licensed code, is available at [nanokernel.tar.gz](https://www.eecis.udel.edu/~ntp/ntp_spool/software/nanokernel.tar.gz).

The model also changes the way the system clock is adjusted in time and frequency relative to an external precision timing source, such as described in the [Pulse-per-second (PPS) Signal Interfacing](/archives/4.2.0/pps) page. The NTP software daemon uses the PPS to provide synchronization limited in principle only by the accuracy and stability of the external timing source.

#### Footnotes

<a name="myfootnote1">1</a> Mills, D.L., and P.-H. Kamp. The nanokernel. _Proc. Precision Time and Time Interval (PTTI) Applications and Planning Meeting_ (Reston VA, November 2000). Paper: [PostScript](http://www.eecis.udel.edu/%7emills/database/papers/nano/nano2.ps) | [PDF](http://www.eecis.udel.edu/%7emills/database/papers/nano/nano2.pdf), Slides: [PostScript](http://www.eecis.udel.edu/%7emills/database/brief/nano/nano.ps) | [PDF](http://www.eecis.udel.edu/%7emills/database/brief/nano/nano.pdf) | [PowerPoint](http://www.eecis.udel.edu/%7emills/database/brief/nano/nano.ppt)

<a name="myfootnote2">2</a>  Mills, D.L. Unix kernel modifications for precision time synchronization. Electrical Engineering Department Report 94-10-1, University of Delaware, October 1994, 24 pp. Abstract: [PostScript](http://www.eecis.udel.edu/%7emills/database/reports/kern/kerna.ps) | [PDF](http://www.eecis.udel.edu/%7emills/database/reports/kern/kerna.pdf), Body: [PostScript](http://www.eecis.udel.edu/%7emills/database/reports/kern/kernb.ps) | [PDF](http://www.eecis.udel.edu/%7emills/database/reports/kern/kernb.pdf)

<a name="myfootnote3">3</a>  Mills, D.L. A kernel model for precision timekeeping. Network Working Group Report RFC-1589, University of Delaware, March 1994. 31 pp. [ASCII](http://www.eecis.udel.edu/%7emills/database/rfc/rfc1589.txt)