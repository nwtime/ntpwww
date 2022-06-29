---
title: "4.2.8p5 Release Announcement"
description: "The NTP Project at Network Time Foundation released NTP 4.2.8p5 on January 7, 2016. This release addresses 1 vulnerability and 14 bug fixes."
type: archives
date: "2016-01-07"
---

NTF's NTP Project has been notified of the following 1 medium-severity vulnerability that is fixed in ntp-4.2.8p5, released on Thursday, 7 January 2016:

* [2956: Small-step/Big-step](/support/securitynotice/ntpbug2956/) / [CVE-2015-5300](https://nvd.nist.gov/vuln/detail/CVE-2015-5300)

ntp-4.2.8p5 also fixes:

* A number of Coverity nits were fixed in the new Unity tests.
* [2829: Clean up pipe_fds in ntpd.c](https://bugs.ntp.org/show_bug.cgi?id=2829)
* [2887: stratum -1 config results as showing value 99](https://bugs.ntp.org/show_bug.cgi?id=2887)
* [2932: Update leapsecond file info in miscopt.html](https://bugs.ntp.org/show_bug.cgi?id=2932)
* [2934: tests/ntpd/t-ntp_scanner.c has a magic constant wired in](https://bugs.ntp.org/show_bug.cgi?id=2934)
* [2944: errno is not preserved properly in ntpdate after sendto call](https://bugs.ntp.org/show_bug.cgi?id=2944)
* [2952: peer associations were broken by the fix for 2901](https://bugs.ntp.org/show_bug.cgi?id=2952) / [CVE-2015-7704](https://nvd.nist.gov/vuln/detail/CVE-2015-7704)
* [2954: Version 4.2.8p4 crashes on startup on some OSes](https://bugs.ntp.org/show_bug.cgi?id=2954)
* [2957: 'unsigned int' vs 'size_t' format clash](https://bugs.ntp.org/show_bug.cgi?id=2957)
* [2958: ntpq: fatal error messages need a final newline](https://bugs.ntp.org/show_bug.cgi?id=2958)
* [2962: truncation of size_t/ptrdiff_t on 64bit targets](https://bugs.ntp.org/show_bug.cgi?id=2962)
* [2965: Local clock didn't work since 4.2.8p4](https://bugs.ntp.org/show_bug.cgi?id=2965)
* [2967: ntpdate command suffers an assertion failure](https://bugs.ntp.org/show_bug.cgi?id=2967)
* [2969: Seg fault from ntpq/mrulist when looking at server with lots of clients](https://bugs.ntp.org/show_bug.cgi?id=2969)
* [2971: ntpq bails on ^C: select fails: Interrupted system call](https://bugs.ntp.org/show_bug.cgi?id=2971)

* * *

**Timeline:**

* 2016 Jan 7: Public release
* 2016 Jan 4: CERT notified and pre-release patch availability announced to CERT
* 2016 Jan 4: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2015 Oct 16: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2016 Oct 8: Initial notification; analysis begins