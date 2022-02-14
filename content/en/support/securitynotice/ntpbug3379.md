---
title: "NTP BUG 3379: Potential Overflows in ctl_put() functions"
type: archives
date: "2017-03-21"
---

* * *

#### Summary

<table>
  <tbody>
	<tr>
		<th><b>Resolved</b></th>
		<td><a href="/support/securitynotice/4_2_8p10-release-announcement/">Potential Overflows in ctl_put() functions</a></td>
		<td>21 Mar 2017</td>
	</tr>
	<tr>
		<th><b>References</b></th>
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=3379">Bug 3379</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2017-6458/">CVE-2017-6458</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>All versions of NTP, up to but not including ntp-4.2.8p10,<br> and ntp-4.3.0 up to, but not including ntp-4.3.94.</td>
		<td>Resolved in 4.2.8p10.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>MED 4.6</td>
		<td><a href="https://nvd.nist.gov/cvss.cfm?calculator&version=2&vector=(AV:N/AC:H/Au:M/C:N/I:N/A:C)">AV:N/AC:H/Au:M/C:N/I:N/A:C)</a></td>
	</tr>
	<tr>
		<th><b>CVSS3 Score<b></th>
		<td>MED 4.2</td>
		<td><a href="https://www.first.org/cvss/calculator/3.0#CVSS:3.0/AV:N/AC:H/PR:H/UI:R/S:U/C:N/I:N/A:H">CVSS:3.0/AV:N/AC:H/PR:H/UI:R/S:U/C:N/I:N/A:H</a></td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

`ntpd` makes use of different wrappers around `ctl_putdata()` to create name/value `ntpq` (mode 6) response strings. For example, `ctl_putstr()` is usually used to send string data (variable names or string data). The formatting code was missing a length check for variable names. If somebody explicitly created any unusually long variable names in `ntpd` (longer than 200-512 bytes, depending on the type of variable), then if any of these variables are added to the response list it would overflow a buffer. 

* * *
    
#### Mitigation

* Implement [BCP-38.](http://www.bcp38.info/index.php/Main_Page) 
* Upgrade to [4.2.8p10 or later.](/downloads/)
* If you don't want to upgrade, then don't `setvar` variable names longer than 200-512 bytes in your `ntp.conf` file. 
* Properly monitor your `ntpd` instances, and auto-restart `ntpd` (without `-g`) if it stops running. 

* * *

#### Credit

This weakness was discovered by Cure53.

* * *

#### Timeline

* 2017 Mar 21: Public release
* 2017 Mar 06: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2017 Mar 06: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2017 Feb 09: Mozilla/Cure53 audit received