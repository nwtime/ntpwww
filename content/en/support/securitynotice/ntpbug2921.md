---
title: "NTP BUG 2921: Password Length Memory Corruption Vulnerability"
description: "If ntpd is configured to allow remote configuration, and the source IP address is allowed to send remote configuration requests, and the attacker knows the remote configuration password or ntpd was configured to disable authentication, then an attacker can send a set of packets to crash ntpd. This bug was resolved in NTP 4.2.8p4."
type: archives
date: "2015-10-21"
---

* * *

#### Summary

<table>
  <tbody>
	<tr>
		<th><b>Resolved</b></th>
		<td><a href="/support/securitynotice/4_2_8p4-release-announcement/">4.2.8p4</a></td>
		<td>21 Oct 2015</td>
	</tr>
	<tr>
		<th><b>References</b></th>
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=2921">Bug 2921</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2015-7854">CVE-2015-7854</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>All ntp-4 releases up to, but not including 4.2.8p4,<br> and 4.3.0 up to, but not including 4.3.77.</td>
		<td>Resolved in 4.2.8p4.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>0.0 best case, 1.7 usual case, 6.8, worst case</td>
		<td><a href="https://nvd.nist.gov/vuln-metrics/cvss/v2-calculator?calculator&version=2.0&vector=(AV:N/AC:H/Au:M/C:C/I:C/A:C)">AV:N/AC:H/Au:M/C:C/I:C/A:C</a></td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

If `ntpd` is configured to allow remote configuration, and if the (possibly spoofed) source IP address is allowed to send remote configuration requests, and if the attacker knows the remote configuration password or if `ntpd` was (foolishly) configured to disable authentication, then an attacker can send a set of packets to `ntpd` that may cause it to crash, with the hypothetical possibility of a small code injection.

* * *
    
#### Mitigation

* Implement [BCP-38.](http://www.bcp38.info/index.php/Main_Page)
* Upgrade to [4.2.8p4 or later](/downloads/).
* If you are unable to upgrade, remote configuration of NTF's `ntpd` requires:
  * an explicitly configured "trusted" key. Only configure this if you need it.
  * access from a permitted IP address. You choose the IPs.
  * authentication. Don't disable it. Practice secure key safety. 
* Monitor your `ntpd` instances. 

* * *

#### Credit

This weakness was discovered by Yves Younan and Aleksander Nikolich of Cisco Talos.

* * *

#### Timeline

* 2015 Oct 21: Public release
* 2015 Oct 6: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2015 Aug 26: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/) for [1593](/support/securitynotice/ntpbug1593/), [1774](/support/securitynotice/ntpbug1774/), [2382](/support/securitynotice/ntpbug2382/), [2899](/support/securitynotice/ntpbug2899/), and [2902](/support/securitynotice/ntpbug2902/)
* 2015 Aug 20: Initial notification of [2902](/support/securitynotice/ntpbug2902/); analysis begins
* 2015 Aug 11: Initial notification of [2899](/support/securitynotice/ntpbug2899/); analysis begins