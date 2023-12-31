---
title: "AIX Hints"
type: archives
noindex: true 
sitemap_exclude: true
---

#### Problem with recent ANSI compilers

On some systems, including AIX, the compiler quits on the `ntp_refclock.c` file when processing the `refclock_report()` routine. The problem, which is either a feature or a bug, has to do with an unwanted promotion of the `u_char` argument to an `int` and a failure of the compiler to recognize the preceding prototype. A workaround is to use ANSI syntax to delare the arguments. Since ANSI compilers are not universally available, this syntax can't be used in the stock distribution.

<pre>
(Message # 60: 2884 bytes, New)
Date: Sat, 19 Aug 1995 13:20:50 -0400
From: "R. Bernstein" <rocky@panix.com>Newsgroups: comp.protocols.time.ntp
to: mills@udel.edu
return-receipt-to: rocky@panix.com
Subject: time and AIX 3.2.5 raw tty bug
</pre>

This posting isn't strictly about NTP, any program that may stop the clock or set the clock backwards is subject to the AIX 3.2.5 bug.

On AIX 3.2.5, there is a bug in the `tty` driver for a raw device which may crash the box under certain conditions: basically a `read()` on a raw `tty`; in effect, a character was read but not as many as specified by `VMIN` when a read timeout occurred. `VTIME` specifies the timeout. See the AIX manual page on `termios.h` or that include file for information on `VMIN` (or `MIN`) `VTIME` (or `TIME`).

A remedy other than to not use raw `tty`'s is to apply patch U435110.

Details of the problem report follow.

* * *

ABSTRACT:
: **IX43779:** TRAP IN `PSX_TIMEO`

ORIGINATING DETAILS:
: Stacktrace shows:
<pre>
IAR:      01460214   posixdd:psx_timeo  + 8bf4: ti 4,r12,0x0
*LR:      014601a0   posixdd:psx_timeo  + 8b80
00212c60: 014604f4   posixdd:psx_timer  + 8ed4
00212cc0: 0144b74c   ttydd:tty_do_offlevel  + 4284
00212d20: 000216fc  .i_offlevel + 8c
00212d70: 00021d78  .i_softint + c8
00001004: 00008714  .finish_interrupt + 80
</pre>

RESPONDER SUMMARY:
: AIX asserted in `psx_timeo()`. Reason for the assert was that the current time was behind `psx_ctime`. Since this state can occur when the current time is changed after a character is received but before the `VTIME` interbyte timer pops, we should not assert on this.

RESPONDER CONCLUSION:
: Removed the requirement that current time > `psx_ctime` by adding a new `L_ntimersub` macro that is used instead of the `ntimersub` macro in `time.h`. Also added a test for (current time - `psx_ctime`) being negative, in that case we do not adjust the new timeout.

Reported to Correct a PTF in Error:     NO
: **Reported as a Highly pervasive problem:** NO
: **PE Apar?:**       NoPE
: **Hiper Apar?:**    NoHiper
: **Status:**         CLOSED  PER
: **Component Name:** AIX V3 FOR RS/6
: **Version:**        320
: **Component ID:**   575603001
: **Submitted:**      94/05/03
: **Closed:**         94/05/05
: **ChangeTeam:**     TX2527
: **APAR FIXED BY:**  U431696  U432151  U432844  U432870  U432979 U433049  U433081  U433459  U433876  U433906  U434598  U434453 U434672  U434737  U435110