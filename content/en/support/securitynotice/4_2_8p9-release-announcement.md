---
title: "4.2.8p9 Release Announcement"
type: archives
date: "2016-11-21"
---

NTF's NTP Project is releasing ntp-4.2.8p9 which addresses:

* 1 HIGH severity vulnerability that only affects Windows
* 2 MEDIUM severity vulnerabilities
* 2 MEDIUM/LOW severity vulnerabilities
* 5 LOW severity vulnerabilities  
* 28 other non-security fixes and improvements 

All of the security issues in this release are listed in [VU#633847](https://www.kb.cert.org/vuls/id/633847/).

ntp-4.2.8p9 is currently scheduled to be released on 21 November 2016.

* [3119: Trap crash](/support/securitynotice/ntpbug3119/) / [CVE-2016-9311](https://nvd.nist.gov/vuln/detail/CVE-2016-9311)
  * Reported by Matthew Van Gundy of Cisco ASIG. 
* [3118: Mode 6 unauthenticated trap information disclosure and DDoS vector](/support/securitynotice/ntpbug3118/) / [CVE-2016-9310](https://nvd.nist.gov/vuln/detail/CVE-2016-9310)
  * Reported by Matthew Van Gundy of Cisco ASIG. 
* [3114: Broadcast Mode Replay Prevention DoS](/support/securitynotice/ntpbug3114/) / [CVE-2016-7427](https://nvd.nist.gov/vuln/detail/CVE-2016-7427)
  * Reported by Matthew Van Gundy of Cisco ASIG. 
* [3113: Broadcast Mode Poll Interval Enforcement DoS](/support/securitynotice/ntpbug3113/) / [CVE-2016-7428](https://nvd.nist.gov/vuln/detail/CVE-2016-7428)
  * Reported by Matthew Van Gundy of Cisco ASIG. 
* [3110: Windows: ntpd DoS by oversized UDP packet](/support/securitynotice/ntpbug3110/) / [CVE-2016-9312](https://nvd.nist.gov/vuln/detail/CVE-2016-9312)
  * Reported by Robert Pajak of ABB. 
* [3102: Regression: 010-origin: Zero Origin Timestamp Bypass](/support/securitynotice/ntpbug3102/) / [CVE-2016-7431](https://nvd.nist.gov/vuln/detail/CVE-2016-7431)
  * Reported by Sharon Goldberg and Aanchal Malhotra of Boston University. 
* [3082: Null pointer dereference in _IO_str_init_static_internal()](/support/securitynotice/ntpbug3082/) / [CVE-2016-7434](https://nvd.nist.gov/vuln/detail/CVE-2016-7434)
  * Reported by Magnus Stubman. 
* [3072: Interface selection attack](/support/securitynotice/ntpbug3072/) / [CVE-2016-7429](https://nvd.nist.gov/vuln/detail/CVE-2016-7429)
  * Reported by Miroslav Lichvar of Red Hat. 
* [3071: Client rate limiting and server responses](/support/securitynotice/ntpbug3071/) / [CVE-2016-7426](https://nvd.nist.gov/vuln/detail/CVE-2016-7426)
  * Reported by Miroslav Lichvar of Red Hat. 
* [3067: Reboot sync calculation problem](/support/securitynotice/ntpbug3067/) / [CVE-2016-7433](https://nvd.nist.gov/vuln/detail/CVE-2016-7433)
  * Reported independently by Brian Utterback of Oracle, and by Sharon Goldberg and Aanchal Malhotra of Boston University. 


ENotification of these issues were delivered to our Institutional members on a rolling basis as they were reported and as progress was made.

* * *

**Timeline:**

* 2016 Nov 21: Public release
* 2016 Nov 15: CERT given our software release notification 
* 2016 Nov 14: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* : [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/)
* : Report received