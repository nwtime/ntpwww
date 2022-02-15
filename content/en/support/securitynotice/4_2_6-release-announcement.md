---
title: "4.2.6 Release Announcement"
type: archives
date: "2009-12-09"
---

The NTP Public Services Project is pleased to announce that NTP 4.2.6, a Stable Release of the NTP Reference Implementation from the NTP Project, is now available.

**Focus:** Security Fixes

**Severity:** HIGH

This release fixes the following high-severity vulnerability:

* [1331 DoS with mode 7 packets](/support/securitynotice/ntpbug1331/) - [CVE-2009-3563](https://nvd.nist.gov/vuln/detail/CVE-2009-3563).

NTP mode 7 (`MODE_PRIVATE`) is used by the `ntpdc` query and control utility. In contrast, `ntpq` uses NTP mode 6 (`MODE_CONTROL`), while routine
NTP time transfers use modes 1 through 5. Upon receipt of an incorrect mode 7 request or a mode 7 error response from an address which is not
listed in a `restrict ... noquery` or `restrict ... ignore` statement, `ntpd` will reply with a mode 7 error response (and log a message). In
this case:

* If an attacker spoofs the source address of `ntpd` host A in a mode 7 response packet sent to `ntpd` host B, both A and B will continuously send
each other error responses, for as long as those packets get through.
* If an attacker spoofs an address of `ntpd` host A in a mode 7 response packet sent to `ntpd` host A, A will respond to itself endlessly,
consuming CPU and logging excessively.

Credit for finding this vulnerability goes to Robin Park and Dmitri Vinokurov of Alcatel-Lucent.

> THIS IS A STRONGLY RECOMMENDED UPGRADE.

* * *

Please [report](https://bugs.ntp.org/) any bugs, issues, or desired enhancements.

The NTP (Network Time Protocol) Public Services Project, which is hosted by [Internet Systems Consortium, Inc.](https://www.isc.org/), provides support and additional development resources for the Reference Implementation of NTP produced by the NTP Project.