---
title: "Copyright Notice"
description: "The following copyright notice applies to all files collectively called the Network Time Protocol Version 4 Distribution. Unless specifically declared otherwise in an individual file, this entire notice applies as if the text was explicitly included in the file."
type: archives
aliases:
    - /current-stable/copyright/
    - /license/
---

![webp](/documentation/pic/sheepb.webp) Clone me, says Dolly sheepishly.

* * *

The following copyright notice applies to all files collectively called the Network Time Protocol Version 4 Distribution. Unless specifically declared otherwise in an individual file, this entire notice applies as if the text was explicitly included in the file.

<pre>***********************************************************************
*                                                                     *
* Copyright (c) University of Delaware 1992-2015                      *
*                                                                     *
* Permission to use, copy, modify, and distribute this software and   *
* its documentation for any purpose with or without fee is hereby     *
* granted, provided that the above copyright notice appears in all    *
* copies and that both the copyright notice and this permission       *
* notice appear in supporting documentation, and that the name        *
* University of Delaware not be used in advertising or publicity      *
* pertaining to distribution of the software without specific,        *
* written prior permission. The University of Delaware makes no       *
* representations about the suitability this software for any         *
* purpose. It is provided "as is" without express or implied          *
* warranty.                                                           *
*                                                                     *
***********************************************************************
</pre>

Content starting in 2011 from Harlan Stenn, Danny Mayer, and Martin Burnicki is:

<pre>***********************************************************************
*                                                                     *
* Copyright (c) Network Time Foundation 2011-2020                     *
*                                                                     *
* All Rights Reserved                                                 *
*                                                                     *
* Redistribution and use in source and binary forms, with or without  *
* modification, are permitted provided that the following conditions  *
* are met:                                                            *
* 1. Redistributions of source code must retain the above copyright   *
*    notice, this list of conditions and the following disclaimer.    *
* 2. Redistributions in binary form must reproduce the above          *
*    copyright notice, this list of conditions and the following      *
*    disclaimer in the documentation and/or other materials provided  *
*    with the distribution.                                           *
*                                                                     *
* THIS SOFTWARE IS PROVIDED BY THE AUTHORS ``AS IS'' AND ANY EXPRESS  *
* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED   *
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE  *
* ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE    *
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR *
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT   *
* OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR  *
* BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF          *
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT           *
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE   *
* USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH    *
* DAMAGE.                                                             *
***********************************************************************
</pre>

The following individuals contributed in part to the Network Time Protocol Distribution Version 4 and are acknowledged as authors of this work.

