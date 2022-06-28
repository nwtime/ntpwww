---
title: "4.2.2-series Changelog"
description: "The changelogs for NTP versions 4.2.2 through 4.2.2p4."
type: archives
---

* [4.2.2p4](#422p4)
* [4.2.2p3](#422p3)
* [4.2.2p2](#422p2)
* [4.2.2p1](#422p1)
* [4.2.2](#422)

* * *

#### 4.2.2p4

**Release Date:** 2006 Oct 15

* [Bug 710: compat getnameinfo() has off-by-one error](https://bugs.ntp.org/show_bug.cgi?id=710)
* [Bug 690: Buffer overflow in Windows when doing DNS Lookups](https://bugs.ntp.org/show_bug.cgi?id=690)

* * *

#### 4.2.2p3

**Release Date:** 2006 Aug 5

* [Bug 657: Different OSes need different sized args for IP_MULTICAST_LOOP](https://bugs.ntp.org/show_bug.cgi?id=657)
* [Bug 601: ntpq's decodeint uses an extra level of indirection](https://bugs.ntp.org/show_bug.cgi?id=601)
* Make the `ChangeLog` file cleaner and easier to read
* release engineering/build changes
* Documentation fixes
* Get `sntp` working under AIX-5

* * *

#### 4.2.2p2

**Release Date:** 2006 Jul 9 (broken)

* Get `sntp` working under AIX-5

* * *

#### 4.2.2p1

**Release Date:** 2006 Jul 9

* [Bug 661: Use environment variable to specify the base path to openssl.](https://bugs.ntp.org/show_bug.cgi?id=661)
* [Bug 657: IP_MULTICAST_LOOP uses a u_char value/size](https://bugs.ntp.org/show_bug.cgi?id=657)
* [Bug 637: Ignore UP in*addr_any interfaces](https://bugs.ntp.org/show_bug.cgi?id=637)
* [Bug 633: Avoid writing files in srcdir](https://bugs.ntp.org/show_bug.cgi?id=633)
* [Bug 632: update kernel PPS offsets when PPS offset is re-configured](https://bugs.ntp.org/show_bug.cgi?id=632)
* [Bug 614: manage file descriptors better](https://bugs.ntp.org/show_bug.cgi?id=614)
* Resolve an ambiguity in the copyright notice
* Added some new documentation files
* URL cleanup in the documentation
* quiet `gcc4` complaints
* more Coverity fixes
* release engineering/build changes

* * *

#### 4.2.2

**Release Date:** 2006 Jun 8

* [Bug 360: ntpd loses handles with LAN connection disabled.](https://bugs.ntp.org/show_bug.cgi?id=360)
* [Bug 239: Fix intermittent autokey failure with multicast clients.](https://bugs.ntp.org/show_bug.cgi?id=239)
* SNTP
* Many bugfixes
* Implements the current "goal state" of NTPv4
* Autokey improvements
* Much better IPv6 support
* Rewrite of the multicast code
* New version numbering scheme