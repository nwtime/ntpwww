---
title: "4.2.8p14 Release Announcement"
type: archives
date: "2020-03-03"
---

The NTP Project at Network Time Foundation publicly released ntp-4.2.8p14 on Tuesday, 03 March 2020.

This release fixes three security issues in `ntpd`:

* **NONE: [3610: `process_control()` should bail earlier on short packets.](/support/securitynotice/ntpbug3610/)**
  * Reported by Philippe Antoine (Catena cyber with oss-fuzz). 
* **MEDIUM: [3596: Unauthenticated `ntpd` may be susceptible to IPv4 spoof attack from highly predictable transmit timestamps.](/support/securitynotice/ntpbug3596/)**
  * Reported by Miroslav Lichvar. 
* **MEDIUM: [3592: DoS Attack on unauthenticated client.](/support/securitynotice/ntpbug3592/)**
    * The fix for [3445](https://bugs.ntp.org/show_bug.cgi?id=3445) introduced a bug whereby a system that is running ntp-4.2.8p12 (possibly earlier) or p13 that only has one unauthenticated time source can be attacked in a way that causes the victim's next poll to its source to be delayed, for as long as the attack is maintained.
    * Reported by Miroslav Lichvar. 

and provides 46 bugfixes and addresses 4 other issues.

ENotification of these issues were delivered to our Institutional members on a rolling basis as they were reported and as progress was made.

* * *

**Timeline:**

* 2020 Mar 03: Public release
* 2020 Feb 17: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2019 Jun 05: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2019 May 30: Notification from reporter 