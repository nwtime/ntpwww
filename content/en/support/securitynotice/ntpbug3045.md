---
title: "NTP BUG 3045: Bad authentication demobilizes ephemeral associations"
type: archives
date: "2016-06-02"
---

* * *

#### Summary

<table>
  <tbody>
	<tr>
		<th><b>Resolved</b></th>
		<td><a href="/support/securitynotice/4_2_8p8-release-announcement/">4.2.8p8</a></td>
		<td>02 June 2016</td>
	</tr>
	<tr>
		<th><b>References</b></th>
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=3045">Bug 3045</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2016-4953/">CVE-2016-4953</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>ntp-4, up to but not including ntp-4.2.8p8,<br> and ntp-4.3.0 up to, but not including ntp-4.3.93.</td>
		<td>Resolved in 4.2.8p8.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>LOW 2.6</td>
		<td><a href="https://nvd.nist.gov/cvss.cfm?calculator&version=2&vector=(AV:N/AC:H/Au:N/C:N/I:N/A:P)">AV:N/AC:H/Au:N/C:N/I:N/A:P</a></td>
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

An attacker who knows the origin timestamp and can send a spoofed packet containing a `CRYPTO-NAK` to an ephemeral peer target before any other response is sent can demobilize that association.

* * *
    
#### Mitigation

* Implement [BCP-38](http://www.bcp38.info/index.php/Main_Page).
* Upgrade to [4.2.8p8 or later](/downloads/).
* Properly monitor your `ntpd` instances, and auto-restart `ntpd` (without `-g`) if it stops running. 

* * *

#### Credit

This weakness was discovered by Miroslav Lichvar of Red Hat.

* * *

#### Timeline

* 2016 Jun 02: Public release
* 2016 May 24: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* : [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/)
* : Report received