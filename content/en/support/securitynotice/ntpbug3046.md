---
title: "NTP BUG 3046: CRYPTO_NAK crash"
description: "This bug could cause ntpd to crash. This bug was resolved in NTP 4.2.8p8."
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
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=3046">Bug 3046</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2016-4957">CVE-2016-4957</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>ntp-4.2.8p7, and ntp-4.3.92.</td>
		<td>Resolved in 4.2.8p8.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>HIGH 7.8</td>
		<td><a href="https://nvd.nist.gov/vuln-metrics/cvss/v2-calculator?calculator&version=2.0&vector=(AV:N/AC:L/Au:N/C:N/I:N/A:C)">AV:N/AC:L/Au:N/C:N/I:N/A:C</a></td>
	</tr>
	<tr>
		<th><b>CVSS3 Score<b></th>
		<td>HIGH 7.5</td>
		<td><a href="https://www.first.org/cvss/calculator/3.0#CVSS:3.0/AV:N/AC:L/PR:N/UI:N/S:U/C:N/I:N/A:H">CVSS:3.0/AV:N/AC:L/PR:N/UI:N/S:U/C:N/I:N/A:H</a></td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

The fix for [3007](https://bugs.ntp.org/show_bug.cgi?id=3007) in ntp-4.2.8p7 contained a bug that could cause `ntpd` to crash.

* * *
    
#### Mitigation

* Implement [BCP-38](http://www.bcp38.info/index.php/Main_Page).
* Upgrade to [4.2.8p8 or later](/downloads/).
* If you cannot upgrade from 4.2.8p7, the only other alternatives are to patch your code or filter `CRYPTO_NAK` packets.
* Properly monitor your `ntpd` instances, and auto-restart `ntpd` (without `-g`) if it stops running. 

* * *

#### Credit

This weakness was discovered by Nicolas Edet of Cisco.

* * *

#### Timeline

* 2016 Jun 02: Public release
* 2016 May 24: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* : [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/)
* : Report received