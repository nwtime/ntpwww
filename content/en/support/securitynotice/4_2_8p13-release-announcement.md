---
title: "4.2.8p13 Release Announcement"
type: archives
date: "2019-03-07"
---

The NTP Project at Network Time Foundation publicly released ntp-4.2.8p13 on Thursday, 07 March 2019.

This release fixes one security issue in `ntpd`:

* **MEDIUM: [3565: Crafted null dereference attack from a trusted source with an authenticated mode 6 packet](/support/securitynotice/ntpbug3565/)**
  * A crafted malicious authenticated mode 6 (`ntpq`) packet from a permitted network address can trigger a NULL pointer dereference, crashing `ntpd`. Note that for this attack to work, the sending system must be on an address that the target's `ntpd` accepts mode 6 packets from, and must properly authenticate the packet with a private key that is specifically listed as being used for mode 6 authorization.
  * Reported by Magnus Stubman. 

and provides 17 bugfixes and 1 other improvement. 

ENotification of these issues were delivered to our Institutional members on a rolling basis as they were reported and as progress was made.

* * *

**Timeline:**

* 2019 Mar 07: Public release
* 2019 Feb 20: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2019 Jan 16: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2019 Jan 15: Notification from reporter 