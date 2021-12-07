---
title: "4.2.8p15 Release Announcement"
type: archives
date: "2020-06-23"
---

The NTP Project at Network Time Foundation publicly released ntp-4.2.8p15 on Tuesday, 23 June 2020.

This release fixes one security issue in `ntpd`:

* MEDIUM: [Sec 3661](/support/securitynotice/ntpbug3661): Memory leak with CMAC keys
  : Systems that use a CMAC algorithm in `ntp.keys` will not release a bit of memory on each packet that uses a CMAC key, eventually causing `ntpd` to run out of memory and fail. The [CMAC cleanup](https://bugs.ntp.org/show_bug.cgi?id=3447), part of ntp-4.2.8p11 and ntp-4.3.97, introduced a bug whereby the CMAC data structure was no longer completely removed.
  : Reported by Martin Burnicki of Meinberg. 

and provides 13 bugfixes.

ENotification of these issues were delivered to our Institutional members on a rolling basis as they were reported and as progress was made.

* * *

**Timeline:**

* 2020 Jun 23: Public release
* 2020 Apr 12: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits)
* 2020 Apr 07: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits)
* 2020 Apr 01: Notification from reporter 