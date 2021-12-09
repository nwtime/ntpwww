---
title: "NTP BUG 3011: Duplicate IPs on unconfig directives will cause an assertion botch in ntpd"
type: archives
date: "2016Y-04-26"
---

* * *

#### Summary

<table>
  <tbody>
	<tr>
		<th><b>Resolved</b></th>
		<td><a href="/support/securitynotice/4_2_8p7-release-announcement">4.2.8p7</a></td>
		<td>26 Apr 2016</td>
	</tr>
	<tr>
		<th><b>References</b></th>
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=3011">Bug 3011</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2016-2516">CVE-2016-2516</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>All ntp-4 releases up to, but not including 4.2.8p7,<br> and 4.3.0 up to, but not including 4.3.92.</td>
		<td>Resolved in 4.2.8p7.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>MED 6.3</td>
		<td><a href="https://nvd.nist.gov/cvss.cfm?calculator&version=2&vector=(AV:N/AC:M/Au:S/C:N/I:N/A:C)">AV:N/AC:M/Au:S/C:N/I:N/A:C</a></td>
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

If `ntpd` was expressly configured to allow for remote configuration, a malicious user who knows the `controlkey` for `ntpq` or the `requestkey` for `ntpdc` (if mode7 is expressly enabled) can create a session with `ntpd` and if an existing association is unconfigured using the same IP twice on the `unconfig` directive line, `ntpd` will abort.

* * *
    
#### Mitigation

* Implement [BCP-38](http://www.bcp38.info).
* Upgrade to [4.2.8p7 or later.](/downloads)
* Properly monitor your `ntpd` instances. 

* * *

#### Credit

This weakness was discovered by Yihan Lian of the Cloud Security Team, Qihoo 360.

* * *

#### Timeline

* 2016 Apr 26: Public release
* 2016 Apr 12: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits)
* 2016 Feb 14: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits)
* 2016 Jan 12: Initial notification from Cisco