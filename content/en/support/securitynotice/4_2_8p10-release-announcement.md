---
title: "4.2.8p10 Release Announcement"
type: archives
date: "2017-03-21"
---

NTF's NTP Project is releasing ntp-4.2.8p10 which addresses:

* 6 MEDIUM severity vulnerabilities (1 is about the Windows PPSAPI DLL)
* 5 LOW severity vulnerabilities (2 are in the Windows Installer)
* 4 Informational-level vulnerabilities 
* 15 other non-security fixes and improvements 

ntp-4.2.8p10 was released on 21 March 2017.

* [3389: Denial of Service via Malformed Config](/support/securitynotice/ntpbug3389/) / [CVE-2017-6464](https://nvd.nist.gov/vuln/detail/CVE-2017-6464)
  * Reported by Cure53 (Pentest report 01.2017).
* [3388: Buffer Overflow in DPTS Clock](/support/securitynotice/ntpbug3388/) / [CVE-2017-6462](https://nvd.nist.gov/vuln/detail/CVE-2017-6462)
  * Reported by Cure53 (Pentest report 01.2017). 
* [3387: Authenticated DoS via Malicious Config Option](/support/securitynotice/ntpbug3387/) / [CVE-2017-6463](https://nvd.nist.gov/vuln/detail/CVE-2017-6463)
  * Reported by Cure53 (Pentest report 01.2017). 
* [3386: ntpq_stripquotes() returns incorrect Value](/support/securitynotice/ntpbug3386/)
  * Reported by Cure53 (Pentest report 01.2017). 
* [3385: ereallocarray()/eallocarray() underused](/support/securitynotice/ntpbug3385/)
  * Reported by Cure53 (Pentest report 01.2017). 
* [3384: Windows: Privileged execution of User Library code](/support/securitynotice/ntpbug3384/) / [CVE-2017-6455](https://nvd.nist.gov/vuln/detail/CVE-2017-6455)
  * Reported by Cure53 (Pentest report 01.2017). 
* [3383: Windows Installer: Stack Buffer Overflow from Command Line](/support/securitynotice/ntpbug3383/) / [CVE-2017-6452](https://nvd.nist.gov/vuln/detail/CVE-2017-6452)
  * Reported by Cure53 (Pentest report 01.2017). 
* [3382: Windows Installer: Data Structure terminated insufficiently](/support/securitynotice/ntpbug3382/) / [CVE-2017-6459](https://nvd.nist.gov/vuln/detail/CVE-2017-6459)
  * Reported by Cure53 (Pentest report 01.2017). 
* 3381: Copious amounts of Unused Code](/support/securitynotice/ntpbug3381/)
  * Reported by Cure53 (Pentest report 01.2017). 
* [3380: Off-by-one in Oncore GPS Receiver](/support/securitynotice/ntpbug3380/)
  * Reported by Cure53 (Pentest report 01.2017). 
* [3379: Potential Overflows in ctl_put() functions](/support/securitynotice/ntpbug3379/) / [CVE-2017-6458](https://nvd.nist.gov/vuln/detail/CVE-2017-6458)
  * Reported by Cure53 (Pentest report 01.2017). 
* [3378: Improper use of snprintf() in mx4200_send()](/support/securitynotice/ntpbug3378/) / [CVE-2017-6451](https://nvd.nist.gov/vuln/detail/CVE-2017-6451)
  * Reported by Cure53 (Pentest report 01.2017). 
* [3377: Buffer Overflow in ntpq when fetching reslist](/support/securitynotice/ntpbug3377/) / [CVE-2017-6460](https://nvd.nist.gov/vuln/detail/CVE-2017-6460)
  * Reported by Cure53 (Pentest report 01.2017). 
* [3376: Makefile does not enforce Security Flags](/support/securitynotice/ntpbug3376/)
  * Reported by Cure53 (Pentest report 01.2017). 
* [3361: 0rigin DoS](/support/securitynotice/ntpbug3361/) / [CVE-2016-9042](https://nvd.nist.gov/vuln/detail/CVE-2016-9042)
  * Reported by Matthew Van Gundy of Cisco ASIG. 

ENotification of these issues were delivered to our Institutional members on a rolling basis as they were reported and as progress was made.

* * *

**Timeline:**

* 2017 Mar 21: Public release
* 2017 Mar 13: CERT notified 
* 2017 Mar 06: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2017 Mar 06: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2017 Feb 09: Mozilla/Cure53 audit received 