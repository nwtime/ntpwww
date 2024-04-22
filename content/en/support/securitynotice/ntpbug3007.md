---
title: "NTP BUG 3007: CRYPTO-NAK DoS"
description: "An off-path attacker can cause a preemptable client association to be demobilized by sending a crypto NAK packet to a victim client with a spoofed source address of an existing associated peer. This is true even if authentication is enabled. This bug was resolved in NTP 4.2.8p7."
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
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=3007">Bug 3007</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2016-1547">CVE-2016-1547</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>All ntp-4 releases up to, but not including 4.2.8p7,<br> and 4.3.0 up to, but not including 4.3.92.</td>
		<td>Resolved in 4.2.8p7.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>MED 4.3</td>
		<td><a href="https://nvd.nist.gov/vuln-metrics/cvss/v2-calculator?calculator&version=2.0&vector=(AV:N/AC:M/Au:N/C:N/I:N/A:P)">AV:N/AC:M/Au:N/C:N/I:N/A:P</a></td>
	</tr>
	<tr>
		<th><b>CVSS3 Score<b></th>
		<td>LOW 3.7</td>
		<td><a href="https://www.first.org/cvss/calculator/3.0#CVSS:3.0/AV:N/AC:H/PR:N/UI:N/S:U/C:N/I:N/A:L">CVSS:3.0/AV:N/AC:H/PR:N/UI:N/S:U/C:N/I:N/A:L</a></td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

For ntp-4 versions up to but not including ntp-4.2.8p7, an off-path attacker can cause a preemptable client association to be demobilized by sending a crypto NAK packet to a victim client with a spoofed source address of an existing associated peer. This is true even if authentication is enabled.

Furthermore, if the attacker keeps sending crypto NAK packets, for example one every second, the victim never has a chance to reestablish the association and synchronize time with that legitimate server.

For ntp-4.2.8 thru ntp-4.2.8p6 there is less risk because more stringent checks are performed on incoming packets, but there are still ways to exploit this vulnerability in versions before ntp-4.2.8p7.

* * *
    
#### Mitigation

* Implement [BCP-38](http://www.bcp38.info/index.php/Main_Page).
* Upgrade to [4.2.8p7 or later.](https://downloads.nwtime.org/ntp/4.2.8/)
* Properly monitor your `ntpd` instances. 

* * *

#### Credit

This weakness was discovered by Stephen Gray and Matthew Van Gundy of Cisco ASIG.

* * *

#### Timeline

* 2016 Apr 26: Public release
* 2016 Apr 12: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2016 Feb 14: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2016 Jan 12: Initial notification from Cisco