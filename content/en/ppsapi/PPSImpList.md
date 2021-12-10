---
title: "Available implementations of Pulse Per Second (PPS) API"
type: "archives"
---

This document lists known publicly-available implementations of the Pulse Per Second (PPS) API described in [RFC 2783](/reflib/rfc/rfc2783.txt).

This page was last updated 18 October 1999 at 15:03 by [Jeff Mogul](mailto:mogul@pa.dec.com).

* * *

*   [NetBSD](#netbsd)
*   [Linux](#linux)
*   [FreeBSD](#freebsd)

* * *

#### NetBSD

A prototype implementation for [NetBSD](https://netbsd.org/), based on an earlier draft of this specification, using the `com` serial driver for NS8250, NS16450, and NS16650 UARTS is available in NetBSD-current.

> **Note:** This implementation currently corresponds to an earlier version of the API specification, and should NOT be used in production environments.

The relevant source files are:

<pre>src/sys/sys/timepps.h
src/sys/dev/ic/com.c
src/sys/dev/ic/comvar.h
</pre>

Information valid as of: 10 June 1998
: Contact: [Jonathan Stone](mailto:jonathan@NetBSD.ORG)


* * *

#### Linux

An implementation for Linux 2.2.12 is available as an [extension package](https://mirrors.edge.kernel.org/pub/linux/daemons/ntp/PPS/). The API has been implemented for the serial driver, using the Carrier Detect (CD) pin. The optional `time_pps_kcbind()` is implemented for `hardpps()`. At the time of writing the most current version is contained in PPSkit-0.8.0.tar.gz which adds general PPS capabilities, as well as a kernel upgrade to nanoseconds, the newer NTP algorithms, and the PPS API.

The relevant source files for the PPS API are:

<pre>/usr/src/linux/include/linux/timepps.h
/usr/src/linux/drivers/char/serial.c
</pre>

The implementation supports a signal on the carrier detect pin of any interrupt-driven serial port. Supported capabilities currently are:

<pre>PPS_CAPTUREASSERT
PPS_CAPTURECLEAR
PPS_OFFSETASSERT
PPS_OFFSETCLEAR
PPS_ECHOASSERT
PPS_ECHOCLEAR
PS_CANWAIT
PPS_TSFMT_TSPEC
PPS_KC_HARDPPS
</pre>

Information valid as of: 10 October 1999
: Contact: [Ulrich Windl](mailto:Ulrich.Windl@rz.uni-regensburg.de)

* * *

#### FreeBSD

The PPS API is a standard part of [FreeBSD](https://www.freebsd.org/). It is included in FreeBSD-CURRENT as of 10 Oct 1999, FreeBSD-3.3-STABLE as of 16 Oct 1999 and releases built after these dates. (Until the specification changes.)

The implementation includes driver support for parallel ports and async serial ports.

The relevant source files are:

<pre>src/sys/sys/timepps.h
src/sys/kern/kern_clock.c
src/sys/i386/isa/sio.c
src/sys/dev/ppbus/pps.c
</pre>

Information valid as of: 16 October 1999
: Contact: jhay@FreeBSD.org
