---
title: "NTP BUG 3361: 0rigin DoS"
type: archives
date: "2017-03-21"
---

* * *

#### Summary

<table>
  <tbody>
	<tr>
		<th><b>Resolved</b></th>
		<td><a href="/support/securitynotice/4_2_8p10-release-announcement/">4.2.8p10</a></td>
		<td>21 Mar 2017</td>
	</tr>
	<tr>
		<th><b>References</b></th>
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=3361">Bug 3361</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2016-9042/">CVE-2016-9042</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>ntp-4.2.8p9 (21 Nov 2016), up to but not including ntp-4.2.8p10.</td>
		<td>Resolved in 4.2.8p10.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>MED 4.9</td>
		<td><a href="https://nvd.nist.gov/cvss.cfm?calculator&version=2&vector=(AV:N/AC:H/Au:S/C:N/I:N/A:C)">AV:N/AC:H/Au:N/C:N/I:N/A:C</a> (worst case)</td>
	</tr>
	<tr>
		<th><b>CVSS3 Score<b></th>
		<td>MED 4.4</td>
		<td><a href="https://www.first.org/cvss/calculator/3.0#CVSS:3.0/AV:N/AC:H/PR:H/UI:N/S:U/C:N/I:N/A:H">CVSS:3.0/AV:N/AC:H/PR:H/UI:N/S:U/C:N/I:N/A:H </a> (worst case)</td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

An exploitable denial of service vulnerability exists in the origin timestamp check functionality of `ntpd` 4.2.8p9. A specially crafted unauthenticated network packet can be used to reset the expected origin timestamp for target peers. Legitimate replies from targeted peers will fail the origin timestamp check (TEST2) causing the reply to be dropped and creating a denial of service condition. This vulnerability can only be exploited if the attacker can spoof all of the servers.

* * *
    
#### Mitigation

* Implement [BCP-38.](http://www.bcp38.info/index.php/Main_Page)
* Configure enough servers/peers that an attacker cannot target all of your time sources.
* Upgrade to [4.2.8p10 or later.](/downloads/) 
* Properly monitor your `ntpd` instances, and auto-restart `ntpd` (without `-g`) if it stops running.

* * *

#### Credit

This weakness was discovered by Matthew Van Gundy of Cisco.

* * *

#### Timeline

* 2017 Mar 21: Public release
* 2017 Mar 06: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2017 Mar 06: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2017 Feb 09: Mozilla/Cure53 audit received