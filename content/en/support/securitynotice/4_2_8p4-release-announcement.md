---
title: "4.2.8p4 Release Announcement"
type: archives
date: "2015-10-21"
---

NTF's NTP Project has been notified of the following 13 low- and medium-severity vulnerabilities that are fixed in ntp-4.2.8p4, released on Wednesday, 21 October 2015:

* [2941: NAK to the Future: Symmetric association authentication bypass via crypto-NAK](/support/securitynotice/ntpbug2941) / [CVE-2015-7871](https://nvd.nist.gov/vuln/detail/CVE-2015-7871) (Cisco ASIG) 
* [2922: decodenetnum() will ASSERT botch instead of returning FAIL on some bogus values](/support/securitynotice/ntpbug2922) / [CVE-2015-7855](https://nvd.nist.gov/vuln/detail/CVE-2015-7855) (IDA)
* [2921: Password Length Memory Corruption Vulnerability](/support/securitynotice/ntpbug2921) / [CVE-2015-7854](https://nvd.nist.gov/vuln/detail/CVE-2015-7854) (Cisco TALOS)
* [2920: Invalid length data provided by a custom refclock driver could cause a buffer overflow](/support/securitynotice/ntpbug2920) / [CVE-2015-7853](https://nvd.nist.gov/vuln/detail/CVE-2015-7853) (Cisco TALOS)
* [2919: ntpq atoascii() Memory Corruption Vulnerability](/support/securitynotice/ntpbug2919) / [CVE-2015-7852](https://nvd.nist.gov/vuln/detail/CVE-2015-7852) (Cisco TALOS)
* [2918: saveconfig Directory Traversal Vulnerability](/support/securitynotice/ntpbug2918) / [CVE-2015-7851](https://nvd.nist.gov/vuln/detail/CVE-2015-7851) (OpenVMS) (Cisco TALOS)
* [2917: remote config logfile-keyfile](/support/securitynotice/ntpbug2917) / [CVE-2015-7850](https://nvd.nist.gov/vuln/detail/CVE-2015-7850) (Cisco TALOS)
* [2916: trusted key use-after-free](/support/securitynotice/ntpbug2916) / [CVE-2015-7849](https://nvd.nist.gov/vuln/detail/CVE-2015-7849) (Cisco TALOS)
* [2913: mode 7 loop counter underrun](/support/securitynotice/ntpbug2913) / [CVE-2015-7848](https://nvd.nist.gov/vuln/detail/CVE-2015-7848) (Cisco TALOS)
* [2909:Slow memory leak in CRYPTO_ASSOC](/support/securitynotice/ntpbug2909) / [CVE-2015-7701](https://nvd.nist.gov/vuln/detail/CVE-2015-7701) (Tenable)
* [2902: configuration directives "pidfile" and "driftfile" should only be allowed locally](/support/securitynotice/ntpbug2902) / [CVE-2015-7703](https://nvd.nist.gov/vuln/detail/CVE-2015-7703) (RedHat)
* [2901: Clients that receive a KoD should validate the origin timestamp field](/support/securitynotice/ntpbug2901) / [CVE-2015-7704](https://nvd.nist.gov/vuln/detail/CVE-2015-7704), [CVE-2015-7705](https://nvd.nist.gov/vuln/detail/CVE-2015-7705) (Boston University)
* [2899: Incomplete autokey data packet length checks](/support/securitynotice/ntpbug2899) / [CVE-2015-7691](https://nvd.nist.gov/vuln/detail/CVE-2015-7691), [CVE-2015-7692](https://nvd.nist.gov/vuln/detail/CVE-2015-7692), [CVE-2015-7702](https://nvd.nist.gov/vuln/detail/CVE-2015-7702) (Tenable) 

The only generally-exploitable bug in the above list is the crypto-NAK bug, which has a CVSS2 score of 6.4.

Additionally, three bugs that have already been fixed in ntp-4.2.8 but were not fixed in ntp-4.2.6 as it was EOL'd have a security component, but are all below 1.8 CVSS score, so we're reporting them here:

* [2382: Peer precision < -31 gives division by zero](https://bugs.ntp.org/show_bug.cgi?id=2382) 
* [1774: Segfaults if cryptostats enabled when built without OpenSSL](https://bugs.ntp.org/show_bug.cgi?id=1774) 
* [1593: ntpd abort in free() with logconfig syntax error](https://bugs.ntp.org/show_bug.cgi?id=1593)  

* * *

**Timeline:**

* 2015 Oct 21: Public release
* 2015 Oct 20: CERT & Mitre updated with final drafts of announcement
* 2015 Oct 19: NAK bug addition and new CVE#s announced to CERT
* 2015 Oct 17: Advance notification of NAK bug being added was sent to Institutional members
* 2015 Oct 14: pre-release patch availability announced to CERT
* 2015 Oct 9: notification of public release date change to 21 Oct sent to members and reporters and Mitre
* 2015 Oct 6: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits)
* 2015 Aug 26: Initial notification of [2909](/support/securitynotice/ntpbug2909); analysis begins
* 2015 Aug 26: CVE number clarification requested from Mitre
* 2015 Aug 26: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits) for [1593](https://bugs.ntp.org/show_bug.cgi?id=1593), [1774](https://bugs.ntp.org/show_bug.cgi?id=1774), [2382](https://bugs.ntp.org/show_bug.cgi?id=2382), [2899](/support/securitynotice/ntpbug2899), and [2902](/support/securitynotice/ntpbug2902)
* 2015 Aug 20: Initial notification of [2902](/support/securitynotice/ntpbug2902); analysis begins
* 2015 Aug 11: Initial notification of [2899](/support/securitynotice/ntpbug2899); analysis begins