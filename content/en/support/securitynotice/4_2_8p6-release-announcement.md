---
title: "4.2.8p6 Release Announcement"
type: archives
date: "2016-01-19"
---

NTF's NTP Project has been notified of the following low- and medium-severity vulnerabilities that are fixed in ntp-4.2.8p6, released on Tuesday, 19 January 2016:

* [2948: Potential Infinite Loop in ntpq](/support/securitynotice/ntpbug2948/) / [CVE-2015-8158](https://nvd.nist.gov/vuln/detail/CVE-2015-8158)
  * Reported by Cisco ASIG 
* [2945: origin: Zero Origin Timestamp Bypass](/support/securitynotice/ntpbug2945/) / [CVE-2015-8138](https://nvd.nist.gov/vuln/detail/CVE-2015-8138)
  * Reported by Cisco ASIG 
* [2942: Off-path Denial of Service (DoS) attack on authenticated broadcast mode](/support/securitynotice/ntpbug2942/) / [CVE-2015-7979](https://nvd.nist.gov/vuln/detail/CVE-2015-7979)
  * Reported by Cisco ASIG 
* [2940: Stack exhaustion in recursive traversal of restriction list](/support/securitynotice/ntpbug2940/) / [CVE-2015-7978](https://nvd.nist.gov/vuln/detail/CVE-2015-7978)
  * Reported by Cisco ASIG 
* [2939: reslist NULL pointer dereference](/support/securitynotice/ntpbug2939/) / [CVE-2015-7977](https://nvd.nist.gov/vuln/detail/CVE-2015-7977)
  * Reported by Cisco ASIG 
* [2938: ntpq saveconfig command allows dangerous characters in filenames](/support/securitynotice/ntpbug2938/) / [CVE-2015-7976](https://nvd.nist.gov/vuln/detail/CVE-2015-7976)
  * Reported by Cisco ASIG 
* [2937: nextvar() missing length check](/support/securitynotice/ntpbug2937/) / [CVE-2015-7975](https://nvd.nist.gov/vuln/detail/CVE-2015-7975)
  * Reported by Cisco ASIG 
* [2936: Skeleton Key: Missing key check allows impersonation between authenticated peers](/support/securitynotice/ntpbug2936/) / [CVE-2015-7974](https://nvd.nist.gov/vuln/detail/CVE-2015-7974)
  * Reported by Cisco ASIG 
* [2935: Deja Vu: Replay attack on authenticated broadcast mode](/support/securitynotice/ntpbug2935/) / [CVE-2015-7973](https://nvd.nist.gov/vuln/detail/CVE-2015-7973)
  * Reported by Cisco ASIG. 

Additionally, mitigations are published for the following two issues:

* [2947: ntpq vulnerable to replay attacks](/support/securitynotice/ntpbug2947/) / [CVE-2015-8140](https://nvd.nist.gov/vuln/detail/CVE-2015-8140)
  * Reported by Cisco ASIG 
* [2946: Origin Leak: ntpq and ntpdc, disclose origin](/support/securitynotice/ntpbug2946/) / [CVE-2015-8139](https://nvd.nist.gov/vuln/detail/CVE-2015-8139)
  * Reported by Cisco ASIG, discovered by Boston University 

* * *

**Timeline:**

* 2016 Jan 19: Public release
* 2016 Jan 18: CERT notified and pre-release patch availability announced to CERT
* 2016 Jan 17: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2015 Nov 23: CVE numbers requested from Mitre
* 2015 Nov 5: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2016 Oct 16: Initial notification from Cisco; analysis begins