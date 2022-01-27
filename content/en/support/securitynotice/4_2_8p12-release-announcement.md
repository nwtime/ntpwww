---
title: "4.2.8p12 Release Announcement"
type: archives
date: "2018-08-14"
---

The NTP Project at Network Time Foundation publicly released ntp-4.2.8p13 on Tuesday, 14 August 2018.

This release improves on one security issue in `ntpd`:

* **LOW/MEDIUM: [3012: Sybil vulnerability: ephemeral association attack](/support/securitynotice/ntpbug3012p12)**
  * While fixed in ntp-4.2.8p7 and with significant additional protections for this issue in 4.2.8p11, ntp-4.2.8p12 includes a fix for an edge case in the new noepeer support.
  * Originally reported by Matt Van Gundy of Cisco. Edge-case hole reported by Martin Burnicki of Meinberg. 

one security issue in `ntpq` and `ntpdc`:

* **LOW: [3505: The openhost() function used during command-line hostname processing by ntpq and ntpdc can write beyond its buffer limit.](/support/securitynotice/ntpbug3505)**
  * Reported by Fakhri Zulkifli. 

and provides 27 bugfixes and 4 other improvements.

ENotification of these issues were delivered to our Institutional members on a rolling basis as they were reported and as progress was made.

* * *

**Timeline:**

* 2018 Aug 14: Public release
* 2018 Jul 25: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits)