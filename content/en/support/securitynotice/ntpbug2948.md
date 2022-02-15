---
title: "NTP BUG 2948: Potential Infinite Loop in ntpq"
type: archives
date: "2016-01-19"
---

* * *

#### Summary

<table>
  <tbody>
	<tr>
		<th><b>Resolved</b></th>
		<td><a href="/support/securitynotice/4_2_8p6-release-announcement/">4.2.8p6</a></td>
		<td>19 Jan 2016</td>
	</tr>
	<tr>
		<th><b>References</b></th>
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=2948">Bug 2948</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2015-8158">CVE-2015-8158</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>All ntp-4 releases up to, but not including 4.2.8p6,<br> and 4.3.0 up to, but not including 4.3.90.</td>
		<td>Resolved in 4.2.8p6</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>MED 4.3</td>
		<td><a href="https://nvd.nist.gov/vuln-metrics/cvss/v2-calculator?calculator&version=2.0&vector=(AV:N/AC:M/Au:N/C:N/I:N/A:P)">AV:N/AC:M/Au:N/C:N/I:N/A:P</a></td>
	</tr>
	<tr>
		<th><b>CVSS3 Score<b></th>
		<td>MED 5.3</td>
		<td><a href="https://www.first.org/cvss/calculator/3.0#CVSS:3.0/AV:N/AC:L/PR:N/UI:N/S:U/C:N/I:L/A:N">CVSS:3.0/AV:N/AC:L/PR:N/UI:N/S:U/C:N/I:L/A:N</a></td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

`ntpq` processes incoming packets in a loop in `getresponse()`. The loop's only stopping conditions are receiving a complete and correct response or hitting a small number of error conditions. If the packet contains incorrect values that don't trigger one of the error conditions, the loop continues to receive new packets. 

> Note well, this is an attack against an instance of `ntpq`, not `ntpd`, and this attack requires the attacker to do one of the following:

  * Own a malicious NTP server that the client trusts.
  * Prevent a legitimate NTP server from sending packets to the `ntpq` client.
  * [MITM](https://en.wikipedia.org/wiki/Man-in-the-middle_attack) the `ntpq` communications between the `ntpq` client and the NTP server. 

* * *
    
#### Mitigation

* Upgrade to [4.2.8p6 or later.](/downloads/)

* * *

#### Credit

This weakness was discovered by Jonathan Gardner of Cisco ASIG.

* * *

#### Timeline

* 2016 Jan 19: Public release
* 2016 Jan 17: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2015 Nov 5: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2016 Oct 16: Initial notification from Cisco