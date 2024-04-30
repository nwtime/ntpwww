---
title: Security
description: "NTP security vulnerability notification policy, security patch policy, how to report a security issue, and the archive of known vulnerabilities by release version."
type: archives
---

<div>
  <div class="container">
    <div class="row row-cols-1 row-cols-sm-3 row-cols-md-3 g-3">
      <div class="col">
        <div class="card mh-100">
          <div class="card-body">
		    <h5 class="card-text" style="text-align: center; margin-top: 10px;">Notification Policy</h5>
            <p>When we discover a security vulnerability in NTP we follow our Phased Vulnerability Process which includes first notifying Institutional members of the <a href="https://www.nwtime.org/membership/benefits/">NTP Consortium at Network Time Foundation</a>, then <a href="https://www.sei.cmu.edu/about/divisions/cert/index.cfm">CERT</a>, and finally making a public announcement.</p>
            <p style="text-align: center;"><a href="https://www.nwtime.org/membership/benefits/#institutional-consortia-memberships">Institutional Members</a> receive advanced notification of security vulnerabilities.</p><br><br><br><br>
              <div class="d-flex justify-content-between align-items-center">
            </div>
          </div>
        </div>
      </div>
      <div class="col">
        <div class="card mh-100">
          <div class="card-body">
		    <h5 class="card-text" style="text-align: center; margin-top: 10px;">Security Patch Policy</h5>
            <p>When security patches are ready, they are first given to Premier and Partner Institutional members of the <a href="https://www.nwtime.org/membership/benefits/">NTP Consortium at Network Time Foundation</a>, then access instructions are provided to <a href="https://www.sei.cmu.edu/about/divisions/cert/index.cfm">CERT</a>, and finally the public release is made on the embargo date.</p>
            <p style="text-align: center;"><a href="https://www.nwtime.org/membership/benefits/#institutional-consortia-memberships">Premier and Partner Members</a> receive early access to security patches.</p><br><br><br><br>
              <div class="d-flex justify-content-between align-items-center">
            </div>
          </div>
        </div>
      </div>
      <div class="col">
	    <div class="card mh-100">
          <div class="card-body">
		    <h5 class="card-text" style="text-align: center; margin-top: 10px;">Reporting Security Issues</h5>
            <p class="card-text">If you find a security vulnerability in the NTP codebase, please report it by <b>PGP-encrypted</b> email to the NTF Security Officer Team. You can use our <a href="https://www.nwtime.org/about/documents/NTFSecurityOfficerPGPKey.txt">NTF Security Officer PGP Key</a>. Please refrain from discussing potential security issues in any mailing lists or public forums.</p>
			<p><b>NOTE:</b> Non-code vulnerabilities (such as a website issue) should instead be reported to <a href="mailto:webmaster@nwtime.org">webmaster.</a> Issues for subdomains of "pool.ntp.org" should be reported to the <a href="https://www.ntppool.org/en/mailinglists.html">NTP Pool Project</a>.</p>		
              <div class="d-flex justify-content-between align-items-center">
			</div>
          </div>
        </div>
      </div>
	</div>
  </div>
</div>

***

#### Known Vulnerabilities by Release Version

The following releases provided fixes for at least one security vulnerability. The table for each release provides an entry for each security issue (click its hyperlink to read the details for the vulnerability), indicates the issue's severity, and provides the dates of advance notification to institutional members, advance release to premier and partner institutional members, and public release.

Refer to the [Release Timeline](/dev/releasetimeline/) for a complete list of all releases, their public release dates, release announcements, and changelogs.

<details open>
<summary><strong>Release Version:</strong></summary>

