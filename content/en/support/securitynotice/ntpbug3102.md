---
title: "NTP BUG 3102: Zero Origin timestamp regression"
type: archives
date: "2016-11-21"
---

* * *

#### Summary

<table>
  <tbody>
	<tr>
		<th><b>Resolved</b></th>
		<td><a href="/support/securitynotice/4_2_8p9-release-announcement/">4.2.8p9</a></td>
		<td>21 Nov 2016</td>
	</tr>
	<tr>
		<th><b>References</b></th>
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=3102">Bug 3102</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2016-7431">CVE-2016-7431</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>ntp-4.2.8p8 and ntp-4.3.93.</td>
		<td>Resolved in 4.2.8p9.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>MED 5.0</td>
		<td><a href="https://nvd.nist.gov/vuln-metrics/cvss/v2-calculator?calculator&version=2&vector=(AV:N/AC:L/Au:N/C:N/I:P/A:N)">AV:N/AC:L/Au:N/C:N/I:P/A:N</a></td>
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

Zero Origin timestamp problems were fixed by [Bug 2945](https://bugs.ntp.org/show_bug.cgi?id=2945) in ntp-4.2.8p6. However, subsequent timestamp validation checks introduced a regression in the handling of some Zero origin timestamp checks.

* * *
    
#### Mitigation

* Implement [BCP-38.](http://www.bcp38.info/index.php/Main_Page) 
* Upgrade to [4.2.8p9 or later.](/downloads/)
* Properly monitor your `ntpd` instances, and auto-restart `ntpd` (without `-g`) if it stops running. 

* * *

#### Credit

This weakness was discovered by Sharon Goldberg and Aanchal Malhotra of Boston University.

* * *

#### Timeline

* 2016 Nov 21: Public release
* 2016 Nov 15: CERT given our software release notification 
* 2016 Nov 14: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* : [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/)
* : Report received