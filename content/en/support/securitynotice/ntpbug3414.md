---
title: "NTP BUG 3414: ntpq: decodearr() can write beyond its buf limits"
type: archives
date: "2018-02-27"
---

* * *

#### Summary

<table>
  <tbody>
	<tr>
		<th><b>Resolved</b></th>
		<td><a href="/support/securitynotice/4_2_8p11-release-announcement/">27 Feb 2018</a></td>
		<td>DATE</td>
	</tr>
	<tr>
		<th><b>References</b></th>
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=3414">Bug 3414</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2018-7183/">CVE-2018-7183</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td><code>ntpq</code> in ntp-4.2.8p6, up to but not including ntp-4.2.8p11.</td>
		<td>Resolved in 4.2.8p11.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>MED 6.8</td>
		<td><a href="https://nvd.nist.gov/vuln-metrics/cvss/v2-calculator?vector=(AV:N/AC:M/Au:N/C:P/I:P/A:P)">AV:N/AC:M/Au:N/C:P/I:P/A:P</a></td>
	</tr>
	<tr>
		<th><b>CVSS3 Score<b></th>
		<td>MED 5.0</td>
		<td><a href="https://www.first.org/cvss/calculator/3.0#CVSS:3.0/AV:N/AC:H/PR:N/UI:R/S:U/C:L/I:L/A:L">CVSS:3.0/AV:N/AC:H/PR:N/UI:R/S:U/C:L/I:L/A:L</a></td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

`ntpq` is a monitoring and control program for `ntpd`. `decodearr()` is an internal function of `ntpq` that is used to -- wait for it -- decode an array in a response string when formatted data is being displayed. This is a problem in affected versions of `ntpq` if a maliciously-altered `ntpd` returns an array result that will trip this bug, or if a bad actor is able to read an `ntpq` request on its way to a remote `ntpd` server and forge and send a response before the remote `ntpd` sends its response. It's potentially possible that the malicious data could become injectable/executable code. 

* * *
    
#### Mitigation

* Implement [BCP-38](http://www.bcp38.info/index.php/Main_Page).
* Upgrade to [ntp-4.2.8p11 or later.](/downloads/)

* * *

#### Credit

This weakness was discovered by Michael Macnair of Thales e-Security.

* * *

#### Timeline

* 2018 Feb 27: Public release
* 2018 Feb 12: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2018 Jan 23: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/)
* : Notification from reporter