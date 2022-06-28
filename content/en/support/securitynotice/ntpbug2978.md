---
title: "NTP BUG 2978: Interleave-pivot"
description: "It is possible to change the time of an ntpd client or deny service to an ntpd client by forcing it to change from basic client/server mode to interleaved symmetric mode. This bug was resolved in NTP 4.2.8p7."
type: archives
date: "2016-04-26"
---

* * *

#### Summary

<table>
  <tbody>
	<tr>
		<th><b>Resolved</b></th>
		<td><a href="/support/securitynotice/4_2_8p7-release-announcement/">4.2.8p7</a></td>
		<td>26 Apr 2016</td>
	</tr>
	<tr>
		<th><b>References</b></th>
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=2978">Bug 2978</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2016-1548">CVE-2016-1548</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>All ntp-4 releases up to, but not including 4.2.8p7,<br> and 4.3.0 up to, but not including 4.3.92.</td>
		<td>Resolved in 4.2.8p7.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>MED 6.4</td>
		<td><a href="https://nvd.nist.gov/vuln-metrics/cvss/v2-calculator?calculator&version=2.0&vector=(AV:N/AC:L/Au:N/C:N/I:P/A:P)">AV:N/AC:L/Au:N/C:N/I:P/A:P</a></td>
	</tr>
	<tr>
		<th><b>CVSS3 Score<b></th>
		<td>MED 7.2</td>
		<td><a href="https://www.first.org/cvss/calculator/3.0#CVSS:3.0/AV:N/AC:L/PR:N/UI:N/S:C/C:N/I:L/A:L">CVSS:3.0/AV:N/AC:L/PR:N/UI:N/S:C/C:N/I:L/A:L</a></td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

It is possible to change the time of an `ntpd` client or deny service to an `ntpd` client by forcing it to change from basic client/server mode to interleaved symmetric mode. An attacker can spoof a packet from a legitimate `ntpd` server with an origin timestamp that matches the `peer->dst` timestamp recorded for that server. After making this switch, the client will reject all future legitimate server responses. It is possible to force the victim client to move time after the mode has been changed. `ntpq` gives no indication that the mode has been switched.

* * *
    
#### Mitigation

* Implement [BCP-38](http://www.bcp38.info/index.php/Main_Page).
* Upgrade to [4.2.8p7 or later](/downloads/), which prevents `ntpd` from dynamically enabling interleave mode.
* Properly monitor your `ntpd` instances. 

* * *

#### Credit

This weakness was discovered by Miroslav Lichvar of RedHat and separately by Jonathan Gardner of Cisco ASIG.

* * *

#### Timeline

* 2016 Apr 26: Public release
* 2016 Apr 12: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2016 Feb 14: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2016 Jan 12: Initial notification from Cisco