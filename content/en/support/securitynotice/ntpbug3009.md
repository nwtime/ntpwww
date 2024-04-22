---
title: "NTP BUG 3009: Crafted addpeer with hmode > 7 causes array wraparound with MATCH_ASSOC"
description: "Using a crafted packet to create a peer association with hmode > 7 causes the MATCH_ASSOC() lookup to make an out-of-bounds reference. This bug was resolved in NTP 4.2.8p7."
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
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=3009">Bug 3009</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2016-2518">CVE-2016-2518</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>All ntp-4 releases up to, but not including 4.2.8p7,<br> and 4.3.0 up to, but not including 4.3.92.</td>
		<td>Resolved in 4.2.8p7.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>LOW 2.1</td>
		<td><a href="https://nvd.nist.gov/vuln-metrics/cvss/v2-calculator?calculator&version=2.0&vector=(AV:N/AC:H/Au:S/C:N/I:N/A:P)">AV:N/AC:H/Au:S/C:N/I:N/A:P</a></td>
	</tr>
	<tr>
		<th><b>CVSS3 Score<b></th>
		<td>LOW 2.0</td>
		<td><a href="https://www.first.org/cvss/calculator/3.0#CVSS:3.0/AV:N/AC:H/PR:H/UI:R/S:U/C:N/I:N/A:L">CVSS:3.0/AV:N/AC:H/PR:H/UI:R/S:U/C:N/I:N/A:L</a></td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

Using a crafted packet to create a peer association with `hmode` > 7 causes the `MATCH_ASSOC()` lookup to make an out-of-bounds reference.

* * *
    
#### Mitigation

* Implement [BCP-38](http://www.bcp38.info/index.php/Main_Page).
* Upgrade to [4.2.8p7 or later.](https://downloads.nwtime.org/ntp/4.2.8/)
* Properly monitor your `ntpd` instances. 

* * *

#### Credit

This weakness was discovered by Yihan Lian of the Cloud Security Team, Qihoo 360.

* * *

#### Timeline

* 2016 Apr 26: Public release
* 2016 Apr 12: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2016 Feb 14: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2016 Jan 12: Initial notification from Cisco