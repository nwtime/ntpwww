---
title: "4.2.8p1 Release Announcement"
type: archives
date: "2015-02-04"
---

NTF's NTP Project has been notified of a number of vulnerabilities from Neel Mehta and Stephen Roettger of Google's Security Team.

The two most serious of these issues and four less serious issues have been resolved as of [ntp-4.2.8](/support/securitynotice/4_2_8-release-announcement/), which was released on 18 December 2014.

The remaining two issues are addressed by 4.2.8p1, which was released on 4 February 2015.

* [2671: vallen is not validated in several places in ntp_crypto.c, leading to a potential info leak or possibly crashing ntpd](/support/securitynotice/ntpbug2671/) / [CVE-2014-9297](https://nvd.nist.gov/vuln/detail/CVE-2014-9297/)
* [2672: ::1 can be spoofed on some OSes, so ACLs based on IPv6 ::1 addresses can be bypassed](/support/securitynotice/ntpbug2672/) / [CVE-2014-9298](https://nvd.nist.gov/vuln/detail/CVE-2014-9298/)

These are the vulnerabilities from Neel Mehta and Stephen Roettger of Google's Security Team:

* We have been generating a weak default key if no authentication key is defined in the `ntp.conf` file.
* `ntp-keygen` before 4.2.7p230 used a non-cryptographic random number generator with a weak seed to generate symmetric keys.
* It's possible to overflow a stack buffer in `crypto_recv()` when using autokey and potentially allow malicious code to be executed with the privilege level of the `ntpd` process.
* It's possible to overflow a buffer in `ctl_putdata()` and potentially allow malicious code to be executed with the privilege level of the `ntpd` process.
* It's possible to overflow a buffer in `configure()` and potentially allow malicious code to be executed with the privilege level of the `ntpd` process.
* A missing `return;` in a rare error condition case in `ntp_proto.c:receive()` will cause a temporary association to become mobilized. While we haven't yet found a way this can be exploited, an exploit might be possible.
* In several places, the `vallen` packet value in `ntp_crypto.c` is not validated, which can lead to information leakage.
* If ::1 is spoofed on some OSes, the packet is processed instead of being dropped, so ACLs based on IPv6 ::1 addresses can be bypassed. This could allow an attacker to tell your `ntpd` to, among other things, reconfigure itself. 

Additionally, we are working to patch the known deficiencies in NTP's Autokey protocol, as a stop-gap measure until the Network Time Security draft (which will replace Autokey) is ready to be deployed. These weaknesses were discovered by Dieter Sibold, PhD of PTB, and Stephen Roettger of the Google Security Team. 

* * *

**Timeline:**

* 2015 Feb 4: Public release
* : [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits)
* : [Notification to Institutional Members](https://www.nwtime.org/membership/benefits)
* : Initial notification received; analysis begins