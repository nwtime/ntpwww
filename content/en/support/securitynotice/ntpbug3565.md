---
title: "NTP BUG 3565: Crafted null dereference attack from a trusted source with an authenticated mode 6 packet"
type: archives
date: "2019-03-07"
---

* * *

#### Summary

<table>
  <tbody>
	<tr>
		<th><b>Resolved</b></th>
		<td><a href="/support/securitynotice/4_2_8p13-release-announcement/">4.2.8p13</a></td>
		<td>07 Mar 2019</td>
	</tr>
	<tr>
		<th><b>References</b></th>
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=3565">Bug 3565</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2019-8936/">CVE-2019-8936</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>All ntp-4 releases up to, but not including 4.2.8p13,<br> and 4.3.0 up to, but not including 4.3.94.</td>
		<td>Resolved in 4.2.8p13 and 4.3.94.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>4.6</td>
		<td><a href="https://nvd.nist.gov/vuln-metrics/cvss/v2-calculator?vector=(AV:N/AC:H/Au:M/C:N/I:N/A:C)">AV:N/AC:H/Au:M/C:N/I:N/A:C</a></td>
	</tr>
	<tr>
		<th><b>CVSS3 Score<b></th>
		<td>4.2</td>
		<td><a href="https://nvd.nist.gov/vuln-metrics/cvss/v3-calculator?vector=AV:N/AC:H/PR:H/UI:R/S:U/C:N/I:N/A:H">CVSS:3.0/AV:N/AC:H/PR:H/UI:R/S:U/C:N/I:N/A:H</a></td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

A crafted malicious authenticated mode 6 (`ntpq`) packet from a permitted network address can trigger a NULL pointer dereference, crashing `ntpd`. Note that for this attack to work, the sending system must be on an address that the target's `ntpd` accepts mode 6 packets from, and must use a private key that is specifically listed as being used for mode 6 authorization. 

* * *
    
#### Mitigation

* Use `restrict noquery` to limit addresses that can send mode 6 queries.
* Limit access to the private controlkey in `ntp.keys`.
* Upgrade to [4.2.8p13 or later.](/downloads/)

* * *

#### Credit

Reported by Magnus Stubman.

* * *

#### Timeline

* 2019 Mar 07: Public release
* 2019 Feb 19: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2019 Jan 17: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2019 Jan 15: Notification from reporter