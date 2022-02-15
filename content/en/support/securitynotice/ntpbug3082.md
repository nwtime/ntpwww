---
title: "NTP BUG 3082: read_mru_list() does inadequate incoming packet checks"
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
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=3082">Bug 3082</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2016-7434">CVE-2016-7434</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>ntp-4.2.7p22, up to but not including ntp-4.2.8p9,<br> and ntp-4.3.0 up to, but not including ntp-4.3.94. </td>
		<td>Resolved in 4.2.8p9.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>LOW 3.8</td>
		<td><a href="https://nvd.nist.gov/vuln-metrics/cvss/v2-calculator?calculator&version=2.0&vector=(AV:L/AC:H/Au:S/C:N/I:N/A:C)">AV:L/AC:H/Au:S/C:N/I:N/A:C</a></td>
	</tr>
	<tr>
		<th><b>CVSS3 Score<b></th>
		<td>LOW 3.8</td>
		<td><a href="https://www.first.org/cvss/calculator/3.0#CVSS:3.0/AV:P/AC:H/PR:H/UI:R/S:U/C:N/I:N/A:H">CVSS:3.0/AV:P/AC:H/PR:H/UI:R/S:U/C:N/I:N/A:H</a></td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

If `ntpd` is configured to allow `mrulist` query requests from a server that sends a crafted malicious packet, `ntpd` will crash on receipt of that crafted malicious `mrulist` query packet.

* * *
    
#### Mitigation

* Only allow `mrulist` query packets from trusted hosts.
* Implement [BCP-38.](http://www.bcp38.info/index.php/Main_Page) 
* Upgrade to [4.2.8p9 or later.](/downloads/)
* Properly monitor your `ntpd` instances, and auto-restart `ntpd` (without `-g`) if it stops running. 

* * *

#### Credit

This weakness was discovered by Magnus Stubman.

* * *

#### Timeline

* 2016 Nov 21: Public release
* 2016 Nov 15: CERT given our software release notification 
* 2016 Nov 14: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* : [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/)
* : Report received