* [4.2.8p16](#428p16)
* [4.2.8p15](#428p15)
* [4.2.8p14](#428p14)
* [4.2.8p13](#428p13)
* [4.2.8p12](#428p12)
* [4.2.8p11](#428p11)
* [4.2.8p10](#428p10)
* [4.2.8p9](#428p9)
* [4.2.8p8](#428p8)
* [4.2.8p7](#428p7)
* [4.2.8p6](#428p6)
* [4.2.8p5](#428p5)
* [4.2.8p4](#428p4)
* [4.2.8p3](#428p3)
* [4.2.8p2](#428p2)
* [4.2.8p1](#428p1)
* [4.2.8](#428)
* [4.2.7p230](#427p230)
* [4.2.7p26](#427p26)
* [4.2.7p11](#427p11)
* [4.2.6](#426)
* [4.2.4p7](#424p7)
* [4.2.4p5](#424p5)

</details>

* * *

#### 4.2.8p16

* Advance Release:  2023 May 10
* Public Release: 2023 May 30 

| Security Issue | Severity |
| -------------- | -------- |
| [3808: ntpq will abort with an assertion failure given a malformed RT-11 date ](/support/securitynotice/ntpbug3808/) | NONE |
| [3807: praecis_parse() in ntpd/refclock_palisade.c can write out-of-bounds](/support/securitynotice/ntpbug3807/) | <span style="color:green">LOW</span> |
| [3806: libntp/mstolfp() needs bounds checking ](/support/securitynotice/ntpbug3806/) | <span style="color:green">LOW</span> |
| [3767: An out-of-bounds KoD RATE ppoll value triggers an assertion abort in debug-enabled ntpd](/support/securitynotice/ntpbug3767/) | <span style="color:green">LOW</span> |

* * *

#### 4.2.8p15

* Advance Notification: 2020 Apr 07
* Advance Release: 2020 Apr 12
* Public Release: 2020 Jun 23

| Security Issue | Severity |
| -------------- | -------- |
| [3661: Memory leak with CMAC keys](/support/securitynotice/ntpbug3661/) | <span style="color:orange">MEDIUM</span> |

* * *

#### 4.2.8p14

* Advance Notification: 2019 Jun 05
* Advance Release: 2020 Feb 17
* Public Release: 2020 Mar 03

| Security Issue | Severity |
| -------------- | -------- |
| [3610:  <code>process_control()</code> should bail earlier on short packets ](/support/securitynotice/ntpbug3610/) | <span style="color:green">NONE</span> |
| [3596: Unauthenticated and unmonitored <code>ntpd</code> may be susceptible to IPv4 attack from highly predictable transmit timestamps ](/support/securitynotice/ntpbug3596/) | <span style="color:orange">MEDIUM</span> |
| [3592: DoS Attack on Unauthenticated Client](/support/securitynotice/ntpbug3592/) | <span style="color:orange">MEDIUM</span> |

* * *

#### 4.2.8p13

* Advance Notification: 2019 Jan 16
* Advance Release: 2019 Feb 20
* Public Release: 2019 Mar 07

| Security Issue | Severity |
| -------------- | -------- |
| [3565:  Crafted null dereference attack from a trusted source with an authenticated mode 6 packet ](/support/securitynotice/ntpbug3565/) | <span style="color:orange">MEDIUM</span> |

* * *

#### 4.2.8p12

* Advance Release: 2018 Jul 25
* Public Release: 2018 Aug 14

| Security Issue | Severity |
| -------------- | -------- |
| [3505:  NTPQ/NTPDC: Buffer Overflow in <code>openhost()</code> ](/support/securitynotice/ntpbug3505/) | <span style="color:green">LOW</span> | |  | |
| [3012:  Sybil vulnerability: ephemeral association attack ](/support/securitynotice/ntpbug3012p12/) | <span style="color:orange">LOW/MEDIUM</span> | | | |


* * *

#### 4.2.8p11

* Advance Notification: 2018 Jan 23
* Advance Release: 2018 Feb 12
* Public Release: 2018 Feb 27

| Security Issue | Severity |
| -------------- | -------- |
| [3454:  Unauthenticated packet can reset authenticated interleaved association ](/support/securitynotice/ntpbug3454/) | <span style="color:orange">LOW/MEDIUM</span> |
| [3453:  Interleaved symmetric mode cannot recover from bad state ](/support/securitynotice/ntpbug3453/) | <span style="color:green">LOW</span> |
| [3415:  Provide a way to prevent authenticated symmetric passive peering ](/support/securitynotice/ntpbug3415/) | <span style="color:green">LOW</span> |
| [3414: <code>ntpq: decodearr()</code> can write beyond its 'buf' limits](/support/securitynotice/ntpbug3414/) | <span style="color:orange">MEDIUM</span> |
| [3412: <code>ctl_getitem()</code>: buffer read overrun leads to undefined behavior and information leak](/support/securitynotice/ntpbug3412/) | <span style="color:orange">INFO/MEDIUM</span> |
| [3012:  Sybil vulnerability: ephemeral association attack ](/support/securitynotice/ntpbug3012/) | <span style="color:orange">LOW/MEDIUM</span> |

* * *

#### 4.2.8p10

* Public Release: 2017 Mar 21

| Security Issue | Severity |
| -------------- | -------- |
| [3389: Denial of Service via Malformed Config](/support/securitynotice/ntpbug3389/) |<span style="color:orange">MEDIUM</span> |
| [3388: Buffer Overflow in DPTS Clock](/support/securitynotice/ntpbug3388/) | <span style="color:green">LOW</span> |
| [3387: Authenticated DoS via Malicious Config Option](/support/securitynotice/ntpbug3387/) | <span style="color:orange">MEDIUM</span>|
| [3386: <code>ntpq_stripquotes()</code> returns incorrect value](/support/securitynotice/ntpbug3386/) | <span style="color:green">INFO</span> |
| [3385:  <code>ereallocarray() / eallocarray()</code> underused](/support/securitynotice/ntpbug3385/) | <span style="color:green">INFO</span> |
| [3384: Privileged execution of User Library code (Windows PPSAPI Only)](/support/securitynotice/ntpbug3384/) | <span style="color:green">LOW</span> |
| [3383: Stack Buffer Overflow from Command Line (Windows Installer Only)](/support/securitynotice/ntpbug3383/) | <span style="color:green">LOW</span> |
| [3382: Data Structure terminated insufficiently (Windows Installer Only)](/support/securitynotice/ntpbug3382/) | <span style="color:green">LOW</span> |
| [3381: Copious amounts of Unused Code](/support/securitynotice/ntpbug3381/) | <span style="color:green">INFO</span>|
| [3380: Off-by-one in Oncore GPS Receiver](/support/securitynotice/ntpbug3380/) | <span style="color:green">LOW</span> |
| [3379: Potential Overflows in <code>ctl_put()</code> functions](/support/securitynotice/ntpbug3379/) | <span style="color:orange">MEDIUM</span>|
| [3378: Improper use of <code>snprintf()</code> in <code>mx4200_send()</code>](/support/securitynotice/ntpbug3378/) | <span style="color:green">LOW</span> |
| [3377: Buffer Overflow in <code>ntpq</code> when fetching <code>reslist</code> from a malicious <code>ntpd</code>](/support/securitynotice/ntpbug3377/) | <span style="color:orange">MEDIUM</span>|
| [3376: <code>Makefile</code> does not enforce Security Flags](/support/securitynotice/ntpbug3376/) | <span style="color:green">INFO</span> |
| [3361: 0rigin DoS](/support/securitynotice/ntpbug3361/) | <span style="color:orange">MEDIUM</span>|

* * *

#### 4.2.8p9

* Public Release: 2016 Nov 21

| Security Issue | Severity |
| -------------- | -------- |
| [3119: Mode 6 unauthenticated trap information disclosure and DDoS vector](/support/securitynotice/ntpbug3119/) | <span style="color:orange">MEDIUM</span>|
| [3118:  Mode 6 unauthenticated trap information disclosure and DDoS vector ](/support/securitynotice/ntpbug3118/) | <span style="color:orange">MEDIUM</span>|
| [3114:  Broadcast Mode Replay Prevention DoS ](/support/securitynotice/ntpbug3114/) |<span style="color:orange">LOW/MEDIUM</span> |
| [3113: Broadcast Mode Poll Interval Enforcement DoS](/support/securitynotice/ntpbug3113/) |<span style="color:orange">LOW/MEDIUM</span> |
| [3110: Windows: <code>ntpd</code> DoS by oversized UDP packet ](/support/securitynotice/ntpbug3110/) |<span style="color:red">HIGH</span>|
| [3102: Zero Origin timestamp regression ](/support/securitynotice/ntpbug3102/) |<span style="color:orange">MEDIUM</span>|
| [3082:  <code>read_mru_list()</code> does inadequate incoming packet checks ](/support/securitynotice/ntpbug3082/) |<span style="color:green">LOW</span>|
| [3072:  Attack on interface selection ](/support/securitynotice/ntpbug3072/) |<span style="color:green">LOW</span>|
| [3071:  Client rate limiting and server responses ](/support/securitynotice/ntpbug3071/) |<span style="color:green">LOW</span>|
| [3067:  Fix for bug 2085 broke initial sync calculations ](/support/securitynotice/ntpbug3067/) |<span style="color:green">LOW</span>|

* * *

#### 4.2.8p8

Public Release: 2016 Jun 02

| Security Issue | Severity |
| -------------- | -------- |
| [3046:  <code>CRYPTO_NAK</code> crash ](/support/securitynotice/ntpbug3046/) |<span style="color:red">HIGH</span>|
| [3045:  Bad authentication demobilizes ephemeral associations ](/support/securitynotice/ntpbug3045/) | <span style="color:green">LOW</span>|
| [3044:  Processing spoofed server packets ](/support/securitynotice/ntpbug3044/) |<span style="color:green">LOW</span>|
| [3043:  Autokey association reset ](/support/securitynotice/ntpbug3043/) |<span style="color:green">LOW</span>|
| [3042:  Broadcast interleave ](/support/securitynotice/ntpbug3042/) | <span style="color:green">LOW</span>|

* * *

#### 4.2.8p7

* Public Release: 2016 Apr 26

| Security Issue | Severity |
| -------------- | -------- |
| [3020:  Refclock impersonation vulnerability ](/support/securitynotice/ntpbug3020/) | <span style="color:green">LOW</span>|
| [3011:  Duplicate IPs on unconfig directives will cause an assertion botch in <code>ntpd</code>](/support/securitynotice/ntpbug3011/) |<span style="color:orange">MEDIUM</span>|
| [3010:  remote configuration trustedkey/requestkey/controlkey values are not properly validated ](/support/securitynotice/ntpbug3010/) |<span style="color:orange">MEDIUM</span>|
| [3009:  Crafted <code>addpeer</code> with <code>hmode</code> > 7 causes array wraparound with <code>MATCH_ASSOC</code> ](/support/securitynotice/ntpbug3009/) |<span style="color:green">LOW</span>|
| [3008:  <code>ctl_getitem()</code> return value not always checked ](/support/securitynotice/ntpbug3008/) |<span style="color:orange">MEDIUM</span>|
| [3007:  <code>CRYPTO-NAK</code> DoS ](/support/securitynotice/ntpbug3007/) |<span style="color:orange">MEDIUM/LOW</span>|
| [2978: Interleave-pivot ](/support/securitynotice/ntpbug2978/) |<span style="color:orange">MEDIUM</span>|
| [2952: Original fix for NTP Bug 2901 broke peer associations](/support/securitynotice/ntpbug2952/) |<span style="color:orange">MEDIUM</span>|
| [2946: Origin Leak: <code>ntpq</code> and <code>ntpdc</code> Disclose Origin Timestamp to Unauthenticated Clients](/support/securitynotice/ntpbug2946/) |<span style="color:orange">MEDIUM</span>|
| [2879: Improve NTP security against buffer comparison timing attacks](/support/securitynotice/ntpbug2879/) |<span style="color:orange">LOW/MEDIUM</span>|

* * *

#### 4.2.8p6

* Public Release: 2016 Jan 19

| Security Issue | Severity |
| -------------- | -------- |
| [2948: Potential Infinite Loop in <code>ntpq</code>](/support/securitynotice/ntpbug2948/) |<span style="color:orange">MEDIUM</span>|
| [2947: <code>ntpq</code> protocol vulnerable to replay attacks](/support/securitynotice/ntpbug2947/) |<span style="color:orange">MEDIUM</span>|
| [2945: 0rigin: Zero Origin Timestamp Bypass](/support/securitynotice/ntpbug2945/) |<span style="color:orange">MEDIUM</span>|
| [2942: Off-path Denial of Service (DoS) attack on authenticated broadcast mode](/support/securitynotice/ntpbug2942/) |<span style="color:orange">MEDIUM</span>|
| [2940: Stack exhaustion in recursive traversal of restriction list](/support/securitynotice/ntpbug2940/) |<span style="color:orange">MEDIUM</span>|
| [2939: <code>reslist</code> NULL pointer dereference](/support/securitynotice/ntpbug2939/) |<span style="color:orange">MEDIUM</span>|
| [2938: <code>ntpq saveconfig</code> command allows dangerous characters in filenames](/support/securitynotice/ntpbug2938/) |<span style="color:orange">MEDIUM</span>|
| [2937: <code>nextvar()</code> missing length check in <code>ntpq</code>](/support/securitynotice/ntpbug2937/) |<span style="color:green">LOW</span>|
| [2936: Skeleton Key: Any trusted key system can serve time ](/support/securitynotice/ntpbug2936/) |<span style="color:red">HIGH</span>|
| [2935: Deja Vu: Replay attack on authenticated broadcast mode](/support/securitynotice/ntpbug2935/) |<span style="color:orange">MEDIUM</span>|

* * *

#### 4.2.8p5

* Public Release: 2016 Jan 07

| Security Issue | Severity |
| -------------- | -------- |
| [2956: Small-step/big-step](/support/securitynotice/ntpbug2956/) |<span style="color:orange">MEDIUM</span>|

* * *

#### 4.2.8p4

* Public Release: 2015 Oct 21

| Security Issue | Severity |
| -------------- | -------- |
| [2941: NAK to the Future: Symmetric association authentication bypass via crypto-NAK](/support/securitynotice/ntpbug2941/) |<span style="color:green">LOW</span>|
| [2922: <code>decodenetnum()</code> will ASSERT botch instead of returning FAIL on some bogus values](/support/securitynotice/ntpbug2922/) |<span style="color:red">HIGH</span>|
| [2921: TALOS-CAN-0065: Password Length Memory Corruption Vulnerability](/support/securitynotice/ntpbug2921/) |<span style="color:red">HIGH</span>|
| [2920: TALOS-CAN-0064: Invalid length data provided by a custom refclock driver could cause a buffer overflow](/support/securitynotice/ntpbug2920/) |<span style="color:red">HIGH</span>|
| [2919: TALOS-CAN-0063: <code>ntpq atoascii()</code> potential memory corruption](/support/securitynotice/ntpbug2919/) |<span style="color:red">HIGH</span>|
| [2918: TALOS-CAN-0062: Potential path traversal vulnerability in the config file saving of <code>ntpd</code> on VMS](/support/securitynotice/ntpbug2918/) |<span style="color:red">HIGH</span>|
| [2917: TALOS-CAN-0055: Infinite loop if extended logging enabled and the logfile and keyfile are the same](/support/securitynotice/ntpbug2917/) |<span style="color:red">HIGH</span>|
| [2916: TALOS-CAN-0054: memory corruption in password store](/support/securitynotice/ntpbug2916/) |<span style="color:red">HIGH</span>|
| [2913: TALOS-CAN-0052: mode 7 loop counter underrun](/support/securitynotice/ntpbug2913/) |<span style="color:red">HIGH</span>|
| [2909: Slow memory leak in <code>CRYPTO_ASSOC</code>](/support/securitynotice/ntpbug2909/) |<span style="color:red">HIGH</span>|
| [2902: Configuration directives to change "pidfile" and "driftfile" should only be allowed locally](/support/securitynotice/ntpbug2902/) |<span style="color:red">HIGH</span>|
| [2901: Clients that receive a KoD should validate the origin timestamp field](/support/securitynotice/ntpbug2901/) |<span style="color:orange">MEDIUM</span>|
| [2899: Incomplete autokey data packet length checks](/support/securitynotice/ntpbug2899/) |<span style="color:red">HIGH</span>|

* * *

#### 4.2.8p3

* Advance Notification: 2015 Jun 22
* Advance Release: 2015 Jun 24
* Public Release: 2015 Jun 29

| Security Issue | Severity |
| -------------- | -------- |
| [2853: ntpd control message crash: Crafted NUL-byte in configuration directive](/support/securitynotice/ntpbug2853/) |<span style="color:green">LOW</span>|

* * *

#### 4.2.8p2

* Advance Notification: 2015 Mar 15
* Advance Release: 2015 Mar 22
* Public Release: 2015 Apr 7

| Security Issue | Severity |
| -------------- | -------- |
| [2781: Authentication doesn't protect symmetric associations against DoS attacks](/support/securitynotice/ntpbug2781/) |<span style="color:orange">MEDIUM</span>|
| [2779: ntpd accepts unauthenticated packets with symmetric key crypto](/support/securitynotice/ntpbug2779/) |<span style="color:green">LOW</span>|

* * *

#### 4.2.8p1

* Public Release: 2015 Feb 04

| Security Issue | Severity |
| -------------- | -------- |
| [2672: ::1 can be spoofed on some OSes, so ACLs based on IPv6 ::1 addresses can be bypassed](/support/securitynotice/ntpbug2672/) |<span style="color:orange">MEDIUM</span>|
| [2671: <code>vallen</code> is not validated in several places in <code>ntp_crypto.c</code>, leading to a potential info leak or possibly crashing <code>ntpd</code>](/support/securitynotice/ntpbug2671/) |<span style="color:green">LOW</span>|

* * *

#### 4.2.8

* Public Release: 2014 Dec 18

| Security Issue | Severity |
| -------------- | -------- |
| [2670: receive(): missing return on error](/support/securitynotice/ntpbug2670/) |<span style="color:orange">MEDIUM</span>|
| [2669: Buffer overflow in configure()](/support/securitynotice/ntpbug2669/) |<span style="color:red">HIGH</span>|
| [2668: Buffer overflow in ctl_putdata()](/support/securitynotice/ntpbug2668/) |<span style="color:red">HIGH</span>|
| [2667: Buffer overflow in crypto_recv()](/support/securitynotice/ntpbug2667/) |<span style="color:red">HIGH</span>|

* * *

#### 4.2.7p230

* Public Release: 2011 Nov 1

| Security Issue | Severity |
| -------------- | -------- |
| [2666: non-cryptographic random number generator with weak seed used by ntp-keygen to generate symmetric keys](/support/securitynotice/ntpbug2666/) |<span style="color:red">HIGH</span>|

* * *

#### 4.2.7p26

* Public Release: 2010 Apr 24

| Security Issue | Severity |
| -------------- | -------- |
| [1532: DRDoS / Amplification Attack using ntpdc monlist command](/support/securitynotice/ntpbug1532/) |<span style="color:orange">MEDIUM</span>|

* * *

#### 4.2.7p11

* Public Release: 2010 Jan 28

| Security Issue | Severity |
| -------------- | -------- |
| [2665 :Weak default key in config_auth()](/support/securitynotice/ntpbug2665/) |<span style="color:red">HIGH</span>|

* * *

#### 4.2.6

* Public Release: 2009 Dec 8

| Security Issue | Severity |
| -------------- | -------- |
| [1331: DoS attack from certain NTP mode 7 packets](/support/securitynotice/ntpbug1331/) |<span style="color:orange">MEDIUM</span>|

* * *

#### 4.2.4p7

* Public Release: 2009 Mar 4

| Security Issue | Severity |
| -------------- | -------- |
| [1151: Remote exploit if autokey is enabled](/support/securitynotice/ntpbug1151/) |<span style="color:orange">MEDIUM</span>|

#### 4.2.4p5

* Public Release: 2009 Jan 8

| Security Issue | Severity |
| -------------- | -------- |
| [Multiple OpenSSL signature verification API misuse](https://nvd.nist.gov/vuln/detail/CVE-2009-0021) |<span style="color:orange">MEDIUM</span>|

