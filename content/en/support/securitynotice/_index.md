---
title: Security
type: archives
---

#### Table of Contents

* [Notification Policy](#notification-policy)
* [Security Patch Policy](#security-patch-policy)
* [Reporting Security Issues](#reporting-security-issues)
* [Recent Vulnerabilities](#recent-vulnerabilities)
* [Older Resolved Issues](#older-resolved-issues)

#### Notification Policy

When we discover a security vulnerability in NTP we follow our Phased Vulnerability Process which includes first notifying Institutional members of the [NTP Consortium at Network Time Foundation](https://www.nwtime.org/membership/), then [CERT](https://www.sei.cmu.edu/about/divisions/cert/index.cfm), and finally making a public announcement.

> [Institutional Members](https://www.nwtime.org/membership/benefits/#institutional-consortia-memberships) receive advanced notification of security vulnerabilities.

* * *

#### Security Patch Policy

When security patches are ready, they are first given to Premier and Partner Institutional members of the [NTP Consortium at Network Time Foundation](https://www.nwtime.org/membership/), then access instructions are provided to [CERT](https://www.sei.cmu.edu/about/divisions/cert/index.cfm), and finally the public release is made on the embargo date.

> [Premier and Partner Members](https://www.nwtime.org/membership/benefits/#institutional-consortia-memberships) receive early access to security patches.

* * *

#### Reporting Security Issues

**Security related bugs, confirmed or suspected, are to be reported by email to [security@ntp.org](mailto:security@ntp.org).**

**Do not disclose details with unencrypted email. We will exchange PGP keys for further discussion.**

You can use our [NTP Security Officer Key](/downloads/NTPSecKey0x0066B2FD.txt) for reporting issues you have verified as security-related.

Please refrain from discussing potential security issues in public fora such as [comp.protocols.time.ntp](https://groups.google.com/g/comp.protocols.time.ntp), our Bug Tracking system, bugs@ntp.org, or any mailing list.

* * *

#### Recent Vulnerabilities

| Security Issue | Severity |  Fixed In | Advance Notification | Advance Release | Public Release |
| -------------- | -------- |  -------- | -------------------- | --------------- | -------------- |
| [3661: Memory leak with CMAC keys](/support/securitynotice/ntpbug3661) | <span style="color:orange">MEDIUM</span> | [4.2.8p15](/support/securitynotice/4_2_8p15-release-announcement) | 2020<br> Apr 07 | 2020<br> Apr 12 | 2020<br> Jun 23 |
| [3610:  <code>process_control()</code> should bail earlier on short packets ](/support/securitynotice/ntpbug3610) | <span style="color:green">NONE</span> | [4.2.8p14](/support/securitynotice/4_2_8p14-release-announcement) | 2019<br> Jun 05 | 2020<br> Feb 17 | 2020<br> Mar 03 |
| [3596: Unauthenticated and unmonitored <code>ntpd</code> may be susceptible to IPv4 attack from highly predictable transmit timestamps ](/support/securitynotice/ntpbug3596) | <span style="color:orange">MEDIUM</span> | [4.2.8p14](/support/securitynotice/4_2_8p14-release-announcement) | 2019<br> Jun 05 | 2020<br> Feb 17 | 2020<br> Mar 03 |
| [3592: DoS Attack on Unauthenticated Client](/support/securitynotice/ntpbug3592) | <span style="color:orange">MEDIUM</span> | [4.2.8p14](/support/securitynotice/4_2_8p14-release-announcement) | 2019<br> Jun 05 | 2020<br> Feb 17 | 2020<br> Mar 03 |
| [3565:  Crafted null dereference attack from a trusted source with an authenticated mode 6 packet ](/support/securitynotice/ntpbug3565) | <span style="color:orange">MEDIUM</span> | [4.2.8p13](/support/securitynotice/4_2_8p13-release-announcement) | 2019<br> Jan 16 | 2019<br> Feb 20 | 2019 Mar 07 |
| [3012:  Sybil vulnerability: ephemeral association attack ](/support/securitynotice/ntpbug3012p12)<br> [CVE-2016-1549](http://web.nvd.nist.gov/view/vuln/detail?vulnId=CVE-2016-1549) <br>[CVE-2018-7170](https://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE-2018-7170) | <span style="color:orange">LOW/MEDIUM</span> | [4.2.8p12](/support/securitynotice/4_2_8p12-release-announcement) | | 2018<br> Jul 25 | 2018<br> Aug 14 |
| [3505:  NTPQ/NTPDC: Buffer Overflow in <code>openhost()</code> ](/support/securitynotice/ntpbug3505)<br> [CVE-2018-12327](http://web.nvd.nist.gov/view/vuln/detail?vulnId=CVE-2018-12327)<br> | <span style="color:green">NONE</span> | [4.2.8p12](/support/securitynotice/4_2_8p12-release-announcement) | | 2018<br> Jul 25 | 2018<br> Aug 14 |
| [3012:  Sybil vulnerability: ephemeral association attack ](/support/securitynotice/ntpbug3012)<br> [CVE-2016-1549](http://web.nvd.nist.gov/view/vuln/detail?vulnId=CVE-2016-1549) <br>[VU#961909](http://www.kb.cert.org/vuls/id/961909) | <span style="color:orange">LOW/MEDIUM</span> | [4.2.8p11](/support/securitynotice/4_2_8p11-release-announcement) | | 2018<br> Jan 23 | 2018<br> Feb 27 |
| [3412: <code>ctl_getitem()</code>: buffer read overrun leads to undefined behavior and information leak](/support/securitynotice/ntpbug3412)<br> [CVE-2018-7182](http://web.nvd.nist.gov/view/vuln/detail?vulnId=CVE-2018-7182)<br> [VU#961909](http://www.kb.cert.org/vuls/id/961909) | <span style="color:orange">INFO/MEDIUM</span> | [4.2.8p11](/support/securitynotice/4_2_8p11-release-announcement) | | 2018<br> Jan 23 | 2018<br> Feb 27 |
| [3415:  Provide a way to prevent authenticated symmetric passive peering ](/support/securitynotice/ntpbug3415)<br> [CVE-2018-7170](http://web.nvd.nist.gov/view/vuln/detail?vulnId=CVE-2018-7170)<br> [VU#961909](http://www.kb.cert.org/vuls/id/961909) | <span style="color:green">LOW</span> | [4.2.8p11](/support/securitynotice/4_2_8p11-release-announcement) | | 2018<br> Jan 23 | 2018<br> Feb 27 |
| [3453:  Interleaved symmetric mode cannot recover from bad state ](/support/securitynotice/ntpbug3453)<br> [CVD-2018-7184]()<br> [VU#961909](http://www.kb.cert.org/vuls/id/961909) | <span style="color:green">LOW</span> | [4.2.8p11](/support/securitynotice/4_2_8p11-release-announcement) | | 2018<br> Jan 23 | 2018<br> Feb 27 |
| [3454:  Unauthenticated packet can reset authenticated interleaved association ](/support/securitynotice/ntpbug3454)<br> [CVE-2018-7185](http://web.nvd.nist.gov/view/vuln/detail?vulnId=CVE-2018-7185)<br> [VU#961909](http://www.kb.cert.org/vuls/id/961909) | <span style="color:orange">LOW/MEDIUM</span> | [4.2.8p11](/support/securitynotice/4_2_8p11-release-announcement) | | 2018<br> Jan 23 | 2018<br> Feb 27 |

* * *

#### Older Resolved Issues

| Security Issue | Severity | Fixed In | Public Release |
| -------------- | -------- | -------- | -------------- |
| [3414: <code>ntpq: decodearr()</code> can write beyond its 'buf' limits](/support/securitynotice/ntpbug3414) | <span style="color:orange">MEDIUM</span> | [4.2.8p11](/support/securitynotice/4_2_8p11-release-announcement) | 2018 Feb 27|
| [3389: Denial of Service via Malformed Config](/support/securitynotice/ntpbug3389) |<span style="color:orange">MEDIUM</span> | [4.2.8p10](/support/securitynotice/4_2_8p10-release-announcement) | 2017 Mar 21|
| [3388: Buffer Overflow in DPTS Clock](/support/securitynotice/ntpbug3388) | <span style="color:green">LOW</span> | [4.2.8p10](/support/securitynotice/4_2_8p10-release-announcement) | 2017 Mar 21|
| [3387: Authenticated DoS via Malicious Config Option](/support/securitynotice/ntpbug3387) | <span style="color:orange">MEDIUM</span>| [4.2.8p10](/support/securitynotice/4_2_8p10-release-announcement) | 2017 Mar 21|
| [3386: <code>ntpq_stripquotes()</code> returns incorrect value](/support/securitynotice/ntpbug3386) | <span style="color:green">INFO</span> | [4.2.8p10](/support/securitynotice/4_2_8p10-release-announcement) | 2017 Mar 21|
| [3385:  <code>ereallocarray() / eallocarray()</code> underused](/support/securitynotice/ntpbug3385) | <span style="color:green">INFO</span> | [4.2.8p10](/support/securitynotice/4_2_8p10-release-announcement) | 2017 Mar 21|
| [3384: Privileged execution of User Library code (Windows PPSAPI Only)](/support/securitynotice/ntpbug3384) | <span style="color:green">LOW</span> | [4.2.8p10](/support/securitynotice/4_2_8p10-release-announcement) | 2017 Mar 21|
| [3383: Stack Buffer Overflow from Command Line (Windows Installer Only)](/support/securitynotice/ntpbug3383) | <span style="color:green">LOW</span> | [4.2.8p10](/support/securitynotice/4_2_8p10-release-announcement) | 2017 Mar 21|
| [3382: Data Structure terminated insufficiently (Windows Installer Only)](/support/securitynotice/ntpbug3382) | <span style="color:green">LOW</span> | [4.2.8p10](/support/securitynotice/4_2_8p10-release-announcement) | 2017 Mar 21|
| [3381: Copious amounts of Unused Code](/support/securitynotice/ntpbug3381) | <span style="color:green">INFO</span>|[4.2.8p10](/support/securitynotice/4_2_8p10-release-announcement) | 2017 Mar 21|
| [3380: Off-by-one in Oncore GPS Receiver](/support/securitynotice/ntpbug3380) | <span style="color:green">LOW</span> | [4.2.8p10](/support/securitynotice/4_2_8p10-release-announcement) | 2017 Mar 21|
| [3379: Potential Overflows in <code>ctl_put()</code> functions](/support/securitynotice/ntpbug3379) | <span style="color:orange">MEDIUM</span>| [4.2.8p10](/support/securitynotice/4_2_8p10-release-announcement) | 2017 Mar 21|
| [3378: Improper use of <code>snprintf()</code> in <code>mx4200_send()</code>](/support/securitynotice/ntpbug3378) | <span style="color:green">LOW</span> | [4.2.8p10](/support/securitynotice/4_2_8p10-release-announcement) | 2017 Mar 21|
| [3377: Buffer Overflow in <code>ntpq</code> when fetching <code>reslist</code> from a malicious <code>ntpd</code>](/support/securitynotice/ntpbug3377) | <span style="color:orange">MEDIUM</span>| [4.2.8p10](/support/securitynotice/4_2_8p10-release-announcement) | 2017 Mar 21|
| [3376: <code>Makefile</code> does not enforce Security Flags](/support/securitynotice/ntpbug3376) | <span style="color:green">INFO</span> | [4.2.8p10](/support/securitynotice/4_2_8p10-release-announcement) | 2017 Mar 21|
| [3379: NTP: Potential Overflows in <code>ctl_put()</code> functions]
| [3361: 0rigin DoS](/support/securitynotice/ntpbug3361) | <span style="color:orange">MEDIUM</span>| [4.2.8p10](/support/securitynotice/4_2_8p10-release-announcement) | 2017 Mar 21|
| [3119: Mode 6 unauthenticated trap information disclosure and DDoS vector](/support/securitynotice/ntpbug3119) | <span style="color:orange">MEDIUM</span>| [4.2.8p9](/support/securitynotice/4_2_8p9-release-announcement) | 2016 Nov 21|
| [3118:  Mode 6 unauthenticated trap information disclosure and DDoS vector ](/support/securitynotice/ntpbug3118) | <span style="color:orange">MEDIUM</span>| [4.2.8p9](/support/securitynotice/4_2_8p9-release-announcement) | 2016 Nov 21|
| [3114:  Broadcast Mode Replay Prevention DoS ](/support/securitynotice/ntpbug3114) |<span style="color:orange">LOW/MEDIUM</span> |[4.2.8p9](/support/securitynotice/4_2_8p9-release-announcement) | 2016 Nov 21|
| [3113: Broadcast Mode Poll Interval Enforcement DoS](/support/securitynotice/ntpbug3113) |<span style="color:orange">LOW/MEDIUM</span> |[4.2.8p9](/support/securitynotice/4_2_8p9-release-announcement) | 2016 Nov 21|
| [3110: Windows: <code>ntpd</code> DoS by oversized UDP packet ](/support/securitynotice/ntpbug3110) |<span style="color:red">HIGH</span>|[4.2.8p9](/support/securitynotice/4_2_8p9-release-announcement) | 2016 Nov 21|
| [3102: Zero Origin timestamp regression ](/support/securitynotice/ntpbug3102) |<span style="color:orange">MEDIUM</span>| [4.2.8p9](/support/securitynotice/4_2_8p9-release-announcement) | 2016 Nov 21|
| [3082:  <code>read_mru_list()</code> does inadequate incoming packet checks ](/support/securitynotice/ntpbug3082) |<span style="color:green">LOW</span>|[4.2.8p9](/support/securitynotice/4_2_8p9-release-announcement) | 2016 Nov 21|
| [3072:  Attack on interface selection ](/support/securitynotice/ntpbug3072) |<span style="color:green">LOW</span>|[4.2.8p9](/support/securitynotice/4_2_8p9-release-announcement) | 2016 Nov 21|
| [3071:  Client rate limiting and server responses ](/support/securitynotice/ntpbug3071) |<span style="color:green">LOW</span>|[4.2.8p9](/support/securitynotice/4_2_8p9-release-announcement) | 2016 Nov 21|
| [3067:  Fix for bug 2085 broke initial sync calculations ](/support/securitynotice/ntpbug3067) |<span style="color:green">LOW</span>|[4.2.8p9](/support/securitynotice/4_2_8p9-release-announcement) | 2016 Nov 21|
| [3046:  <code>CRYPTO_NAK</code> crash ](/support/securitynotice/ntpbug3046) |<span style="color:red">HIGH</span>|[4.2.8p8](/support/securitynotice/4_2_8p8-release-announcement) | 2016 Jun 02|
| [3045:  Bad authentication demobilizes ephemeral associations ](/support/securitynotice/ntpbug3045) | <span style="color:green">LOW</span>|[4.2.8p8](/support/securitynotice/4_2_8p8-release-announcement) | 2016 Jun 02|
| [3044:  Processing spoofed server packets ](/support/securitynotice/ntpbug3044) |<span style="color:green">LOW</span>|[4.2.8p8](/support/securitynotice/4_2_8p8-release-announcement) | 2016 Jun 02|
| [3043:  Autokey association reset ](/support/securitynotice/ntpbug3043) |<span style="color:green">LOW</span>|[4.2.8p8](/support/securitynotice/4_2_8p8-release-announcement) | 2016 Jun 02|
| [3042:  Broadcast interleave ](/support/securitynotice/ntpbug3042) | <span style="color:green">LOW</span>|[4.2.8p8](/support/securitynotice/4_2_8p8-release-announcement) | 2016 Jun 02|
| [3020:  Refclock impersonation vulnerability ](/support/securitynotice/ntpbug3020) | <span style="color:green">LOW</span>|[4.2.8p7](/support/securitynotice/4_2_8p7-release-announcement) | 2016 Apr 26|
| [3011:  Duplicate IPs on unconfig directives will cause an assertion botch in <code>ntpd</code>](/support/securitynotice/ntpbug3011) |<span style="color:orange">MEDIUM</span>|[4.2.8p7](/support/securitynotice/4_2_8p7-release-announcement) | 2016 Apr 26|
| [3010:  remote configuration trustedkey/requestkey/controlkey values are not properly validated ](/support/securitynotice/ntpbug3010) |<span style="color:orange">MEDIUM</span>|[4.2.8p7](/support/securitynotice/4_2_8p7-release-announcement) | 2016 Apr 26|
| [3009:  Crafted <code>addpeer</code> with <code>hmode</code> > 7 causes array wraparound with <code>MATCH_ASSOC</code> ](/support/securitynotice/ntpbug3009) |<span style="color:green">LOW</span>|[4.2.8p7](/support/securitynotice/4_2_8p7-release-announcement) | 2016 Apr 26|
| [3008:  <code>ctl_getitem()</code> return value not always checked ](/support/securitynotice/ntpbug3008) |<span style="color:orange">MEDIUM</span>|[4.2.8p7](/support/securitynotice/4_2_8p7-release-announcement) | 2016 Apr 26|
| [3007:  <code>CRYPTO-NAK</code> DoS ](/support/securitynotice/ntpbug3007) |<span style="color:orange">MEDIUM/LOW</span>|[4.2.8p7](/support/securitynotice/4_2_8p7-release-announcement) | 2016 Apr 26|
| [2978: Interleave-pivot ](/support/securitynotice/ntpbug2978) |<span style="color:orange">MEDIUM</span>|[4.2.8p7](/support/securitynotice/4_2_8p7-release-announcement) | 2016 Apr 26|
| [2952: Original fix for NTP Bug 2901 broke peer associations](/support/securitynotice/ntpbug2952) ||[4.2.8p7](/support/securitynotice/4_2_8p7-release-announcement) | 2016 Apr 26|
| [2946: Origin Leak: <code>ntpq</code> and <code>ntpdc</code> Disclose Origin Timestamp to Unauthenticated Clients](/support/securitynotice/ntpbug2946) |<span style="color:orange">MEDIUM</span>|[4.2.8p7](/support/securitynotice/4_2_8p7-release-announcement) | 2016 Apr 26|
| [2879: Improve NTP security against buffer comparison timing attacks](/support/securitynotice/ntpbug2879) |<span style="color:orange">LOW/MEDIUM</span>|[4.2.8p7](/support/securitynotice/4_2_8p7-release-announcement) | 2016 Apr 26|
| [2948: Potential Infinite Loop in <code>ntpq</code>](/support/securitynotice/ntpbug2948) |<span style="color:orange">MEDIUM</span>|[4.2.8p6](/support/securitynotice/4_2_8p6-release-announcement) | 2016 Jan 19|
| [2947: <code>ntpq</code> protocol vulnerable to replay attacks](/support/securitynotice/ntpbug2947) |<span style="color:orange">MEDIUM</span>|[4.2.8p6](/support/securitynotice/4_2_8p6-release-announcement) | 2016 Jan 19|
| [2945: 0rigin: Zero Origin Timestamp Bypass](/support/securitynotice/ntpbug2945) |<span style="color:orange">MEDIUM</span>|[4.2.8p6](/support/securitynotice/4_2_8p6-release-announcement) | 2016 Jan 19|
| [2942: Off-path Denial of Service (DoS) attack on authenticated broadcast mode](/support/securitynotice/ntpbug2942) |<span style="color:orange">MEDIUM</span>|[4.2.8p6](/support/securitynotice/4_2_8p6-release-announcement) | 2016 Jan 19|
| [2940: Stack exhaustion in recursive traversal of restriction list](/support/securitynotice/ntpbug2940) |<span style="color:orange">MEDIUM</span>|[4.2.8p6](/support/securitynotice/4_2_8p6-release-announcement) | 2016 Jan 19|
| [2939: <code>reslist</code> NULL pointer dereference](/support/securitynotice/ntpbug2939) |<span style="color:orange">MEDIUM</span>|[4.2.8p6](/support/securitynotice/4_2_8p6-release-announcement) | 2016 Jan 19|
| [2938: <code>ntpq saveconfig</code> command allows dangerous characters in filenames](/support/securitynotice/ntpbug2938) |<span style="color:orange">MEDIUM</span>|[4.2.8p6](/support/securitynotice/4_2_8p6-release-announcement) | 2016 Jan 19|
| [2937: <code>nextvar()</code> missing length check in <code>ntpq</code>](/support/securitynotice/ntpbug2937) |<span style="color:green">LOW</span>|[4.2.8p6](/support/securitynotice/4_2_8p6-release-announcement) | 2016 Jan 19|
| [2936: Skeleton Key: Any trusted key system can serve time ](/support/securitynotice/ntpbug2936) |<span style="color:red">HIGH</span>|[4.2.8p6](/support/securitynotice/4_2_8p6-release-announcement) | 2016 Jan 19|
| [2935: Deja Vu: Replay attack on authenticated broadcast mode](/support/securitynotice/ntpbug2935) |<span style="color:orange">MEDIUM</span>|[4.2.8p6](/support/securitynotice/4_2_8p6-release-announcement) | 2016 Jan 19|
| [2956: Small-step/big-step](/support/securitynotice/ntpbug2956) |<span style="color:orange">MEDIUM</span>|[4.2.8p5](/support/securitynotice/4_2_8p5-release-announcement) | 2016 Jan 07|
| [2941: NAK to the Future: Symmetric association authentication bypass via crypto-NAK](/support/securitynotice/ntpbug2941) |<span style="color:green">LOW</span>|[4.2.8p4](/support/securitynotice/4_2_8p4-release-announcement) | 2015 Oct 21|
| [2922: <code>decodenetnum()</code> will ASSERT botch instead of returning FAIL on some bogus values](/support/securitynotice/ntpbug2922) |<span style="color:red">HIGH</span>|[4.2.8p4](/support/securitynotice/4_2_8p4-release-announcement) | 2015 Oct 21|
| [2921: TALOS-CAN-0065: Password Length Memory Corruption Vulnerability](/support/securitynotice/ntpbug2921) |<span style="color:red">HIGH</span>|[4.2.8p4](/support/securitynotice/4_2_8p4-release-announcement) | 2015 Oct 21|
| [2920: TALOS-CAN-0064: Invalid length data provided by a custom refclock driver could cause a buffer overflow](/support/securitynotice/ntpbug2920) |<span style="color:red">HIGH</span>|[4.2.8p4](/support/securitynotice/4_2_8p4-release-announcement) | 2015 Oct 21|
| [2919: TALOS-CAN-0063: <code>ntpq atoascii()</code> potential memory corruption](/support/securitynotice/ntpbug2919) |<span style="color:red">HIGH</span>|[4.2.8p4](/support/securitynotice/4_2_8p4-release-announcement) | 2015 Oct 21|
| [2918: TALOS-CAN-0062: Potential path traversal vulnerability in the config file saving of <code>ntpd</code> on VMS](/support/securitynotice/ntpbug2918) |<span style="color:red">HIGH</span>|[4.2.8p4](/support/securitynotice/4_2_8p4-release-announcement) | 2015 Oct 21|
| [2917: TALOS-CAN-0055: Infinite loop if extended logging enabled and the logfile and keyfile are the same](/support/securitynotice/ntpbug2917) |<span style="color:red">HIGH</span>|[4.2.8p4](/support/securitynotice/4_2_8p4-release-announcement) | 2015 Oct 21|
| [2916: TALOS-CAN-0054: memory corruption in password store](/support/securitynotice/ntpbug2916) |<span style="color:red">HIGH</span>|[4.2.8p4](/support/securitynotice/4_2_8p4-release-announcement) | 2015 Oct 21|
| [2913: TALOS-CAN-0052: mode 7 loop counter underrun](/support/securitynotice/ntpbug2913) |<span style="color:red">HIGH</span>|[4.2.8p4](/support/securitynotice/4_2_8p4-release-announcement) | 2015 Oct 21|
| [2909: Slow memory leak in <code>CRYPTO_ASSOC</code>](/support/securitynotice/ntpbug2909) |<span style="color:red">HIGH</span>|[4.2.8p4](/support/securitynotice/4_2_8p4-release-announcement) | 2015 Oct 21|
| [2902: Configuration directives to change "pidfile" and "driftfile" should only be allowed locally](/support/securitynotice/ntpbug2902) |<span style="color:red">HIGH</span>|[4.2.8p4](/support/securitynotice/4_2_8p4-release-announcement) | 2015 Oct 21|
| [2901: Clients that receive a KoD should validate the origin timestamp field](/support/securitynotice/ntpbug2901) |<span style="color:orange">MEDIUM</span>|[4.2.8p4](/support/securitynotice/4_2_8p4-release-announcement) | 2015 Oct 21|
| [2899: Incomplete autokey data packet length checks](/support/securitynotice/ntpbug2899) |<span style="color:red">HIGH</span>|[4.2.8p4](/support/securitynotice/4_2_8p4-release-announcement) | 2015 Oct 21|
| [2382: Peer precision < -31 gives division by zero](/support/securitynotice/ntpbug2382) |<span style="color:red">HIGH</span>|[4.2.8p4](/support/securitynotice/4_2_8p4-release-announcement) | 2015 Oct 21|
| [2671: <code>vallen</code> is not validated in several places in <code>ntp_crypto.c</code>, leading to a potential info leak or possibly crashing <code>ntpd</code>](/support/securitynotice/ntpbug2671) |<span style="color:green">LOW</span>|[4.2.8p1](/support/securitynotice/4_2_8p1-release-announcement) | 2015 Feb 04|
| [1774: <code>ntpd</code> segfaults if <code>cryptostats</code> enabled when built without OpenSSL](/support/securitynotice/ntpbug1774) |<span style="color:red">HIGH</span>|4.2.8-stable | 2014 Dec 19|
| [1593: <code>ntpd</code> abort in <code>free()</code> with logconfig syntax error](/support/securitynotice/ntpbug1593) |<span style="color:red">HIGH</span>|4.2.8-stable | 2014 Dec 19|