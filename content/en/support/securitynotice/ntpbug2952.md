---
title: "NTP BUG 2952: Original fix for NTP Bug 2901 broke peer associations"
description: "The fix for NTP Bug 2901 in 4.2.8p4 went too far, breaking peer associations. This bug was fixed in 4.2.8p7."
type: archives
date: "2016-04-27"
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
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=2952">Bug 2952</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2015-7704">CVE-2015-7704</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>4.2.8p4 up to but not including 4.2.8p7, and 4.3.77 up to, but not including 4.3.92.</td>
		<td>Resolved in 4.2.8p7.</td>
	</tr>	
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>5.0</td>
		<td><a href="https://nvd.nist.gov/vuln-metrics/cvss/v2-calculator?calculator&version=2.0&vector=(AV:N/AC:L/Au:N/C:N/I:N/A:P)">AV:N/AC:L/Au:N/C:N/I:N/A:P</a></td>
	</tr>
	<tr>
		<th><b>CVSS3 Score<b></th>
		<td>7.5</td>
		<td><a href="https://www.first.org/cvss/calculator/3.0#CVSS:3.0/AV:N/AC:L/PR:N/UI:N/S:U/C:N/I:N/A:H">CVSS:3.0/AV:N/AC:L/PR:N/UI:N/S:U/C:N/I:N/A:H</a></td>
	</tr>
  </tbody>	
</table>

* * *
    
#### Description 

The fix for [NTP Bug 2901](https://bugs.ntp.org/show_bug.cgi?id=2901) in ntp-4.2.8p4 went too far, breaking `peer` associations.

* * *
    
#### Mitigation

* Upgrade to [4.2.8p7 or later](https://downloads.nwtime.org/ntp/4.2.8/).
* Don't connect to ntp-4.2.8p4 thru p6 instances of `ntpd` using a `peer` association.
* If you are running ntp-4.2.8p4 thru p6 instances of `ntpd` don't expect clients that connect to you with `peer` associations to work.
* Properly monitor your `ntpd` instances. 

* * *

#### Credit

This weakness was discovered by Michael Tatarinov , NTP Project Developer Volunteer.

* * *

#### Timeline

* 2016 Apr 26: Public release
* 2016 Apr 12: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2016 Feb 14: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2016 Jan 12: Initial notification from Cisco