---
title: "A Kernel Model for Precision Timekeeping"
type: archives
---

The technical memorandum: <cite>A Kernel Model for Precision Timekeeping</cite> [(PDF)](/reflib/memos/memo96b.pdf) describes an engineering model which implements a precision time-of-day function for a generic operating system. The model is based on the principles of disciplined oscillators using phase-lock loops (PLL) and frequency-lock loops (FLL) often found in the engineering literature. The model implements a hybrid PLL/FLL discipline algorithm implemented in the kernel. The hybrid loop provides automatic time and frequency steering with update intervals from a few seconds to several hours.

The hybrid PLL/FLL has been implemented in the Unix kernels for several workstations, including those made by Sun Microsystems, Digital and Hewlett Packard. The model changes the way the system clock is adjusted in time and frequency, as well as provides mechanisms to discipline its time and frequency to an external precision timing source, such as a pulse-per-second (PPS) signal. The model incorporates a generic system-call interface for use with the Network Time Protocol (NTP) or similar time synchronization protocol. The NTP Version 3 daemon <tt>xntpd</tt> operates with this model to provide synchronization limited in principle only by the accuracy and stability of the external timing source. 

This memorandum does not propose a standard protocol, specification or algorithm. It is intended to provoke comment, refinement and implementations for kernels not considered herein. While a working knowledge of NTP is not required for an understanding of the design principles or implementation of the model, it may be helpful in understanding how the model behaves in a fully functional timekeeping system. 

The model has been implemented in the Unix kernels for Sun Microsystems, Digital and Hewlett Packard workstations. In addition, for the Digital machines the model provides improved precision to one microsecond. Since these specific implementations involve modifications to licensed code, they cannot be provided directly. Inquiries should be directed to the manufacturer's representatives. However, the engineering model for these implementations, including a simulator with code segments almost identical to the implementations, but not involving licensed code, is available at [kernel.tar.Z](/reflib/software/kernel.tar.Z).

There are two new system calls defined in the model, <tt>ntp_gettime()</tt>, which returns a structure including the
current time, estimated error and maximum error, and <tt>ntp_adjtime()</tt>, which provides a means to adjust kernel
variables, including the current time and frequency offsets. Further information on the calling sequences and variable definitions are in the <tt>./include/sys/timex.h</tt> file.