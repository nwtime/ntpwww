---
title: "NTP BUG 2670: receive(): missing return on error"
type: archives
date: "2014-12-18"
---

* * *

#### Summary

<table>
  <tbody>
	<tr>
		<th><b>Resolved</b></th>
		<td><a href="/support/securitynotice/4_2_8-release-announcement">4.2.8</a></td>
		<td>18 Dec 2014</td>
	</tr>
	<tr>
		<th><b>References</b></th>
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=2670">Bug 2670</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2014-9296">CVE-2014-9296</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>All NTP4 releases before 4.2.8.</td>
		<td>Resolved in 4.2.8.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>5.0</td>
		<td><a href="https://nvd.nist.gov/cvss.cfm?calculator&version=2&vector=(AV:N/AC:L/Au:N/C:N/I:N/A:P)">AV:N/AC:L/Au:N/C:N/I:N/A:P</a></td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

Code in `ntp_proto.c:receive()` is missing a `return;` in the code path where an error was detected, which meant processing did not stop when a specific rare error occurred. We haven't found a way for this bug to affect system integrity. If there is no way to affect system integrity the base CVSS score for this bug is 0. If there is one avenue through which system integrity can be partially affected, the base score becomes a 5. If system integrity can be partially affected via all three integrity metrics, the CVSS base score become 7.5. 

* * *
    
#### Mitigation

* Upgrade to [4.2.8 or later](/downloads), or
* Remove or comment out all configuration directives beginning with the `crypto` keyword in your `ntp.conf` file. 

* * *

#### Credit

This vulnerability was discovered by Stephen Roettger of the Google Security Team.

* * *

#### Timeline

* 2014 Dec 18: Public release
* : [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits)
* : [Notification to Institutional Members](https://www.nwtime.org/membership/benefits)
* : Initial notification received; analysis begins