---
title: "Copyright Notice"
type: archives
---

![Clone me,](/documentation/pic/sheepb.jpg) Clone me, says Dolly sheepishly.

Last update: 4-Feb-2020 23:47 UTC

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

1.  [Takao Abe](mailto:takao_abe@xurb.jp) Clock driver for JJY receivers
2.  [Mark Andrews ](mailto:mark_andrews@isc.org) Leitch atomic clock controller
3.  [Bernd Altmeier](mailto:altmeier@atlsoft.de) hopf Elektronik serial line and PCI-bus devices
4.  Viraj Bais and Clayton Kirkwood: port to WindowsNT 3.5
5.  [Michael Barone](mailto:michael.barone@lmco.com) GPSVME fixes
6.  Karl Berry: syslog to file option
7.  [Greg Brackley](mailto:greg.brackley@bigfoot.com) Major rework of WINNT port. Clean up recvbuf and iosignal code into separate modules.
8.  Marc Brett: Magnavox GPS clock driver
9.  [Piete Brooks](mailto:Piete.Brooks@cl.cam.ac.uk) MSF clock driver, Trimble PARSE support
10.  [Nelson B Bolyard](mailto:nelson@bolyard.me) update and complete broadcast and crypto features in sntp
11.  Jean-Francois Boudreault: IPv6 support
12.  [Reg Clemens](mailto:reg@dwf.com) Oncore driver (Current maintainer)
13.  Steve Clift: OMEGA clock driver
14.  [Casey Crellin](mailto:casey@csc.co.za) vxWorks (Tornado) port and help with target configuration
15.  [Sven Dietrich](mailto:Sven_Dietrich@trimble.COM) Palisade reference clock driver, NT adj. residuals, integrated Greg's Winnt port.
16.  John A. Dundas III: Apple A/UX port
17.  [Torsten Duwe](mailto:duwe@immd4.informatik.uni-erlangen.de) Linux port
18.  Dennis Ferguson: foundation code for NTP Version 2 as specified in RFC-1119
19.  John Hay: IPv6 support and testing
20.  Dave Hart: General maintenance, Windows port interpolation rewrite
21.  [Claas Hilbrecht](mailto:neoclock4x@linum.com) NeoClock4X clock driver
22.  Glenn Hollinger: GOES clock driver
23.  [Mike Iglesias](mailto:iglesias@uci.edu) DEC Alpha port
24.  Jim Jagielski: A/UX port
25.  [Jeff Johnson](mailto:jbj@chatham.usdesign.com) massive prototyping overhaul
26.  [Hans Lambermont](mailto:H.Lambermont@chello.nl) ntpsweep
27.  [Poul-Henning Kamp](mailto:phk@FreeBSD.ORG) Oncore driver (Original author)
28.  [Frank Kardel](https://www4.cs.fau.de/~kardel/) [email](mailto:kardel@ntp.org) PARSE <GENERIC> (driver 14 reference clocks), STREAMS modules for PARSE, support scripts, syslog cleanup, dynamic interface handling
29.  [Johannes Maximilian Kuehn](mailto:kuehn@ntp.org) Rewrote <code>sntp</code> to comply with NTPv4 specification, <code>ntpq saveconfig</code>
30.  William L. Jones: RS/6000 AIX modifications, HPUX modifications
31.  [Dave Katz](mailto:dkatz@cisco.com) RS/6000 AIX port
32.  [Craig Leres](mailto:leres@ee.lbl.gov) 4.4BSD port, ppsclock, Magnavox GPS clock driver
33.  [George Lindholm](mailto:lindholm@ucs.ubc.ca) SunOS 5.1 port
34.  Louis A. Mamakos: MD5-based authentication
35.  [Lars H. Mathiesen](mailto:thorinn@diku.dk) adaptation of foundation code for Version 3 as specified in RFC-1305
36.  [Danny Mayer](mailto:mayer@ntp.org) Network I/O, Windows Port, Code Maintenance
37.  [David L. Mills](mailto:mills@udel.edu) Version 4 foundation, precision kernel; clock drivers: 1, 3, 4, 6, 7, 11, 13, 18, 19, 22, 36
38.  Wolfgang Moeller: VMS port
39.  Jeffrey Mogul: ntptrace utility
40.  Tom Moore: i386 svr4 port
41.  [Kamal A Mostafa](mailto:kamal@whence.com) SCO OpenServer port
42.  Derek Mulcahy and [Damon Hart-Davis](mailto:d@hd.org) ARCRON MSF clock driver
43.  [Rob Neal](mailto:neal@ntp.org) Bancomm refclock and config/parse code maintenance
44.  [Rainer Pruy](mailto:Rainer.Pruy@informatik.uni-erlangen.de) monitoring/trap scripts, statistics file handling
45.  Dirce Richards: Digital UNIX V4.0 port
46.  [Wilfredo Sánchez](mailto:wsanchez@apple.com) added support for NetInfo
47.  Nick Sayer: SunOS streams modules
48.  [Jack Sasportas](mailto:jack@innovativeinternet.com) Saved a Lot of space on the stuff in the html/pic/ subdirectory
49.  [Ray Schnitzler](mailto:schnitz@unipress.com) Unixware1 port
50.  [Michael Shields](mailto:shields@tembel.org) USNO clock driver
51.  Jeff Steinman: Datum PTS clock driver
52.  [Harlan Stenn](mailto:harlan@pfcs.com) GNU automake/autoconfigure makeover, various other bits (see the ChangeLog)
53.  [Kenneth Stone](mailto:ken@sdd.hp.com) HP-UX port
54.  [Ajit Thyagarajan](mailto:ajit@ee.udel.edu) IP multicast/anycast support
55.  Tomoaki TSURUOKA: TRAK clock driver
56.  [Brian Utterback](mailto:brian.utterback@oracle.com) General codebase, Solaris issues
57.  [Loganaden Velvindron](mailto:loganaden@gmail.com) Sandboxing (libseccomp) support
58.  [Paul A Vixie](mailto:vixie@vix.com) TrueTime GPS driver, generic TrueTime clock driver
59.  [Ulrich Windl](mailto:Ulrich.Windl@rz.uni-regensburg.de) corrected and validated HTML documents according to the HTML DTD
