---
title: "NTP BUG 2945: 0rigin: Zero Origin Timestamp Bypass"
type: archives
date: "2016-01-19"
---

* * *

#### Summary

<table>
  <tbody>
	<tr>
		<th><b>Resolved</b></th>
		<td><a href="/support/securitynotice/4_2_8p6-release-announcement/">4.2.8p6</a></td>
		<td>19 Jan 2016</td>
	</tr>
	<tr>
		<th><b>References</b></th>
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=2945">Bug 2945</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2015-8138">CVE-2015-8138</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>All ntp-4 releases up to, but not including 4.2.8p6,<br> and 4.3.0 up to, but not including 4.3.90.</td>
		<td>Resolved in 4.2.8p6</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>MED 5.0</td>
		<td><a href="https://nvd.nist.gov/vuln-metrics/cvss/v2-calculator?calculator&version=2&vector=(AV:N/AC:L/Au:N/C:N/I:P/A:N)">AV:N/AC:L/Au:N/C:N/I:P/A:N</a></td>
	</tr>
	<tr>
		<th><b>CVSS3 Score<b></th>
		<td>MED 5.3</td>
		<td><a href="https://www.first.org/cvss/calculator/3.0#CVSS:3.0/AV:N/AC:L/PR:N/UI:N/S:U/C:N/I:L/A:N">CVSS:3.0/AV:N/AC:L/PR:N/UI:N/S:U/C:N/I:L/A:N</a><br> (3.7 - LOW if you score AC:H)</td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

To distinguish legitimate peer responses from forgeries, a client attempts to verify a response packet by ensuring that the origin timestamp in the packet matches the origin timestamp it transmitted in its last request. A logic error that allowed packets with an origin timestamp of zero to bypass this check whenever there is not an outstanding request to the server.

* * *
    
#### Mitigation

* Configure `ntpd` to get time from multiple sources.
* Upgrade to 4.2.8p6 or later.](/downloads/)
* Monitor your `ntpd` instances.

* * *

#### Credit

This weakness was discovered by Jonathan Gardner of Cisco ASIG.

* * *

#### Timeline

* 2016 Jan 19: Public release
* 2016 Jan 17: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2015 Nov 5: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2016 Oct 16: Initial notification from Cisco