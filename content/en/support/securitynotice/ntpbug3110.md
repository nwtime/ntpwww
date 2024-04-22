---
title: "NTP BUG 3110: Windows: ntpd DoS by oversized UDP packet"
description: "If a vulnerable instance of ntpd on Windows receives a crafted malicious packet that is too big, ntpd will stop working. This bug was resolved in NTP 4.2.8p9."
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
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=3110">Bug 3110</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2016-9312">CVE-2016-9312</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>Windows only: ntp-4.?.?, up to but not including ntp-4.2.8p9,<br> and ntp-4.3.0 up to, but not including ntp-4.3.94.</td>
		<td>Resolved in 4.2.8p9.</td>
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

If a vulnerable instance of `ntpd` on Windows receives a crafted malicious packet that is "too big", `ntpd` will stop working.

* * *
    
#### Mitigation

* Implement [BCP-38.](http://www.bcp38.info/index.php/Main_Page) 
* Implement a firewall rule blocking oversized NTP packets.
* Upgrade to [4.2.8p9 or later.](https://downloads.nwtime.org/ntp/4.2.8/)
* Properly monitor your `ntpd` instances, and auto-restart `ntpd` (without `-g`) if it stops running. 

* * *

#### Credit

This weakness was discovered by Robert Pajak of ABB.

* * *

#### Timeline

* 2016 Nov 21: Public release
* 2016 Nov 15: CERT given our software release notification 
* 2016 Nov 14: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* : [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/)
* : Report received