* [Takao Abe](mailto:takao_abe@xurb.jp) Clock driver for JJY receivers
* [Mark Andrews ](mailto:mark_andrews@isc.org) Leitch atomic clock controller
* [Bernd Altmeier](mailto:altmeier@atlsoft.de) hopf Elektronik serial line and PCI-bus devices
* Viraj Bais and Clayton Kirkwood: port to WindowsNT 3.5
* [Michael Barone](mailto:michael.barone@lmco.com) GPSVME fixes
* Karl Berry: syslog to file option
* [Greg Brackley](mailto:greg.brackley@bigfoot.com) Major rework of WINNT port. Clean up recvbuf and iosignal code into separate modules.
* Marc Brett: Magnavox GPS clock driver
* [Piete Brooks](mailto:Piete.Brooks@cl.cam.ac.uk) MSF clock driver, Trimble PARSE support
* [Nelson B Bolyard](mailto:nelson@bolyard.me) update and complete broadcast and crypto features in sntp
* Jean-Francois Boudreault: IPv6 support
* Reg Clemens: Oncore driver (Current maintainer)
* Steve Clift: OMEGA clock driver
* Casey Crellin: vxWorks (Tornado) port and help with target configuration
* [Philippe De Muyter](mailto:phdm@macqel.be) Wharton reference clock driver, sysV68 and AIX modifications
* [Sven Dietrich](mailto:Sven_Dietrich@trimble.COM) Palisade reference clock driver, NT adj. residuals, integrated Greg's Winnt port.
* John A. Dundas III: Apple A/UX port
* [Torsten Duwe](mailto:duwe@immd4.informatik.uni-erlangen.de) Linux port
* Dennis Ferguson: foundation code for NTP Version 2 as specified in RFC-1119
* John Hay: IPv6 support and testing
* [Dave Hart](mailto:davehart@gmail.com) General maintenance, IPv6 cleanup, Windows serial PPSAPI
* [Claas Hilbrecht](mailto:neoclock4x@linum.com) NeoClock4X clock driver
* Glenn Hollinger: GOES clock driver
* [Mike Iglesias](mailto:iglesias@uci.edu) DEC Alpha port
* Jim Jagielski: A/UX port
* [Jeff Johnson](mailto:jbj@chatham.usdesign.com) massive prototyping overhaul
* [Hans Lambermont](mailto:H.Lambermont@chello.nl) ntpsweep
* [Poul-Henning Kamp](mailto:phk@FreeBSD.ORG) Oncore driver (Original author)
* [Frank Kardel](https://www4.cs.fau.de/~kardel/) [email](mailto:kardel@ntp.org) PARSE <GENERIC> (driver 14 reference clocks), STREAMS modules for PARSE, support scripts, syslog cleanup, dynamic interface handling
* [Johannes Maximilian Kuehn](mailto:kuehn@ntp.org) Rewrote <code>sntp</code> to comply with NTPv4 specification, <code>ntpq saveconfig</code>
* William L. Jones: RS/6000 AIX modifications, HPUX modifications
* [Dave Katz](mailto:dkatz@cisco.com) RS/6000 AIX port
* [Craig Leres](mailto:leres@ee.lbl.gov) 4.4BSD port, ppsclock, Magnavox GPS clock driver
* [George Lindholm](mailto:lindholm@ucs.ubc.ca) SunOS 5.1 port
* Louis A. Mamakos: MD5-based authentication
* [Lars H. Mathiesen](mailto:thorinn@diku.dk) adaptation of foundation code for Version 3 as specified in RFC-1305
* [Danny Mayer](mailto:mayer@ntp.org) Network I/O, Windows Port, Code Maintenance
* [David L. Mills](https://www.nwtime.org/tribute-to-david-l-mills/) Version 4 foundation, precision kernel; clock drivers: 1, 3, 4, 6, 7, 11, 13, 18, 19, 22, 36
* Wolfgang Moeller: VMS port
* Jeffrey Mogul: ntptrace utility
* Tom Moore: i386 svr4 port
* [Kamal A Mostafa](mailto:kamal@whence.com) SCO OpenServer port
* Derek Mulcahy and [Damon Hart-Davis](mailto:d@hd.org) ARCRON MSF clock driver
* [Rob Neal](mailto:neal@ntp.org) Bancomm refclock and config/parse code maintenance
* [Rainer Pruy](mailto:Rainer.Pruy@informatik.uni-erlangen.de) monitoring/trap scripts, statistics file handling
* Dirce Richards: Digital UNIX V4.0 port
* [Wilfredo Sánchez](mailto:wsanchez@apple.com) added support for NetInfo
* Nick Sayer: SunOS streams modules
* [Jack Sasportas](mailto:jack@innovativeinternet.com) Saved a Lot of space on the stuff in the html/pic/ subdirectory
* [Ray Schnitzler](mailto:schnitz@unipress.com) Unixware1 port
* [Michael Shields](mailto:shields@tembel.org) USNO clock driver
* Jeff Steinman: Datum PTS clock driver
* [Harlan Stenn](mailto:harlan@pfcs.com) GNU automake/autoconfigure makeover, various other bits (see the ChangeLog)
* [Kenneth Stone](mailto:ken@sdd.hp.com) HP-UX port
* [Ajit Thyagarajan](mailto:ajit@ee.udel.edu) IP multicast/anycast support
* Tomoaki TSURUOKA: TRAK clock driver
* [Brian Utterback](mailto:brian.utterback@oracle.com) General codebase, Solaris issues
* [Loganaden Velvindron](mailto:loganaden@gmail.com) Sandboxing (libseccomp) support
* [Paul A Vixie](mailto:vixie@vix.com) TrueTime GPS driver, generic TrueTime clock driver
* [Ulrich Windl](mailto:Ulrich.Windl@rz.uni-regensburg.de) corrected and validated HTML documents according to the HTML DTD
