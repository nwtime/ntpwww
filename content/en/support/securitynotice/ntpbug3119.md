---
title: "NTP BUG 3119: Mode 6 unauthenticated trap information disclosure and DDoS vector"
description: "ntpd does not enable trap service by default. If trap service has been explicitly enabled, an attacker can send a specially crafted packet to cause a null pointer dereference that will crash ntpd, resulting in a denial of service. This bug was resolved in NTP 4.2.8p9."
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
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=3119">Bug 3119</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2016-9311">CVE-2016-9311</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>ntp-4.0.90 (21 July 1999), possibly earlier, up to but not<br> including ntp-4.2.8p9, and ntp-4.3.0 up to, but not including ntp-4.3.94.</td>
		<td>Resolved in 4.2.8p9.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>MED 4.9</td>
		<td><a href="https://nvd.nist.gov/vuln-metrics/cvss/v2-calculator?calculator&version=2.0&vector=(AV:N/AC:H/Au:S/C:N/I:N/A:C)">AV:N/AC:H/Au:N/C:N/I:N/A:C</a></td>
	</tr>
	<tr>
		<th><b>CVSS3 Score<b></th>
		<td>MED 4.4</td>
		<td><a href="https://www.first.org/cvss/calculator/3.0#CVSS:3.0/AV:N/AC:H/PR:H/UI:N/S:U/C:N/I:N/A:H">CVSS:3.0/AV:N/AC:H/PR:H/UI:N/S:U/C:N/I:N/A:H</a></td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

`ntpd` does not enable trap service by default. If trap service has been explicitly enabled, an attacker can send a specially crafted packet to cause a null pointer dereference that will crash `ntpd`, resulting in a denial of service.

* * *
    
#### Mitigation

* Implement [BCP-38.](http://www.bcp38.info/index.php/Main_Page)
* Use `restrict default noquery ...` in your `ntp.conf` file. Only allow mode 6 queries from trusted networks and hosts.
* Upgrade to [4.2.8p9 or later.](/downloads/)
* Properly monitor your `ntpd` instances, and auto-restart `ntpd` (without `-g`) if it stops running. 

* * *

#### Credit

This weakness was discovered by Matthew Van Gundy of Cisco.

* * *

#### Timeline

* 2016 Nov 21: Public release
* 2016 Nov 15: CERT given our software release notification 
* 2016 Nov 14: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* : [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/)
* : Report received