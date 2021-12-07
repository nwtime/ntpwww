---
title: "4.2.8p11 Release Announcement"
type: archives
date: "2018-02-27"
---

The NTP Project at Network Time Foundation is releasing ntp-4.2.8p11.

This release addresses five security issues in `ntpd`:

* **LOW/MEDIUM: [3012: Sybil vulnerability: ephemeral association attack](/support/securitynotice/ntpbug3012)**
  * While fixed in ntp-4.2.8p7, there are significant additional protections for this issue in 4.2.8p11.
  * Reported by Matt Van Gundy of Cisco. 
* **INFO/MEDIUM: [3412: ctl_getitem(): buffer read overrun leads to undefined behavior and information leak](/support/securitynotice/ntpbug3412)**
  * Reported by Yihan Lian of Qihoo 360. 
* **LOW: [3415: Multiple authenticated ephemeral associations](/support/securitynotice/ntpbug3415)**
  * Reported on the questions@ list. 
* **LOW: [3453: Interleaved symmetric mode cannot recover from bad state](/support/securitynotice/ntpbug3453)**
  * Reported by Miroslav Lichvar of Red Hat. 
* **LOW/MEDIUM: [3454: Unauthenticated packet can reset authenticated interleaved association](/support/securitynotice/ntpbug3454)**
  * Reported by Miroslav Lichvar of Red Hat. 

one security issue in `ntpq`:

* **MEDIUM: [3414: ntpq:decodearr() can write beyond its buffer limit](/support/securitynotice/ntpbug3414)**
  * Reported by Michael Macnair of Thales-esecurity.com. 

and provides over 33 bugfixes and 32 other improvements.

ENotification of these issues were delivered to our Institutional members on a rolling basis as they were reported and as progress was made.

* * *

**Timeline:**

* 2018 Feb 27: Public release
* 2018 Feb 20: CVE numbers assigned. NEWS file updated. Tarball updated. CERT notified.
* 2018 Feb 12: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits)
* 2018 Feb 07: Regressions reported for FIPS and multicast mode.
* 2018 Feb 05: Bugs [3453](/support/securitynotice/ntpbug3453) and [3454](/support/securitynotice/ntpbug3454) reported.
* 2018 Jan 23: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits)
* : Notification from reporter 