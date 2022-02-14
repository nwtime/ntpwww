---
title: "4.2.8p7 Release Announcement"
type: archives
date: "2016-04-26"
---

NTF's NTP Project has been notified of the following 4 low- and 7 medium-severity vulnerabilities that are fixed in ntp-4.2.8p7, released on Tuesday, 26 April 2016:

* [3020: Refclock impersonation vulnerability](/support/securitynotice/ntpbug3020/) / [CVE-2016-1551](https://nvd.nist.gov/vuln/detail/CVE-2016-1551/) AKA: refclock-peering
  * Reported by Matt Street and others of Cisco ASIG 
* [3012: Sybil vulnerability: ephemeral association attack](/support/securitynotice/ntpbug3012/) / [CVE-2016-1549](https://nvd.nist.gov/vuln/detail/CVE-2016-1549/) AKA: ntp-sybil - MITIGATION ONLY
  * Reported  by Matthew Van Gundy of Cisco ASIG 
* [3011: Duplicate IPs on unconfig directives will cause an assertion botch](/support/securitynotice/ntpbug3011/) / [CVE-2016-2516](https://nvd.nist.gov/vuln/detail/CVE-2016-2516/)
  * Reported  by Yihan Lian of the Cloud Security Team, Qihoo 360 
* [3010: Remote configuration trustedkey/requestkey values are not properly validated](/support/securitynotice/ntpbug3010/) / [CVE-2016-2517](https://nvd.nist.gov/vuln/detail/CVE-2016-2517/)
  * Reported  by Yihan Lian of the Cloud Security Team, Qihoo 360 
* [3009: Crafted addpeer with hmode > 7 causes array wraparound with MATCH_ASSOC](/support/securitynotice/ntpbug3009/) / [CVE-2016-2518](https://nvd.nist.gov/vuln/detail/CVE-2016-2518/)
  * Reported  by Yihan Lian of the Cloud Security Team, Qihoo 360 
* [3008: ctl_getitem() return value not always checked](/support/securitynotice/ntpbug3008/) / [CVE-2016-2519](https://nvd.nist.gov/vuln/detail/CVE-2016-2519/)
  * Reported  by Yihan Lian of the Cloud Security Team, Qihoo 360 
* [3007: Validate crypto-NAKs](/support/securitynotice/ntpbug3007/) / [CVE-2016-1547](https://nvd.nist.gov/vuln/detail/CVE-2016-1547/) AKA: nak-dos
  * Reported  by Stephen Gray and Matthew Van Gundy of Cisco ASIG 
* [2978: Interleave-pivot](/support/securitynotice/ntpbug2978/) / [CVE-2016-1548](https://nvd.nist.gov/vuln/detail/CVE-2016-1548/) - MITIGATION ONLY
  * Reported  by Miroslav Lichvar of RedHat and separately by Jonathan Gardner of Cisco ASIG 
* [2952: KoD fix: peer associations were broken by the fix for 2901](/support/securitynotice/ntpbug2952/) / [CVE-2015-7704](https://nvd.nist.gov/vuln/detail/CVE-2015-7704/) AKA: Symmetric active/passive mode is broken
  * Reported  by Michael Tatarinov, NTP Project Developer Volunteer 
* [2945](/support/securitynotice/ntpbug2945/) / [2901: Zero Origin Timestamp Bypass](/support/securitynotice/ntpbug2901/) / [CVE-2015-8138](https://nvd.nist.gov/vuln/detail/CVE-2015-8138/) AKA: Additional KoD Checks
  * Reported  by Jonathan Gardner of Cisco ASIG 
* [2879: Improve NTP security against buffer comparison timing attacks, authdecrypt-timing](/support/securitynotice/ntpbug2879/) / [CVE-2016-1550](https://nvd.nist.gov/vuln/detail/CVE-2016-1550/) AKA: authdecrypt-timing
  * Reported  independently by Loganaden Velvindron, and Matthew Van Gundy and Stephen Gray of Cisco ASIG. 

The following issues already listed above are "Mitigation only" and are expected to be fully resolved in an upcoming release.

* [3012: Sybil vulnerability: ephemeral association attack](/support/securitynotice/ntpbug3012/) - MITIGATION ONLY
* [2978: Interleave pivot](/support/securitynotice/ntpbug2978/) - MITIGATION ONLY 

The following issues were fixed in earlier releases and contain improvements in this p7 release:

* [2936: Skeleton Key](/support/securitynotice/ntpbug2936/)
* [2901: Clients that receive a KoD should validate the origin timestamp field](/support/securitynotice/ntpbug2901/)

* * *

**Timeline:**

* 2016 Apr 26: Public release
* 2016 Apr 18: CERT notified and pre-release patch availability announced to CERT
* 2016 Apr 12: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2016 Feb 21: CVE numbers requested from Mitre
* 2016 Feb 19: Initial notification from Qihoo/360; analysis begins
* 2016 Feb 14: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2016 Jan 12: Initial notification from Cisco; analysis begins