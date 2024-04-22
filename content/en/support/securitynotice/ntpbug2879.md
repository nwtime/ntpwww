---
title: "NTP BUG 2879: Improve NTP security against buffer comparison timing attacks"
description: "It is potentially possible for a local or LAN-based attacker to send a packet with an authentication payload and indirectly observe how much of the digest has matched. This bug was resolved in NTP 4.2.8p7."
type: archives
date: "2016-04-26"
---

* * *

#### Summary

<table>
  <tbody>
	<tr>
		<th><b>Resolved</b></th>
		<td><a href="/support/securitynotice/4_2_8p7-release-announcement/">4.2.8p7</a></td>
		<td>26 Apr 2016</td>
	</tr>
	<tr>
		<th><b>References</b></th>
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=2879">Bug 2879</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2016-1550">CVE-2016-1550</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>All ntp-4 releases up to, but not including 4.2.8p7,<br> and 4.3.0 up to, but not including 4.3.92.</td>
		<td>Resolved in 4.2.8p7.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>LOW 2.6</td>
		<td><a href="https://nvd.nist.gov/vuln-metrics/cvss/v2-calculator?calculator&version=2.0&vector=(AV:L/AC:H/Au:N/C:P/I:P/A:N)">AV:L/AC:H/Au:N/C:P/I:P/A:N</a></td>
	</tr>
	<tr>
		<th><b>CVSS3 Score<b></th>
		<td>MED 4.0</td>
		<td><a href="https://www.first.org/cvss/calculator/3.0#CVSS:3.0/AV:L/AC:H/PR:N/UI:N/S:U/C:L/I:L/A:N">CVSS:3.0/AV:L/AC:H/PR:N/UI:N/S:U/C:L/I:L/A:N</a></td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

Packet authentication tests have been performed using `memcmp()` or possibly `bcmp()`, and it is potentially possible for a local or perhaps LAN-based attacker to send a packet with an authentication payload and indirectly observe how much of the digest has matched.

* * *
    
#### Mitigation

* Upgrade to [4.2.8p7 or later.](https://downloads.nwtime.org/ntp/4.2.8/)
* Properly monitor your `ntpd` instances. 

* * *

#### Credit

This weakness was discovered independently by Loganaden Velvindron, and Matthew Van Gundy and Stephen Gray of Cisco ASIG.

* * *

#### Timeline

* 2016 Apr 26: Public release
* 2016 Apr 12: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2016 Feb 14: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2016 Jan 12: Initial notification from Cisco