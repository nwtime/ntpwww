---
title: "Kernel Model for Precision Timekeeping"
type: archives
---

![gif](/archives/pic/alice61.gif) [from _Pogo_, Walt Kelly](http://www.eecis.udel.edu/~mills/pictures.html)

Alice finds the kernel a house of cards.

Last update: 15:42 UTC Sunday, March 02, 2008

* * *

The technical report <sup>[2](#myfootnote2)</sup>, which is a revision and update of an earlier report <sup>[3](#myfootnote3)</sup>, describes an engineering model for a precision clock discipline function for a generic operating system. The model is the same hybrid phase/frequency-lock feedback loop used by <tt>ntpd</tt>, but implemented in the kernel. The code described in <sup>[2](#myfootnote2)</sup> is included in Solaris and Digital/Compaq/HP Tru64. It provides two system calls <tt>ntp_gettime()</tt> and <tt>ntp_adjtime()</tt> and can discipline the system clock with microsecond resolution. However, newer hardware and kernels with the same system calls can discipline the clock with nanosecond resolution. The new code described in <sup>[1](#myfootnote1)</sup> is in FreeBSD and is an option for Linux, SunOS and Tru64; however, of the options, only the Linux implementation, which does not include licensed code, is readily available. The software and documentation, including a simulator used to verify correct behavior, but not involving licensed code, is available from [nanokernel.tar.gz](https://www.eecis.udel.edu/~ntp/ntp_spool/software/nanokernel.tar.gz).

The kernel model also provides support for an external precision timing source, such as described in the [Pulse-per-second (PPS) Signal Interfacing](/archives/4.2.6-series/pps) page. The new system calls are used by the [PPSAPI interface](/archives/4.2.6-series/kernpps) and in turn by the [PPS Clock Discipline](/archives/drivers/driver22) driver (type 22) to provide synchronization limited in principle only by the accuracy and stability of the external timing source.

#### Footnotes

<a name="myfootnote1">1</a> Mills, D.L., and P.-H. Kamp. The nanokernel. _Proc. Precision Time and Time Interval (PTTI) Applications and Planning Meeting_ (Reston VA, November 2000). Paper: [PostScript](http://www.eecis.udel.edu/%7emills/database/papers/nano/nano2.ps) | [PDF](http://www.eecis.udel.edu/%7emills/database/papers/nano/nano2.pdf), Slides: [PostScript](http://www.eecis.udel.edu/%7emills/database/brief/nano/nano.ps) | [PDF](http://www.eecis.udel.edu/%7emills/database/brief/nano/nano.pdf) | [PowerPoint](http://www.eecis.udel.edu/%7emills/database/brief/nano/nano.ppt)

<a name="myfootnote2">2</a>  Mills, D.L. Unix kernel modifications for precision time synchronization. Electrical Engineering Department Report 94-10-1, University of Delaware, October 1994, 24 pp. Abstract: [PostScript](http://www.eecis.udel.edu/%7emills/database/reports/kern/kerna.ps) | [PDF](http://www.eecis.udel.edu/%7emills/database/reports/kern/kerna.pdf), Body: [PostScript](http://www.eecis.udel.edu/%7emills/database/reports/kern/kernb.ps) | [PDF](http://www.eecis.udel.edu/%7emills/database/reports/kern/kernb.pdf)

<a name="myfootnote3">3</a>  Mills, D.L. A kernel model for precision timekeeping. Network Working Group Report RFC-1589, University of Delaware, March 1994\. 31 pp. [ASCII](http://www.eecis.udel.edu/%7emills/database/rfc/rfc1589.txt)