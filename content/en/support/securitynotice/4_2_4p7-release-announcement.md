---
title: "4.2.4p7 Release Announcement"
type: archives
date: "2009-05-18"
---

The NTP Public Services Project is pleased to announce that NTP 4.2.4p7, a Point Release of the NTP Reference Implementation from the
NTP Project, is now available.

* * *

#### Security Updates

* [1144: limited (two byte) buffer overflow in ntpq](https://bugs.ntp.org/show_bug.cgi?id=1144) / [CVE-2009-0159](https://nvd.nist.gov/vuln/detail/CVE-2009-0159)
  Credit for finding this vulnerability goes to Geoff Keating of Apple.
* [1149: use SO_EXCLUSIVEADDRUSE on Windows](https://bugs.ntp.org/show_bug.cgi?id=1149)
  Credit for finding this issue goes to Dave Hart.
* [1151: Remote exploit if autokey is enabled](/support/securitynotice/ntpbug1151) / [CVE-2009-1252](https://nvd.nist.gov/vuln/detail/CVE-2009-1252)

* * *

#### Other Changes

* Fix many compiler warnings
* Many fixes and improvements for Windows
* Adds support for AIX 6.1
* Resolves some issues under MacOS X and Solaris
* Improved logging

* * *

Please [report](https://bugs.ntp.org/) any bugs, issues, or desired enhancements.

The NTP (Network Time Protocol) Public Services Project, which is hosted by [Internet Systems Consortium, Inc.](https://www.isc.org/), provides support and additional development resources for the Reference Implementation of NTP produced by the NTP Project.