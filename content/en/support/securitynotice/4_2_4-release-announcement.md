---
title: "4.2.4 Release Announcement"
description: "The release announcement for NTP 4.2.4, which was released on December 18, 2006."
type: archives
date: "2006-12-18"
---

The NTP Public Services Project is pleased to announce that NTP 4.2.4, a Stable Release of the NTP Reference Implementation from the NTP Project, is now available.

The focus of this Stable Release is enhancements and bug fixes.

Please [report](https://bugs.ntp.org/) any bugs, issues, or desired enhancements.

* * *

#### Changes in this release

Dynamic interface rescanning was added to simplify the use of `ntpd` in conjunction with DHCP. GNU AutoGen is used for its command-line options
processing. Separate PPS devices are supported for PARSE refclocks, MD5 signatures are now provided for the release files. Drivers have been
added for some new ref-clocks and have been removed for some older ref-clocks. This release also includes other improvements, documentation
and bug fixes.

K&R C is no longer supported as of NTP-4.2.4. We are now aiming for ANSI C support.