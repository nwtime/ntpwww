---
title: "NTP BUG 2901: Clients that receive a KoD should validate the origin timestamp field"
type: archives
date: "2015-10-21"
---

* * *

#### Summary

<table>
  <tbody>
	<tr>
		<th><b>Resolved</b></th>
		<td><a href="/support/securitynotice/4_2_8p4-release-announcement">4.2.8p4</a></td>
		<td>21 Oct 2015</td>
	</tr>
	<tr>
		<th><b>References</b></th>
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=2901">Bug 2901</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2015-7704">CVE-2015-7704</a><br> <a href="https://nvd.nist.gov/vuln/detail/CVE-2015-7705">CVE-2015-7705</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>All ntp-4 releases up to, but not including 4.2.8p4,<br> and 4.3.0 up to, but not including 4.3.77.</td>
		<td>Resolved in 4.2.8p4.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>4.3-5.0 at worst</td>
		<td><a href="https://nvd.nist.gov/cvss.cfm?calculator&version=2&vector=(AV:N/AC:M/Au:N/C:N/I:N/A:P)">AV:N/AC:M/Au:N/C:N/I:N/A:P</a></td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

An `ntpd` client that honors Kiss-of-Death responses will honor KoD messages that have been forged by an attacker, causing it to delay or stop querying its servers for time updates. Also, an attacker can forge packets that claim to be from the target and send them to servers often enough that a server that implements KoD rate limiting will send the target machine a KoD response to attempt to reduce the rate of incoming packets, or it may also trigger a firewall block at the server for packets from the target machine. For either of these attacks to succeed, the attacker must know what servers the target is communicating with. An attacker can be anywhere on the Internet and can frequently learn the identity of the target's time source by sending the target a time query.

* * *
    
#### Mitigation

* Implement [BCP-38.](http://www.bcp38.info)
* Upgrade to [4.2.8p4 or later](/downloads).
*  If you cannot upgrade, restrict who can query `ntpd` to learn who its servers are, and what IPs are allowed to ask your system for the time. This mitigation is heavy-handed.
* Monitor your `ntpd` instances. 

> **NOTE:** 4.2.8p4 protects against the first attack. For the second attack, all we can do is warn when it is happening, which we do in 4.2.8p4. 

* * *

#### Credit

This weakness was discovered by Aanchal Malhotra, Issac E. Cohen, and Sharon Goldberg of Boston University.

* * *

#### Timeline

* 2015 Oct 21: Public release
* 2015 Oct 6: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits)
* 2015 Aug 26: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits) for [1593](https://bugs.ntp.org/show_bug.cgi?id=1593), [1774](https://bugs.ntp.org/show_bug.cgi?id=1774), [2382](https://bugs.ntp.org/show_bug.cgi?id=2382), [2899](/support/securitynotice/ntpbug2899), and [2902](/support/securitynotice/ntpbug2902)
* 2015 Aug 20: Initial notification of [2902](/support/securitynotice/ntpbug2902); analysis begins
* 2015 Aug 11: Initial notification of [2899](/support/securitynotice/ntpbug2899); analysis begins