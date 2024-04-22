---
title: "NTP BUG 3592: DoS Attack on Unauthenticated Client"
description: "A system that is running NTP 4.2.8p12 or p13 that only has one unauthenticated time source can be attacked in a way that causes the victim’s next poll to its source to be delayed, for as long as the attack is maintained. This bug was resolved in NTP 4.2.8p14."
type: archives
date: "2020-03-03"
---

* * *

#### Summary

<table>
  <tbody>
	<tr>
		<th><b>Resolved</b></th>
		<td><a href="/support/securitynotice/4_2_8p14-release-announcement/">4.2.8p14</a></td>
		<td>03 Mar 2020</td>
	</tr>
	<tr>
		<th><b>References</b></th>
		<td><a href="https://bugs.ntp.org/show_bug.cgi?id=3592">Bug 3592</a></td>
		<td><a href="https://nvd.nist.gov/vuln/detail/CVE-2020-11868">CVE-2020-11868</a></td>
	</tr>
	<tr>
		<th><b>Affects</b></th>
		<td>ntp-4.2.8p12 (possibly earlier) and ntp-4.2.8p13,<br> and 4.3.98 up to, but not including 4.3.100.</td>
		<td>Resolved in 4.2.8p14 and 4.3.100.</td>
	</tr>
	<tr>
		<th><b>CVSS2 Score</b></th>
		<td>5.4</td>
		<td><a href="https://nvd.nist.gov/vuln-metrics/cvss/v2-calculator?vector=(AV:N/AC:H/Au:N/C:N/I:N/A:C)">AV:N/AC:H/Au:N/C:N/I:N/A:C</a></td>
	</tr>
	<tr>
		<th><b>CVSS3 Score<b></th>
		<td>5.9</td>
		<td><a href="https://nvd.nist.gov/vuln-metrics/cvss/v3-calculator?vector=AV:N/AC:H/PR:N/UI:N/S:U/C:N/I:N/A:H&version=3.0">CVSS:3.0/AV:N/AC:H/PR:N/UI:N/S:U/C:N/I:N/A:H</a></td>
	</tr>	
  </tbody>	
</table>

* * *
    
#### Description 

The fix for [3445](https://bugs.ntp.org/show_bug.cgi?id=3445) introduced a bug whereby a system that is running ntp-4.2.8p12 or p13 that only has one unauthenticated time source can be attacked in a way that causes the victim's next poll to its source to be delayed, for as long as the attack is maintained. 

* * *
    
#### Mitigation

*  Use authentication with symmetric peers.
* Have enough sources of time.
* Upgrade to [4.2.8p14 or later](https://downloads.nwtime.org/ntp/4.2.8/).

* * *

#### Credit

Reported by Miroslav Lichvar. 

* * *

#### Timeline

* 2020 Mar 03: Public release
* 2020 Feb 17: [Early Access Program Release: Premier and Partner Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2019 Jun 05: [Notification to Institutional Members](https://www.nwtime.org/membership/benefits/)
* 2019 May 30: Notification from reporter